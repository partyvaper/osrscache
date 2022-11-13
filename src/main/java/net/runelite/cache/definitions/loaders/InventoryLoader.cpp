#include "InventoryLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using InventoryDefinition = net::runelite::cache::definitions::InventoryDefinition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::shared_ptr<InventoryDefinition> InventoryLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<InventoryDefinition> def = std::make_shared<InventoryDefinition>();
		def->id = id;
		std::shared_ptr<InputStream> is = std::make_shared<InputStream>(b);

		while (true)
		{
			int opcode = is->readUnsignedByte();
			if (opcode == 0)
			{
				break;
			}

			if (opcode == 2)
			{
				def->size = is->readUnsignedShort();
			}
		}

		return def;
	}
}
