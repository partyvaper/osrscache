#include "ItemLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using ItemDefinition = net::runelite::cache::definitions::ItemDefinition;
	using InputStream = net::runelite::cache::io::InputStream;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
	using HashMap = java::util::HashMap;
const std::shared_ptr<org::slf4j::Logger> ItemLoader::logger = org::slf4j::LoggerFactory::getLogger(ItemLoader::class);

	std::shared_ptr<ItemDefinition> ItemLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<ItemDefinition> def = std::make_shared<ItemDefinition>(id);
		std::shared_ptr<InputStream> is = std::make_shared<InputStream>(b);

		while (true)
		{
			int opcode = is->readUnsignedByte();
			if (opcode == 0)
			{
				break;
			}

			this->decodeValues(opcode, def, is);
		}

		post(def);

		return def;
	}

	void ItemLoader::decodeValues(int opcode, std::shared_ptr<ItemDefinition> def, std::shared_ptr<InputStream> stream)
	{
		if (opcode == 1)
		{
			def->inventoryModel = stream->readUnsignedShort();
		}
		else if (opcode == 2)
		{
			def->name = stream->readString();
		}
		else if (opcode == 4)
		{
			def->zoom2d = stream->readUnsignedShort();
		}
		else if (opcode == 5)
		{
			def->xan2d = stream->readUnsignedShort();
		}
		else if (opcode == 6)
		{
			def->yan2d = stream->readUnsignedShort();
		}
		else if (opcode == 7)
		{
			def->xOffset2d = stream->readUnsignedShort();
			if (def->xOffset2d > 32767)
			{
				def->xOffset2d -= 65536;
			}
		}
		else if (opcode == 8)
		{
			def->yOffset2d = stream->readUnsignedShort();
			if (def->yOffset2d > 32767)
			{
				def->yOffset2d -= 65536;
			}
		}
		else if (opcode == 9)
		{
			def->unknown1 = stream->readString();
		}
		else if (opcode == 11)
		{
			def->stackable = 1;
		}
		else if (opcode == 12)
		{
			def->cost = stream->readInt();
		}
		else if (opcode == 13)
		{
			def->wearPos1 = stream->readByte();
		}
		else if (opcode == 14)
		{
			def->wearPos2 = stream->readByte();
		}
		else if (opcode == 16)
		{
			def->members = true;
		}
		else if (opcode == 23)
		{
			def->maleModel0 = stream->readUnsignedShort();
			def->maleOffset = stream->readUnsignedByte();
		}
		else if (opcode == 24)
		{
			def->maleModel1 = stream->readUnsignedShort();
		}
		else if (opcode == 25)
		{
			def->femaleModel0 = stream->readUnsignedShort();
			def->femaleOffset = stream->readUnsignedByte();
		}
		else if (opcode == 26)
		{
			def->femaleModel1 = stream->readUnsignedShort();
		}
		else if (opcode == 27)
		{
			def->wearPos3 = stream->readByte();
		}
		else if (opcode >= 30 && opcode < 35)
		{
			def->options[opcode - 30] = stream->readString();
//JAVA TO C++ CONVERTER TODO TASK: The following Java case-insensitive String method call is not converted:
			if (def->options[opcode - 30].equalsIgnoreCase(L"Hidden"))
			{
				def->options[opcode - 30] = L"";
			}
		}
		else if (opcode >= 35 && opcode < 40)
		{
			def->interfaceOptions[opcode - 35] = stream->readString();
		}
		else if (opcode == 40)
		{
			int var5 = stream->readUnsignedByte();
			def->colorFind = std::vector<short>(var5);
			def->colorReplace = std::vector<short>(var5);

			for (int var4 = 0; var4 < var5; ++var4)
			{
				def->colorFind[var4] = static_cast<short>(stream->readUnsignedShort());
				def->colorReplace[var4] = static_cast<short>(stream->readUnsignedShort());
			}

		}
		else if (opcode == 41)
		{
			int var5 = stream->readUnsignedByte();
			def->textureFind = std::vector<short>(var5);
			def->textureReplace = std::vector<short>(var5);

			for (int var4 = 0; var4 < var5; ++var4)
			{
				def->textureFind[var4] = static_cast<short>(stream->readUnsignedShort());
				def->textureReplace[var4] = static_cast<short>(stream->readUnsignedShort());
			}

		}
		else if (opcode == 42)
		{
			def->shiftClickDropIndex = stream->readByte();
		}
		else if (opcode == 65)
		{
			def->isTradeable = true;
		}
		else if (opcode == 75)
		{
			def->weight = stream->readShort();
		}
		else if (opcode == 78)
		{
			def->maleModel2 = stream->readUnsignedShort();
		}
		else if (opcode == 79)
		{
			def->femaleModel2 = stream->readUnsignedShort();
		}
		else if (opcode == 90)
		{
			def->maleHeadModel = stream->readUnsignedShort();
		}
		else if (opcode == 91)
		{
			def->femaleHeadModel = stream->readUnsignedShort();
		}
		else if (opcode == 92)
		{
			def->maleHeadModel2 = stream->readUnsignedShort();
		}
		else if (opcode == 93)
		{
			def->femaleHeadModel2 = stream->readUnsignedShort();
		}
		else if (opcode == 94)
		{
			def->category = stream->readUnsignedShort();
		}
		else if (opcode == 95)
		{
			def->zan2d = stream->readUnsignedShort();
		}
		else if (opcode == 97)
		{
			def->notedID = stream->readUnsignedShort();
		}
		else if (opcode == 98)
		{
			def->notedTemplate = stream->readUnsignedShort();
		}
		else if (opcode >= 100 && opcode < 110)
		{
			if (def->countObj.empty())
			{
				def->countObj = std::vector<int>(10);
				def->countCo = std::vector<int>(10);
			}

			def->countObj[opcode - 100] = stream->readUnsignedShort();
			def->countCo[opcode - 100] = stream->readUnsignedShort();
		}
		else if (opcode == 110)
		{
			def->resizeX = stream->readUnsignedShort();
		}
		else if (opcode == 111)
		{
			def->resizeY = stream->readUnsignedShort();
		}
		else if (opcode == 112)
		{
			def->resizeZ = stream->readUnsignedShort();
		}
		else if (opcode == 113)
		{
			def->ambient = stream->readByte();
		}
		else if (opcode == 114)
		{
			def->contrast = stream->readByte();
		}
		else if (opcode == 115)
		{
			def->team = stream->readUnsignedByte();
		}
		else if (opcode == 139)
		{
			def->boughtId = stream->readUnsignedShort();
		}
		else if (opcode == 140)
		{
			def->boughtTemplateId = stream->readUnsignedShort();
		}
		else if (opcode == 148)
		{
			def->placeholderId = stream->readUnsignedShort();
		}
		else if (opcode == 149)
		{
			def->placeholderTemplateId = stream->readUnsignedShort();
		}
		else if (opcode == 249)
		{
			int length = stream->readUnsignedByte();

			def->params = std::unordered_map<int, std::any>(length);

			for (int i = 0; i < length; i++)
			{
				bool isString = stream->readUnsignedByte() == 1;
				int key = stream->read24BitInt();
				std::any value;

				if (isString)
				{
					value = stream->readString();
				}

				else
				{
					value = stream->readInt();
				}

				def->params.emplace(key, value);
			}
		}
		else
		{
			logger->warn(L"Unrecognized opcode {}", opcode);
		}
	}

	void ItemLoader::post(std::shared_ptr<ItemDefinition> def)
	{
		if (def->stackable == 1)
		{
			def->weight = 0;
		}
	}
}
