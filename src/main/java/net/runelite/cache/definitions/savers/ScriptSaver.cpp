#include "ScriptSaver.h"

namespace net::runelite::cache::definitions::savers
{
	using Map = java::util::Map;
	using Entry = java::util::Map::Entry;
	using ScriptDefinition = net::runelite::cache::definitions::ScriptDefinition;
	using OutputStream = net::runelite::cache::io::OutputStream;
//	import static net.runelite.cache.script.Opcodes.SCONST;
//	import static net.runelite.cache.script.Opcodes.POP_INT;
//	import static net.runelite.cache.script.Opcodes.POP_STRING;
//	import static net.runelite.cache.script.Opcodes.RETURN;

	std::vector<signed char> ScriptSaver::save(std::shared_ptr<ScriptDefinition> script)
	{
		std::vector<int> instructions = script->getInstructions();
		std::vector<int> intOperands = script->getIntOperands();
		std::vector<std::wstring> stringOperands = script->getStringOperands();
		std::vector<std::unordered_map<int, int>> switches = script->getSwitches();

		std::shared_ptr<OutputStream> out = std::make_shared<OutputStream>();
		out->writeByte(0); // null string
		for (int i = 0; i < instructions.size(); ++i)
		{
			int opcode = instructions[i];
			out->writeShort(opcode);
			if (opcode == SCONST)
			{
				out->writeString(stringOperands[i]);
			}
			else if (opcode < 100 && opcode != RETURN && opcode != POP_INT && opcode != POP_STRING)
			{
				out->writeInt(intOperands[i]);
			}
			else
			{
				out->writeByte(intOperands[i]);
			}
		}
		out->writeInt(instructions.size());
		out->writeShort(script->getLocalIntCount());
		out->writeShort(script->getLocalStringCount());
		out->writeShort(script->getIntStackCount());
		out->writeShort(script->getStringStackCount());
		int switchStart = out->getOffset();
		if (switches.empty())
		{
			out->writeByte(0);
		}
		else
		{
			out->writeByte(switches.size());
			for (auto s : switches)
			{
				out->writeShort(s.size());
				for (auto e : s)
				{
					out->writeInt(e.first);
					out->writeInt(e.second);
				}
			}
		}
		int switchLength = out->getOffset() - switchStart;
		out->writeShort(switchLength);
		return out->flip();
	}
}
