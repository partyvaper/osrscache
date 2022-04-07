using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

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
namespace OSRSCache.script.disassembler
{
	// using Escaper = com.google.common.escape.Escaper;
	// using Escapers = com.google.common.escape.Escapers;
	using ScriptDefinition = OSRSCache.definitions.ScriptDefinition;
	using Instruction = OSRSCache.script.Instruction;
	using Instructions = OSRSCache.script.Instructions;
	using Opcodes = OSRSCache.script.Opcodes;


	public class Disassembler
	{
		private static readonly Escaper ESCAPER = Escapers.builder().addEscape('"', "\\\"").addEscape('\\', "\\\\").build();

		private readonly Instructions instructions = new Instructions();

		public Disassembler()
		{
			instructions.init();
		}

		private bool isJump(int opcode)
		{
			switch (opcode)
			{
				case (int) Opcodes.JUMP:
				case (int) Opcodes.IF_ICMPEQ:
				case (int) Opcodes.IF_ICMPGE:
				case (int) Opcodes.IF_ICMPGT:
				case (int) Opcodes.IF_ICMPLE:
				case (int) Opcodes.IF_ICMPLT:
				case (int) Opcodes.IF_ICMPNE:
					return true;
				default:
					return false;
			}
		}

		private bool[] needLabel(ScriptDefinition script)
		{
			int[] instructions = script.instructions;
			int[] iops = script.intOperands;
			IDictionary<int, int>[] switches = script.switches;

			bool[] jumped = new bool[instructions.Length];

			for (int i = 0; i < instructions.Length; ++i)
			{
				int opcode = instructions[i];
				int iop = iops[i];

				if (opcode == (int) Opcodes.SWITCH)
				{
					IDictionary<int, int> switchMap = switches[iop];

					foreach (KeyValuePair<int, int> entry in switchMap.SetOfKeyValuePairs())
					{
						int offset = entry.Value;

						int _to = i + offset + 1;
						Debug.Assert(_to >= 0 && _to < instructions.Length);
						jumped[_to] = true;
					}
				}

				if (!isJump(opcode))
				{
					continue;
				}

				// + 1 because the jumps go to the instructions prior to the
				// one you really want, because the pc is incremented on the
				// next loop
				int to = i + iop + 1;
				Debug.Assert(to >= 0 && to < instructions.Length);

				jumped[to] = true;
			}

			return jumped;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public String disassemble(OSRSCache.definitions.ScriptDefinition script) throws java.io.IOException
		public virtual string disassemble(ScriptDefinition script)
		{
			int[] instructions = script.instructions;
			int[] iops = script.intOperands;
			string[] sops = script.stringOperands;
			IDictionary<int, int>[] switches = script.switches;

			Debug.Assert(iops.Length == instructions.Length);
			Debug.Assert(sops.Length == instructions.Length);

			bool[] jumps = needLabel(script);

			StringBuilder writer = new StringBuilder();
			writerHeader(writer, script);

			for (int i = 0; i < instructions.Length; ++i)
			{
				int opcode = instructions[i];
				int iop = iops[i];
				string sop = sops[i];

				Instruction ins = this.instructions.find(opcode);
				if (ins == null)
				{
					Console.WriteLine("Unknown instruction {0} in script {1}", opcode, script.id);
				}

				if (jumps[i])
				{
					// something jumps here
					writer.Append("LABEL").Append(i).Append(":\n");
				}

				string name;
				if (ins != null && !string.ReferenceEquals(ins.Name, null))
				{
					name = ins.Name;
				}
				else
				{
					name = string.Format("{0:D3}", opcode);
				}

				writer.Append(string.Format("   {0,-22}", name));

				if (shouldWriteIntOperand(opcode, iop))
				{
					if (isJump(opcode))
					{
						writer.Append(" LABEL").Append(i + iop + 1);
					}
					else
					{
						writer.Append(" ").Append(iop);
					}
				}

				if (!string.ReferenceEquals(sop, null))
				{
					writer.Append(" \"").Append(ESCAPER.escape(sop)).Append("\"");
				}

				if (opcode == (int) Opcodes.SWITCH)
				{
					IDictionary<int, int> switchMap = switches[iop];

					foreach (KeyValuePair<int, int> entry in switchMap.SetOfKeyValuePairs())
					{
						int value = entry.Key;
						int jump = entry.Value;

						writer.Append("\n");
						writer.Append("      ").Append(value).Append(": LABEL").Append(i + jump + 1);
					}
				}

				writer.Append("\n");
			}

			return writer.ToString();
		}

		private bool shouldWriteIntOperand(int opcode, int operand)
		{
			if (opcode == (int) Opcodes.SWITCH)
			{
				// table follows instruction
				return false;
			}

			if (operand != 0)
			{
				// always write non-zero operand
				return true;
			}

			switch (opcode)
			{
				case (int) Opcodes.ICONST:
				case (int) Opcodes.ILOAD:
				case (int) Opcodes.SLOAD:
				case (int) Opcodes.ISTORE:
				case (int) Opcodes.SSTORE:
					return true;
			}

			// int operand is not used, don't write it
			return false;
		}

		private void writerHeader(StringBuilder writer, ScriptDefinition script)
		{
			int id = script.id;
			int intStackCount = script.intStackCount;
			int stringStackCount = script.stringStackCount;
			int localIntCount = script.localIntCount;
			int localStringCount = script.localStringCount;

			writer.Append(".id                 ").Append(id).Append('\n');
			writer.Append(".int_stack_count    ").Append(intStackCount).Append('\n');
			writer.Append(".string_stack_count ").Append(stringStackCount).Append('\n');
			writer.Append(".int_var_count      ").Append(localIntCount).Append('\n');
			writer.Append(".string_var_count   ").Append(localStringCount).Append('\n');
		}
	}

}