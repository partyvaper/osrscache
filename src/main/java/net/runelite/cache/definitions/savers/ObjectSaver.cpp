#include "ObjectSaver.h"

namespace net::runelite::cache::definitions::savers
{
	using Map = java::util::Map;
	using ObjectDefinition = net::runelite::cache::definitions::ObjectDefinition;
	using OutputStream = net::runelite::cache::io::OutputStream;

	std::vector<signed char> ObjectSaver::save(std::shared_ptr<ObjectDefinition> obj)
	{
		std::shared_ptr<OutputStream> out = std::make_shared<OutputStream>();
		if (obj->getObjectTypes() != nullptr && obj->getObjectModels() != nullptr)
		{
			out->writeByte(1);
			out->writeByte(obj->getObjectTypes()->length);
			for (int i = 0; i < obj->getObjectTypes()->length; ++i)
			{
				out->writeShort(obj->getObjectModels()[i]);
				out->writeByte(obj->getObjectTypes()[i]);
			}
		}
		if (obj->getName() != nullptr)
		{
			out->writeByte(2);
			out->writeString(obj->getName());
		}
		if (obj->getObjectTypes() == nullptr && obj->getObjectModels() != nullptr)
		{
			out->writeByte(5);
			out->writeByte(obj->getObjectModels()->length);
			for (int i = 0; i < obj->getObjectModels()->length; ++i)
			{
				out->writeShort(obj->getObjectModels()[i]);
			}
		}
		out->writeByte(14);
		out->writeByte(obj->getSizeX());
		out->writeByte(15);
		out->writeByte(obj->getSizeY());
		if (obj->getInteractType() == 0 && !obj->isBlocksProjectile())
		{
			out->writeByte(17);
		}
		else if (!obj->isBlocksProjectile())
		{
			out->writeByte(18);
		}
		if (obj->getWallOrDoor() != -1)
		{
			out->writeByte(19);
			out->writeByte(obj->getWallOrDoor());
		}
		if (obj->getContouredGround() == 0)
		{
			out->writeByte(21);
		}
		if (!obj->isMergeNormals())
		{
			out->writeByte(22);
		}
		if (obj->isABool2111())
		{
			out->writeByte(23);
		}
		if (obj->getAnimationID() != -1)
		{
			out->writeByte(24);
			out->writeShort(obj->getAnimationID());
		}
		if (obj->getInteractType() == 1)
		{
			out->writeByte(27);
		}
		out->writeByte(28);
		out->writeByte(obj->getDecorDisplacement());
		out->writeByte(29);
		out->writeByte(obj->getAmbient());
		out->writeByte(39);
		out->writeByte(obj->getContrast() / 25);
		for (int i = 0; i < 5; ++i)
		{
			out->writeByte(30 + i);
			std::wstring action = obj->getActions()[i];
			out->writeString(action != L"" ? action : L"Hidden");
		}
		if (obj->getRecolorToFind() != nullptr && obj->getRecolorToReplace() != nullptr)
		{
			out->writeByte(40);
			out->writeByte(obj->getRecolorToFind()->length);
			for (int i = 0; i < obj->getRecolorToFind()->length; ++i)
			{
				out->writeShort(obj->getRecolorToFind()[i]);
				out->writeShort(obj->getRecolorToReplace()[i]);
			}
		}
		if (obj->getRetextureToFind() != nullptr && obj->getTextureToReplace() != nullptr)
		{
			out->writeByte(41);
			out->writeByte(obj->getRetextureToFind()->length);
			for (int i = 0; i < obj->getRetextureToFind()->length; ++i)
			{
				out->writeShort(obj->getRetextureToFind()[i]);
				out->writeShort(obj->getTextureToReplace()[i]);
			}
		}
		if (obj->isRotated())
		{
			out->writeByte(62);
		}
		if (!obj->isShadow())
		{
			out->writeByte(64);
		}
		out->writeByte(65);
		out->writeShort(obj->getModelSizeX());
		out->writeByte(66);
		out->writeShort(obj->getModelSizeHeight());
		out->writeByte(67);
		out->writeShort(obj->getModelSizeY());
		if (obj->getMapSceneID() != -1)
		{
			out->writeByte(68);
			out->writeShort(obj->getMapSceneID());
		}
		if (obj->getBlockingMask() != 0)
		{
			out->writeByte(69);
			out->writeByte(obj->getBlockingMask());
		}
		out->writeByte(70);
		out->writeShort(obj->getOffsetX());
		out->writeByte(71);
		out->writeShort(obj->getOffsetHeight());
		out->writeByte(72);
		out->writeShort(obj->getOffsetY());
		if (obj->isObstructsGround())
		{
			out->writeByte(73);
		}
		if (obj->isHollow())
		{
			out->writeByte(74);
		}
		if (obj->getSupportsItems() != -1)
		{
			out->writeByte(75);
			out->writeByte(obj->getSupportsItems());
		}
		if (obj->getAmbientSoundId() != -1)
		{
			out->writeByte(78);
			out->writeShort(obj->getAmbientSoundId());
			out->writeByte(obj->getAnInt2083());
		}
		if (obj->getAmbientSoundIds() != nullptr)
		{
			out->writeByte(79);
			out->writeShort(obj->getAnInt2112());
			out->writeShort(obj->getAnInt2113());
			out->writeByte(obj->getAnInt2083());
			out->writeByte(obj->getAmbientSoundIds()->length);
			for (int i : obj->getAmbientSoundIds())
			{
				out->writeShort(i);
			}
		}
		if (obj->getContouredGround() != -1)
		{
			out->writeByte(81);
			out->writeByte(obj->getContouredGround() / 256);
		}
		if (obj->getMapAreaId() != -1)
		{
			out->writeByte(82);
			out->writeShort(obj->getMapAreaId());
		}
		if (obj->getConfigChangeDest() != nullptr)
		{
			out->writeByte(92);
			out->writeShort(obj->getVarbitID());
			out->writeShort(obj->getVarpID());

			std::vector<int> c = obj->getConfigChangeDest();
			out->writeShort(c[c.size() - 1]);
			out->writeByte(c.size() - 2);
			for (int i = 0; i <= c.size() - 2; ++i)
			{
				out->writeShort(c[i]);
			}
		}
		if (obj->getParams() != nullptr)
		{
			out->writeByte(249);
			out->writeByte(obj->getParams()->size());
			for (std::shared_ptr<Map::Entry<int, std::any>> entry : obj->getParams().entrySet())
			{
				out->writeByte(dynamic_cast<std::wstring>(entry.second) != nullptr ? 1 : 0);
				out->write24BitInt(entry.first);
				if (dynamic_cast<std::wstring>(entry.second) != nullptr)
				{
					out->writeString(static_cast<std::wstring>(entry.second));
				}
				else
				{
					out->writeInt(static_cast<int>(entry.second));
				}
			}
		}
		out->writeByte(0);
		return out->flip();
	}
}
