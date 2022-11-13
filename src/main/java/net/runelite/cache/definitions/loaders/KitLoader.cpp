#include "KitLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using KitDefinition = net::runelite::cache::definitions::KitDefinition;
	using InputStream = net::runelite::cache::io::InputStream;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> KitLoader::logger = org::slf4j::LoggerFactory::getLogger(KitLoader::class);

	std::shared_ptr<KitDefinition> KitLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<KitDefinition> def = std::make_shared<KitDefinition>(id);
		std::shared_ptr<InputStream> is = std::make_shared<InputStream>(b);

		for (;;)
		{
			int opcode = is->readUnsignedByte();
			if (opcode == 0)
			{
				break;
			}

			if (opcode == 1)
			{
				def->bodyPartId = is->readUnsignedByte();
			}
			else if (opcode == 2)
			{
				int length = is->readUnsignedByte();
				def->models = std::vector<int>(length);

				for (int index = 0; index < length; ++index)
				{
					def->models[index] = is->readUnsignedShort();
				}
			}
			else if (opcode == 3)
			{
				def->nonSelectable = true;
			}
			else if (opcode == 40)
			{
				int length = is->readUnsignedByte();
				def->recolorToFind = std::vector<short>(length);
				def->recolorToReplace = std::vector<short>(length);

				for (int index = 0; index < length; ++index)
				{
					def->recolorToFind[index] = is->readShort();
					def->recolorToReplace[index] = is->readShort();
				}
			}
			else if (opcode == 41)
			{
				int length = is->readUnsignedByte();
				def->retextureToFind = std::vector<short>(length);
				def->retextureToReplace = std::vector<short>(length);

				for (int index = 0; index < length; ++index)
				{
					def->retextureToFind[index] = is->readShort();
					def->retextureToReplace[index] = is->readShort();
				}
			}
			else if (opcode >= 60 && opcode < 70)
			{
				def->chatheadModels[opcode - 60] = is->readUnsignedShort();
			}
		}

		return def;
	}
}
