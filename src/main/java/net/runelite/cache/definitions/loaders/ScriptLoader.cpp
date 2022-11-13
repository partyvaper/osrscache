#include "ScriptLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using LinkedHashMap = java::util::LinkedHashMap;
	using Map = java::util::Map;
	using ScriptDefinition = net::runelite::cache::definitions::ScriptDefinition;
	using InputStream = net::runelite::cache::io::InputStream;
//	import static net.runelite.cache.script.Opcodes.SCONST;
//	import static net.runelite.cache.script.Opcodes.POP_INT;
//	import static net.runelite.cache.script.Opcodes.POP_STRING;
//	import static net.runelite.cache.script.Opcodes.RETURN;

	std::shared_ptr<ScriptDefinition> ScriptLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<ScriptDefinition> def = std::make_shared<ScriptDefinition>();
		def->setId(id);
		std::shared_ptr<InputStream> in = std::make_shared<InputStream>(b);

		in->setOffset(in->getLength() - 2);
		int switchLength = in->readUnsignedShort();

		// 2 for switchLength + the switch data + 12 for the param/vars/stack data
		int endIdx = in->getLength() - 2 - switchLength - 12;
		in->setOffset(endIdx);
		int numOpcodes = in->readInt();
		int localIntCount = in->readUnsignedShort();
		int localStringCount = in->readUnsignedShort();
		int intStackCount = in->readUnsignedShort();
		int stringStackCount = in->readUnsignedShort();

		int numSwitches = in->readUnsignedByte();
		if (numSwitches > 0)
		{
			std::vector<std::unordered_map<int, int>> switches = std::vector<std::unordered_map>(numSwitches);
			def->setSwitches(switches);

			for (int i = 0; i < numSwitches; ++i)
			{
				switches[i] = std::make_shared<LinkedHashMap<int, int>>();

				int count = in->readUnsignedShort();
				while (count-- > 0)
				{
					int key = in->readInt(); // int from stack is compared to this
					int pcOffset = in->readInt(); // pc jumps by this

					switches[i].emplace(key, pcOffset);
				}
			}
		}

		def->setLocalIntCount(localIntCount);
		def->setLocalStringCount(localStringCount);
		def->setIntStackCount(intStackCount);
		def->setStringStackCount(stringStackCount);

		in->setOffset(0);
		in->readStringOrNull();

		std::vector<int> instructions(numOpcodes);
		std::vector<int> intOperands(numOpcodes);
		std::vector<std::wstring> stringOperands(numOpcodes);

		def->setInstructions(instructions);
		def->setIntOperands(intOperands);
		def->setStringOperands(stringOperands);

		int opcode;
		for (int i = 0; in->getOffset() < endIdx; instructions[i++] = opcode)
		{
			opcode = in->readUnsignedShort();
			if (opcode == SCONST)
			{
				stringOperands[i] = in->readString();
			}
			else if (opcode < 100 && opcode != RETURN && opcode != POP_INT && opcode != POP_STRING)
			{
				intOperands[i] = in->readInt();
			}
			else
			{
				intOperands[i] = in->readUnsignedByte();
			}
		}

		return def;
	}
}
