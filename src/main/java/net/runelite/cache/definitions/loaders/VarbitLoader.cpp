#include "VarbitLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using VarbitDefinition = net::runelite::cache::definitions::VarbitDefinition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::shared_ptr<VarbitDefinition> VarbitLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<VarbitDefinition> def = std::make_shared<VarbitDefinition>();
		std::shared_ptr<InputStream> is = std::make_shared<InputStream>(b);

		def->setId(id);

		for (;;)
		{
			int opcode = is->readUnsignedByte();
			if (opcode == 0)
			{
				break;
			}

			if (opcode == 1)
			{
				def->setIndex(is->readUnsignedShort());
				def->setLeastSignificantBit(is->readUnsignedByte());
				def->setMostSignificantBit(is->readUnsignedByte());
			}
		}

		return def;
	}
}
