#include "OverlayLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using OverlayDefinition = net::runelite::cache::definitions::OverlayDefinition;
	using InputStream = net::runelite::cache::io::InputStream;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> OverlayLoader::logger = org::slf4j::LoggerFactory::getLogger(OverlayLoader::class);

	std::shared_ptr<OverlayDefinition> OverlayLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<OverlayDefinition> def = std::make_shared<OverlayDefinition>();
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
				def->setRgbColor(color);
			}
			else if (opcode == 2)
			{
				int texture = is->readUnsignedByte();
				def->setTexture(texture);
			}
			else if (opcode == 5)
			{
				def->setHideUnderlay(false);
			}
			else if (opcode == 7)
			{
				int secondaryColor = is->read24BitInt();
				def->setSecondaryRgbColor(secondaryColor);
			}
		}

		def->calculateHsl();

		return def;
	}
}
