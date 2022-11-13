#include "ObjectLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using ObjectDefinition = net::runelite::cache::definitions::ObjectDefinition;
	using InputStream = net::runelite::cache::io::InputStream;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> ObjectLoader::logger = org::slf4j::LoggerFactory::getLogger(ObjectLoader::class);

	std::shared_ptr<ObjectDefinition> ObjectLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<ObjectDefinition> def = std::make_shared<ObjectDefinition>();
		std::shared_ptr<InputStream> is = std::make_shared<InputStream>(b);

		def->setId(id);

		for (;;)
		{
			int opcode = is->readUnsignedByte();
			if (opcode == 0)
			{
				break;
			}

			processOp(opcode, def, is);
		}

		post(def);

		return def;
	}

	void ObjectLoader::processOp(int opcode, std::shared_ptr<ObjectDefinition> def, std::shared_ptr<InputStream> is)
	{
		if (opcode == 1)
		{
			int length = is->readUnsignedByte();
			if (length > 0)
			{
				std::vector<int> objectTypes(length);
				std::vector<int> objectModels(length);

				for (int index = 0; index < length; ++index)
				{
					objectModels[index] = is->readUnsignedShort();
					objectTypes[index] = is->readUnsignedByte();
				}

				def->setObjectTypes(objectTypes);
				def->setObjectModels(objectModels);
			}
		}
		else if (opcode == 2)
		{
			def->setName(is->readString());
		}
		else if (opcode == 5)
		{
			int length = is->readUnsignedByte();
			if (length > 0)
			{
				def->setObjectTypes(nullptr);
				std::vector<int> objectModels(length);

				for (int index = 0; index < length; ++index)
				{
					objectModels[index] = is->readUnsignedShort();
				}

				def->setObjectModels(objectModels);
			}
		}
		else if (opcode == 14)
		{
			def->setSizeX(is->readUnsignedByte());
		}
		else if (opcode == 15)
		{
			def->setSizeY(is->readUnsignedByte());
		}
		else if (opcode == 17)
		{
			def->setInteractType(0);
			def->setBlocksProjectile(false);
		}
		else if (opcode == 18)
		{
			def->setBlocksProjectile(false);
		}
		else if (opcode == 19)
		{
			def->setWallOrDoor(is->readUnsignedByte());
		}
		else if (opcode == 21)
		{
			def->setContouredGround(0);
		}
		else if (opcode == 22)
		{
			def->setMergeNormals(true);
		}
		else if (opcode == 23)
		{
			def->setABool2111(true);
		}
		else if (opcode == 24)
		{
			def->setAnimationID(is->readUnsignedShort());
			if (def->getAnimationID() == 0xFFFF)
			{
				def->setAnimationID(-1);
			}
		}
		else if (opcode == 27)
		{
			def->setInteractType(1);
		}
		else if (opcode == 28)
		{
			def->setDecorDisplacement(is->readUnsignedByte());
		}
		else if (opcode == 29)
		{
			def->setAmbient(is->readByte());
		}
		else if (opcode == 39)
		{
			def->setContrast(is->readByte() * 25);
		}
		else if (opcode >= 30 && opcode < 35)
		{
			std::vector<std::wstring> actions = def->getActions();
			actions[opcode - 30] = is->readString();
//JAVA TO C++ CONVERTER TODO TASK: The following Java case-insensitive String method call is not converted:
			if (actions[opcode - 30].equalsIgnoreCase(L"Hidden"))
			{
				actions[opcode - 30] = L"";
			}
		}
		else if (opcode == 40)
		{
			int length = is->readUnsignedByte();
			std::vector<short> recolorToFind(length);
			std::vector<short> recolorToReplace(length);

			for (int index = 0; index < length; ++index)
			{
				recolorToFind[index] = is->readShort();
				recolorToReplace[index] = is->readShort();
			}

			def->setRecolorToFind(recolorToFind);
			def->setRecolorToReplace(recolorToReplace);
		}
		else if (opcode == 41)
		{
			int length = is->readUnsignedByte();
			std::vector<short> retextureToFind(length);
			std::vector<short> textureToReplace(length);

			for (int index = 0; index < length; ++index)
			{
				retextureToFind[index] = is->readShort();
				textureToReplace[index] = is->readShort();
			}

			def->setRetextureToFind(retextureToFind);
			def->setTextureToReplace(textureToReplace);
		}
		else if (opcode == 61)
		{
			def->setCategory(is->readUnsignedShort());
		}
		else if (opcode == 62)
		{
			def->setRotated(true);
		}
		else if (opcode == 64)
		{
			def->setShadow(false);
		}
		else if (opcode == 65)
		{
			def->setModelSizeX(is->readUnsignedShort());
		}
		else if (opcode == 66)
		{
			def->setModelSizeHeight(is->readUnsignedShort());
		}
		else if (opcode == 67)
		{
			def->setModelSizeY(is->readUnsignedShort());
		}
		else if (opcode == 68)
		{
			def->setMapSceneID(is->readUnsignedShort());
		}
		else if (opcode == 69)
		{
			def->setBlockingMask(is->readByte());
		}
		else if (opcode == 70)
		{
			def->setOffsetX(is->readUnsignedShort());
		}
		else if (opcode == 71)
		{
			def->setOffsetHeight(is->readUnsignedShort());
		}
		else if (opcode == 72)
		{
			def->setOffsetY(is->readUnsignedShort());
		}
		else if (opcode == 73)
		{
			def->setObstructsGround(true);
		}
		else if (opcode == 74)
		{
			def->setHollow(true);
		}
		else if (opcode == 75)
		{
			def->setSupportsItems(is->readUnsignedByte());
		}
		else if (opcode == 77)
		{
			int varpID = is->readUnsignedShort();
			if (varpID == 0xFFFF)
			{
				varpID = -1;
			}
			def->setVarbitID(varpID);

			int configId = is->readUnsignedShort();
			if (configId == 0xFFFF)
			{
				configId = -1;
			}
			def->setVarpID(configId);

			int length = is->readUnsignedByte();
			std::vector<int> configChangeDest(length + 2);

			for (int index = 0; index <= length; ++index)
			{
				configChangeDest[index] = is->readUnsignedShort();
				if (0xFFFF == configChangeDest[index])
				{
					configChangeDest[index] = -1;
				}
			}

			configChangeDest[length + 1] = -1;

			def->setConfigChangeDest(configChangeDest);
		}
		else if (opcode == 78)
		{
			def->setAmbientSoundId(is->readUnsignedShort());
			def->setAnInt2083(is->readUnsignedByte());
		}
		else if (opcode == 79)
		{
			def->setAnInt2112(is->readUnsignedShort());
			def->setAnInt2113(is->readUnsignedShort());
			def->setAnInt2083(is->readUnsignedByte());
			int length = is->readUnsignedByte();
			std::vector<int> anIntArray2084(length);

			for (int index = 0; index < length; ++index)
			{
				anIntArray2084[index] = is->readUnsignedShort();
			}

			def->setAmbientSoundIds(anIntArray2084);
		}
		else if (opcode == 81)
		{
			def->setContouredGround(is->readUnsignedByte() * 256);
		}
		else if (opcode == 82)
		{
			def->setMapAreaId(is->readUnsignedShort());
		}
		else if (opcode == 89)
		{
			def->setRandomizeAnimStart(true);
		}
		else if (opcode == 92)
		{
			int varpID = is->readUnsignedShort();
			if (varpID == 0xFFFF)
			{
				varpID = -1;
			}
			def->setVarbitID(varpID);

			int configId = is->readUnsignedShort();
			if (configId == 0xFFFF)
			{
				configId = -1;
			}
			def->setVarpID(configId);


			int var = is->readUnsignedShort();
			if (var == 0xFFFF)
			{
				var = -1;
			}

			int length = is->readUnsignedByte();
			std::vector<int> configChangeDest(length + 2);

			for (int index = 0; index <= length; ++index)
			{
				configChangeDest[index] = is->readUnsignedShort();
				if (0xFFFF == configChangeDest[index])
				{
					configChangeDest[index] = -1;
				}
			}

			configChangeDest[length + 1] = var;

			def->setConfigChangeDest(configChangeDest);
		}
		else if (opcode == 249)
		{
			int length = is->readUnsignedByte();

			std::unordered_map<int, std::any> params(length);
			for (int i = 0; i < length; i++)
			{
				bool isString = is->readUnsignedByte() == 1;
				int key = is->read24BitInt();
				std::any value;

				if (isString)
				{
					value = is->readString();
				}

				else
				{
					value = is->readInt();
				}

				params.emplace(key, value);
			}

			def->setParams(params);
		}
		else
		{
			logger->warn(L"Unrecognized opcode {}", opcode);
		}
	}

	void ObjectLoader::post(std::shared_ptr<ObjectDefinition> def)
	{
		if (def->getWallOrDoor() == -1)
		{
			def->setWallOrDoor(0);
			if (def->getObjectModels() != nullptr && (def->getObjectTypes() == nullptr || def->getObjectTypes()[0] == 10))
			{
				def->setWallOrDoor(1);
			}

			for (int var1 = 0; var1 < 5; ++var1)
			{
				if (def->getActions()[var1] != nullptr)
				{
					def->setWallOrDoor(1);
				}
			}
		}

		if (def->getSupportsItems() == -1)
		{
			def->setSupportsItems(def->getInteractType() != 0 ? 1 : 0);
		}
	}
}
