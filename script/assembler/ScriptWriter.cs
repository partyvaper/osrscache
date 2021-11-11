using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

/*
 * Copyright (c) 2017, Adam <Adam@sigterm.info>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
namespace OSRSCache.script.assembler
{
	using ScriptDefinition = OSRSCache.definitions.ScriptDefinition;
	using Instruction = OSRSCache.script.Instruction;
	using Instructions = OSRSCache.script.Instructions;
	using Opcodes = OSRSCache.script.Opcodes;


	public class ScriptWriter : rs2asmBaseListener
	{
		private readonly Instructions instructions;
		private readonly LabelVisitor labelVisitor;

		private int id;
		private int pos;
		private int intStackCount;
		private int stringStackCount;
		private int localIntCount;
		private int localStringCount;
		private IList<int> opcodes = new List<int>();
		private IList<int> iops = new List<int>();
		private IList<string> sops = new List<string>();
		private IList<LookupSwitch> switches = new List<LookupSwitch>();

		public ScriptWriter(Instructions instructions, LabelVisitor labelVisitor)
		{
			this.instructions = instructions;
			this.labelVisitor = labelVisitor;
		}

		public override void enterId_value(rs2asmParser.Id_valueContext ctx)
		{
			int value = int.Parse(ctx.getText());
			id = value;
		}

		public override void enterInt_stack_value(rs2asmParser.Int_stack_valueContext ctx)
		{
			int value = int.Parse(ctx.getText());
			intStackCount = value;
		}

		public override void enterString_stack_value(rs2asmParser.String_stack_valueContext ctx)
		{
			int value = int.Parse(ctx.getText());
			stringStackCount = value;
		}

		public override void enterInt_var_value(rs2asmParser.Int_var_valueContext ctx)
		{
			int value = int.Parse(ctx.getText());
			localIntCount = value;
		}

		public override void enterString_var_value(rs2asmParser.String_var_valueContext ctx)
		{
			int value = int.Parse(ctx.getText());
			localStringCount = value;
		}

		public override void exitInstruction(rs2asmParser.InstructionContext ctx)
		{
			++pos;
		}

		public override void enterName_string(rs2asmParser.Name_stringContext ctx)
		{
			string text = ctx.getText();
			Instruction i = instructions.find(text);
			if (i == null)
			{
				Console.WriteLine("Unknown instruction {}", text);
				throw new Exception("Unknown instruction " + text);
			}

			int opcode = i.Opcode;
			addOpcode(opcode);
		}

		public override void enterName_opcode(rs2asmParser.Name_opcodeContext ctx)
		{
			string text = ctx.getText();
			int opcode = int.Parse(text);
			addOpcode(opcode);
		}

		private void addOpcode(int opcode)
		{
			Debug.Assert(opcodes.Count == pos);
			Debug.Assert(iops.Count == pos);
			Debug.Assert(sops.Count == pos);
			Debug.Assert(switches.Count == pos);

			opcodes.Add(opcode);
			iops.Add(null);
			sops.Add(null);
			switches.Add(null);
		}

		public override void enterOperand_int(rs2asmParser.Operand_intContext ctx)
		{
			string text = ctx.getText();
			int value = int.Parse(text);
			iops[pos] = value;
		}

		public override void enterOperand_qstring(rs2asmParser.Operand_qstringContext ctx)
		{
			string text = ctx.getText();
			text = text.Substring(1, (text.Length - 1) - 1);
			sops[pos] = text;
		}

		public override void enterOperand_label(rs2asmParser.Operand_labelContext ctx)
		{
			string text = ctx.getText();
			int? instruction = labelVisitor.getInstructionForLabel(text);
			if (instruction == null)
			{
				throw new Exception("reference to unknown label " + text);
			}

			int target = instruction.Value - pos - 1; // -1 to go to the instruction prior
			iops[pos] = target;
		}

		public override void enterSwitch_lookup(rs2asmParser.Switch_lookupContext ctx)
		{
			if (switches[pos - 1] != null)
			{
				return;
			}

			LookupSwitch ls = new LookupSwitch();
			switches[pos - 1] = ls;
		}

		public override void exitSwitch_key(rs2asmParser.Switch_keyContext ctx)
		{
			string text = ctx.getText();
			int key = int.Parse(text);

			LookupSwitch ls = switches[pos - 1];
			Debug.Assert(ls != null);

			LookupCase scase = new LookupCase();
			scase.Value = key;

			ls.Cases.Add(scase);
		}

		public override void exitSwitch_value(rs2asmParser.Switch_valueContext ctx)
		{
			string text = ctx.getText();
			int? instruction = labelVisitor.getInstructionForLabel(text);
			if (instruction == null)
			{
				throw new Exception("reference to unknown label " + text);
			}

			int target = instruction.Value - (pos - 1) - 1; // to go to the instruction prior to target

			LookupSwitch ls = switches[pos - 1];
			Debug.Assert(ls != null);

			LookupCase scase = ls.Cases[ls.Cases.Count - 1];
			scase.Offset = target;
		}

		public virtual ScriptDefinition buildScript()
		{
			setSwitchOperands();

			ScriptDefinition script = new ScriptDefinition(id);
			script.intStackCount = intStackCount;
			script.stringStackCount = stringStackCount;
			script.localIntCount = localIntCount;
			script.localStringCount = localStringCount;
			script.instructions = ((List<int>)opcodes).ToArray(); // opcodes.Select(int.valueOf).ToArray();
			script.intOperands = iops.Select(i => i == null ? 0 : i).ToArray(); // .Select(int.valueOf).ToArray();
			script.stringOperands = ((List<string>)sops).ToArray();
			script.switches = buildSwitches();
			return script;
		}

		private void setSwitchOperands()
		{
			int count = 0;
			for (int i = 0; i < opcodes.Count; ++i)
			{
				if (opcodes[i] != (int) Opcodes.SWITCH)
				{
					continue;
				}

				iops[i] = count++;
			}
		}

		private IDictionary<int, int>[] buildSwitches()
		{
			int count = (int) switches.Where(Object.nonNull).Count();

			if (count == 0)
			{
				return null;
			}

			int index = 0;
			IDictionary<int, int>[] maps = new System.Collections.IDictionary[count];
			foreach (LookupSwitch lswitch in switches)
			{
				if (lswitch == null)
				{
					continue;
				}

				IDictionary<int, int> map = maps[index++] = new Dictionary<int, int>();

				foreach (LookupCase scase in lswitch.Cases)
				{
					map[scase.Value] = scase.Offset;
				}
			}
			return maps;
		}
	}

}