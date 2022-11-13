#include "NpcSaver.h"

namespace net::runelite::cache::definitions::savers
{
	using Map = java::util::Map;
	using NpcDefinition = net::runelite::cache::definitions::NpcDefinition;
	using OutputStream = net::runelite::cache::io::OutputStream;

	std::vector<signed char> NpcSaver::save(std::shared_ptr<NpcDefinition> npc)
	{
		std::shared_ptr<OutputStream> out = std::make_shared<OutputStream>();
		if (!npc->models.empty())
		{
			out->writeByte(1);
			out->writeByte(npc->models.size());
			for (auto modelId : npc->models)
			{
				out->writeShort(modelId);
			}
		}
		if (npc->name != L"")
		{
			out->writeByte(2);
			out->writeString(npc->name);
		}
		if (npc->size != 1)
		{
			out->writeByte(12);
			out->writeByte(npc->size);
		}
		if (npc->standingAnimation != -1)
		{
			out->writeByte(13);
			out->writeShort(npc->standingAnimation);
		}
		if (npc->walkingAnimation != -1)
		{
			out->writeByte(14);
			out->writeShort(npc->walkingAnimation);
		}
		if (npc->idleRotateLeftAnimation != -1)
		{
			out->writeByte(15);
			out->writeShort(npc->idleRotateLeftAnimation);
		}
		if (npc->idleRotateRightAnimation != -1)
		{
			out->writeByte(16);
			out->writeShort(npc->idleRotateRightAnimation);
		}
		if (npc->rotate180Animation != -1 || npc->rotateLeftAnimation != -1 || npc->rotateRightAnimation != -1)
		{
			out->writeByte(17);
			out->writeShort(npc->walkingAnimation);
			out->writeShort(npc->rotate180Animation);
			out->writeShort(npc->rotateLeftAnimation);
			out->writeShort(npc->rotateRightAnimation);
		}
		for (int i = 0; i < 5; ++i)
		{
			if (npc->actions[i] != L"")
			{
				out->writeByte(30 + i);
				out->writeString(npc->actions[i]);
			}
		}
		if (!npc->recolorToFind.empty() && !npc->recolorToReplace.empty())
		{
			out->writeByte(40);
			out->writeByte(npc->recolorToFind.size());
			for (int i = 0; i < npc->recolorToFind.size(); ++i)
			{
				out->writeShort(npc->recolorToFind[i]);
				out->writeShort(npc->recolorToReplace[i]);
			}
		}
		if (!npc->retextureToFind.empty() && !npc->retextureToReplace.empty())
		{
			out->writeByte(41);
			out->writeByte(npc->retextureToFind.size());
			for (int i = 0; i < npc->retextureToFind.size(); ++i)
			{
				out->writeShort(npc->retextureToFind[i]);
				out->writeShort(npc->retextureToReplace[i]);
			}
		}
		if (!npc->chatheadModels.empty())
		{
			out->writeByte(60);
			out->writeByte(npc->chatheadModels.size());
			for (auto modelId : npc->chatheadModels)
			{
				out->writeShort(modelId);
			}
		}
		if (!npc->isMinimapVisible)
		{
			out->writeByte(93);
		}
		if (npc->combatLevel != -1)
		{
			out->writeByte(95);
			out->writeShort(npc->combatLevel);
		}
		out->writeByte(97);
		out->writeShort(npc->widthScale);
		out->writeByte(98);
		out->writeShort(npc->heightScale);
		if (npc->hasRenderPriority)
		{
			out->writeByte(99);
		}
		out->writeByte(100);
		out->writeByte(npc->ambient);
		out->writeByte(101);
		out->writeByte(npc->contrast);
		if (npc->headIcon != -1)
		{
			out->writeByte(102);
			out->writeShort(npc->headIcon);
		}
		out->writeByte(103);
		out->writeShort(npc->rotationSpeed);
		if (!npc->isInteractable)
		{
			out->writeByte(107);
		}
		if (!npc->rotationFlag)
		{
			out->writeByte(109);
		}
		if (npc->isPet)
		{
			out->writeByte(111);
		}
		if (!npc->configs.empty())
		{
			out->writeByte(118);
			out->writeShort(npc->varbitId);
			out->writeShort(npc->varpIndex);

			std::vector<int> c = npc->configs;
			out->writeShort(c[c.size() - 1]);
			out->writeByte(c.size() - 2);
			for (int i = 0; i <= c.size() - 2; ++i)
			{
				out->writeShort(c[i]);
			}
		}
		if (!npc->params.empty())
		{
			out->writeByte(249);
			out->writeByte(npc->params.size());
			for (auto entry : npc->params)
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
