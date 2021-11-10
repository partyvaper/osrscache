using System.Collections.Generic;

namespace OSRSCache.definitions.loaders
{
	using ScriptDefinition = OSRSCache.definitions.ScriptDefinition;
	using InputStream = OSRSCache.io.InputStream;
	
//JAVA TO C# CONVERTER TODO TASK: This Java 'import static' statement cannot be converted to C#:
//	import static OSRSCache.script.Opcodes.SCONST;
//JAVA TO C# CONVERTER TODO TASK: This Java 'import static' statement cannot be converted to C#:
//	import static OSRSCache.script.Opcodes.POP_INT;
//JAVA TO C# CONVERTER TODO TASK: This Java 'import static' statement cannot be converted to C#:
//	import static OSRSCache.script.Opcodes.POP_STRING;
//JAVA TO C# CONVERTER TODO TASK: This Java 'import static' statement cannot be converted to C#:
//	import static OSRSCache.script.Opcodes.RETURN;

	public class ScriptLoader
	{
		public virtual ScriptDefinition load(int id, sbyte[] b)
		{
			ScriptDefinition def = new ScriptDefinition(id);
			InputStream @in = new InputStream(b);

			@in.Offset = @in.Length - 2;
			int switchLength = @in.readUnsignedShort();

			// 2 for switchLength + the switch data + 12 for the param/vars/stack data
			int endIdx = @in.Length - 2 - switchLength - 12;
			@in.Offset = endIdx;
			int numOpcodes = @in.readInt();
			int localIntCount = @in.readUnsignedShort();
			int localStringCount = @in.readUnsignedShort();
			int intStackCount = @in.readUnsignedShort();
			int stringStackCount = @in.readUnsignedShort();

			int numSwitches = @in.readUnsignedByte();
			if (numSwitches > 0)
			{
				IDictionary<int, int>[] switches = new System.Collections.IDictionary[numSwitches];
				def.switches = switches;

				for (int i = 0; i < numSwitches; ++i)
				{
					switches[i] = new Dictionary<int, int>();

					int count = @in.readUnsignedShort();
					while (count-- > 0)
					{
						int key = @in.readInt(); // int from stack is compared to this
						int pcOffset = @in.readInt(); // pc jumps by this

						switches[i][key] = pcOffset;
					}
				}
			}

			def.localIntCount = localIntCount;
			def.localStringCount = localStringCount;
			def.intStackCount = intStackCount;
			def.stringStackCount = stringStackCount;

			@in.Offset = 0;
			@in.readStringOrNull();

			int[] instructions = new int[numOpcodes];
			int[] intOperands = new int[numOpcodes];
			string[] stringOperands = new string[numOpcodes];

			def.instructions = instructions;
			def.intOperands = intOperands;
			def.stringOperands = stringOperands;

			int opcode;
			for (int i = 0; @in.Offset < endIdx; instructions[i++] = opcode)
			{
				opcode = @in.readUnsignedShort();
				if (opcode == SCONST)
				{
					stringOperands[i] = @in.readString();
				}
				else if (opcode < 100 && opcode != RETURN && opcode != POP_INT && opcode != POP_STRING)
				{
					intOperands[i] = @in.readInt();
				}
				else
				{
					intOperands[i] = @in.readUnsignedByte();
				}
			}

			return def;
		}
	}

}