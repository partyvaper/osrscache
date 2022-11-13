#include "NpcLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using HashMap = java::util::HashMap;
	using NpcDefinition = net::runelite::cache::definitions::NpcDefinition;
	using InputStream = net::runelite::cache::io::InputStream;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> NpcLoader::logger = org::slf4j::LoggerFactory::getLogger(NpcLoader::class);

	std::shared_ptr<NpcDefinition> NpcLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<NpcDefinition> def = std::make_shared<NpcDefinition>(id);
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

		return def;
	}

	void NpcLoader::decodeValues(int opcode, std::shared_ptr<NpcDefinition> def, std::shared_ptr<InputStream> stream)
	{
		int length;
		int index;
		if (opcode == 1)
		{
			length = stream->readUnsignedByte();
			def->models = std::vector<int>(length);

			for (index = 0; index < length; ++index)
			{
				def->models[index] = stream->readUnsignedShort();
			}
		}
		else if (opcode == 2)
		{
			def->name = stream->readString();
		}
		else if (opcode == 12)
		{
			def->size = stream->readUnsignedByte();
		}
		else if (opcode == 13)
		{
			def->standingAnimation = stream->readUnsignedShort();
		}
		else if (opcode == 14)
		{
			def->walkingAnimation = stream->readUnsignedShort();
		}
		else if (opcode == 15)
		{
			def->idleRotateLeftAnimation = stream->readUnsignedShort();
		}
		else if (opcode == 16)
		{
			def->idleRotateRightAnimation = stream->readUnsignedShort();
		}
		else if (opcode == 17)
		{
			def->walkingAnimation = stream->readUnsignedShort();
			def->rotate180Animation = stream->readUnsignedShort();
			def->rotateLeftAnimation = stream->readUnsignedShort();
			def->rotateRightAnimation = stream->readUnsignedShort();
		}
		else if (opcode == 18)
		{
			def->category = stream->readUnsignedShort();
		}
		else if (opcode >= 30 && opcode < 35)
		{
			def->actions[opcode - 30] = stream->readString();
//JAVA TO C++ CONVERTER TODO TASK: The following Java case-insensitive String method call is not converted:
			if (def->actions[opcode - 30].equalsIgnoreCase(L"Hidden"))
			{
				def->actions[opcode - 30] = L"";
			}
		}
		else if (opcode == 40)
		{
			length = stream->readUnsignedByte();
			def->recolorToFind = std::vector<short>(length);
			def->recolorToReplace = std::vector<short>(length);

			for (index = 0; index < length; ++index)
			{
				def->recolorToFind[index] = static_cast<short>(stream->readUnsignedShort());
				def->recolorToReplace[index] = static_cast<short>(stream->readUnsignedShort());
			}

		}
		else if (opcode == 41)
		{
			length = stream->readUnsignedByte();
			def->retextureToFind = std::vector<short>(length);
			def->retextureToReplace = std::vector<short>(length);

			for (index = 0; index < length; ++index)
			{
				def->retextureToFind[index] = static_cast<short>(stream->readUnsignedShort());
				def->retextureToReplace[index] = static_cast<short>(stream->readUnsignedShort());
			}

		}
		else if (opcode == 60)
		{
			length = stream->readUnsignedByte();
			def->chatheadModels = std::vector<int>(length);

			for (index = 0; index < length; ++index)
			{
				def->chatheadModels[index] = stream->readUnsignedShort();
			}

		}
		else if (opcode == 93)
		{
			def->isMinimapVisible = false;
		}
		else if (opcode == 95)
		{
			def->combatLevel = stream->readUnsignedShort();
		}
		else if (opcode == 97)
		{
			def->widthScale = stream->readUnsignedShort();
		}
		else if (opcode == 98)
		{
			def->heightScale = stream->readUnsignedShort();
		}
		else if (opcode == 99)
		{
			def->hasRenderPriority = true;
		}
		else if (opcode == 100)
		{
			def->ambient = stream->readByte();
		}
		else if (opcode == 101)
		{
			def->contrast = stream->readByte();
		}
		else if (opcode == 102)
		{
			def->headIcon = stream->readUnsignedShort();
		}
		else if (opcode == 103)
		{
			def->rotationSpeed = stream->readUnsignedShort();
		}
		else if (opcode == 106)
		{
			def->varbitId = stream->readUnsignedShort();
			if (def->varbitId == 65535)
			{
				def->varbitId = -1;
			}

			def->varpIndex = stream->readUnsignedShort();
			if (def->varpIndex == 65535)
			{
				def->varpIndex = -1;
			}

			length = stream->readUnsignedByte();
			def->configs = std::vector<int>(length + 2);

			for (index = 0; index <= length; ++index)
			{
				def->configs[index] = stream->readUnsignedShort();
				if (def->configs[index] == L'\uffff')
				{
					def->configs[index] = -1;
				}
			}

			def->configs[length + 1] = -1;

		}
		else if (opcode == 107)
		{
			def->isInteractable = false;
		}
		else if (opcode == 109)
		{
			def->rotationFlag = false;
		}
		else if (opcode == 111)
		{
			def->isPet = true;
		}
		else if (opcode == 114)
		{
			def->runAnimation = stream->readUnsignedShort();
		}
		else if (opcode == 115)
		{
			def->runAnimation = stream->readUnsignedShort();
			def->runRotate180Animation = stream->readUnsignedShort();
			def->runRotateLeftAnimation = stream->readUnsignedShort();
			def->runRotateRightAnimation = stream->readUnsignedShort();
		}
		else if (opcode == 116)
		{
			def->crawlAnimation = stream->readUnsignedShort();
		}
		else if (opcode == 117)
		{
			def->crawlAnimation = stream->readUnsignedShort();
			def->crawlRotate180Animation = stream->readUnsignedShort();
			def->crawlRotateLeftAnimation = stream->readUnsignedShort();
			def->crawlRotateRightAnimation = stream->readUnsignedShort();
		}
		else if (opcode == 118)
		{
			def->varbitId = stream->readUnsignedShort();
			if (def->varbitId == 65535)
			{
				def->varbitId = -1;
			}

			def->varpIndex = stream->readUnsignedShort();
			if (def->varpIndex == 65535)
			{
				def->varpIndex = -1;
			}

			int var = stream->readUnsignedShort();
			if (var == 0xFFFF)
			{
				var = -1;
			}

			length = stream->readUnsignedByte();
			def->configs = std::vector<int>(length + 2);

			for (index = 0; index <= length; ++index)
			{
				def->configs[index] = stream->readUnsignedShort();
				if (def->configs[index] == L'\uffff')
				{
					def->configs[index] = -1;
				}
			}

			def->configs[length + 1] = var;
		}
		else if (opcode == 249)
		{
			length = stream->readUnsignedByte();

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
}
