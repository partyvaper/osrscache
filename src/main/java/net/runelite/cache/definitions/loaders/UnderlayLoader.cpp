#include "UnderlayLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using UnderlayDefinition = net::runelite::cache::definitions::UnderlayDefinition;
	using InputStream = net::runelite::cache::io::InputStream;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> UnderlayLoader::logger = org::slf4j::LoggerFactory::getLogger(UnderlayLoader::class);

	std::shared_ptr<UnderlayDefinition> UnderlayLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<UnderlayDefinition> def = std::make_shared<UnderlayDefinition>();
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
				int color = is->read24BitInt();
				def->setColor(color);
			}
		}

		def->calculateHsl();

		return def;
	}
}
