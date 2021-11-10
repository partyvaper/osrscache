using System.Collections.Generic;

namespace OSRSCache.definitions.savers
{
	using ScriptDefinition = OSRSCache.definitions.ScriptDefinition;
	using OutputStream = OSRSCache.io.OutputStream;
//JAVA TO C# CONVERTER TODO TASK: This Java 'import static' statement cannot be converted to C#:
//	import static OSRSCache.script.Opcodes.SCONST;
//JAVA TO C# CONVERTER TODO TASK: This Java 'import static' statement cannot be converted to C#:
//	import static OSRSCache.script.Opcodes.POP_INT;
//JAVA TO C# CONVERTER TODO TASK: This Java 'import static' statement cannot be converted to C#:
//	import static OSRSCache.script.Opcodes.POP_STRING;
//JAVA TO C# CONVERTER TODO TASK: This Java 'import static' statement cannot be converted to C#:
//	import static OSRSCache.script.Opcodes.RETURN;

	public class ScriptSaver
	{
		public virtual sbyte[] save(ScriptDefinition script)
		{
			int[] instructions = script.instructions;
			int[] intOperands = script.intOperands;
			string[] stringOperands = script.stringOperands;
			IDictionary<int, int>[] switches = script.switches;

			OutputStream @out = new OutputStream();
			@out.writeByte(0); // null string
			for (int i = 0; i < instructions.Length; ++i)
			{
				int opcode = instructions[i];
				@out.writeShort(opcode);
				if (opcode == SCONST)
				{
					@out.writeString(stringOperands[i]);
				}
				else if (opcode < 100 && opcode != RETURN && opcode != POP_INT && opcode != POP_STRING)
				{
					@out.writeInt(intOperands[i]);
				}
				else
				{
					@out.writeByte(intOperands[i]);
				}
			}
			@out.writeInt(instructions.Length);
			@out.writeShort(script.localIntCount);
			@out.writeShort(script.localStringCount);
			@out.writeShort(script.intStackCount);
			@out.writeShort(script.stringStackCount);
			int switchStart = @out.Offset;
			if (switches == null)
			{
				@out.writeByte(0);
			}
			else
			{
				@out.writeByte(switches.Length);
				foreach (IDictionary<int, int> s in switches)
				{
					@out.writeShort(s.Count);
					foreach (KeyValuePair<int, int> e in s.SetOfKeyValuePairs())
					{
						@out.writeInt(e.Key);
						@out.writeInt(e.Value);
					}
				}
			}
			int switchLength = @out.Offset - switchStart;
			@out.writeShort(switchLength);
			return @out.flip();
		}
	}

}