#include "ItemSaver.h"

namespace net::runelite::cache::definitions::savers
{
	using Entry = java::util::Map::Entry;
	using ItemDefinition = net::runelite::cache::definitions::ItemDefinition;
	using OutputStream = net::runelite::cache::io::OutputStream;

	std::vector<signed char> ItemSaver::save(std::shared_ptr<ItemDefinition> item)
	{
		std::shared_ptr<OutputStream> out = std::make_shared<OutputStream>();
		if (item->inventoryModel != 0)
		{
			out->writeByte(1);
			out->writeShort(item->inventoryModel);
		}
		if (item->name != L"")
		{
			out->writeByte(2);
			out->writeString(item->name);
		}
		out->writeByte(4);
		out->writeShort(item->zoom2d);
		out->writeByte(5);
		out->writeShort(item->xan2d);
		out->writeByte(6);
		out->writeShort(item->yan2d);
		out->writeByte(7);
		out->writeShort(item->xOffset2d);
		out->writeByte(8);
		out->writeShort(item->yOffset2d);
		if (item->stackable != 0)
		{
			out->writeByte(11);
		}
		out->writeByte(12);
		out->writeInt(item->cost);
		if (item->members)
		{
			out->writeByte(16);
		}
		if (item->maleModel0 != -1 || item->maleOffset != 0)
		{
			out->writeByte(23);
			out->writeShort(item->maleModel0);
			out->writeByte(item->maleOffset);
		}
		if (item->maleModel1 != -1)
		{
			out->writeByte(24);
			out->writeShort(item->maleModel1);
		}
		if (item->femaleModel0 != -1 || item->femaleOffset != 0)
		{
			out->writeByte(25);
			out->writeShort(item->femaleModel0);
			out->writeByte(item->femaleOffset);
		}
		if (item->femaleModel1 != -1)
		{
			out->writeByte(26);
			out->writeShort(item->femaleModel1);
		}
		for (int i = 0; i < 5; ++i)
		{
			if (item->options[i] != L"")
			{
				out->writeByte(30 + i);
				out->writeString(item->options[i]);
			}
		}
		for (int i = 0; i < 5; ++i)
		{
			if (item->interfaceOptions[i] != L"")
			{
				out->writeByte(35 + i);
				out->writeString(item->interfaceOptions[i]);
			}
		}
		if (!item->colorFind.empty() && !item->colorReplace.empty())
		{
			out->writeByte(40);
			out->writeByte(item->colorFind.size());
			for (int i = 0; i < item->colorFind.size(); ++i)
			{
				out->writeShort(item->colorFind[i]);
				out->writeShort(item->colorReplace[i]);
			}
		}
		if (!item->textureFind.empty() && !item->textureReplace.empty())
		{
			out->writeByte(41);
			out->writeByte(item->textureFind.size());
			for (int i = 0; i < item->textureFind.size(); ++i)
			{
				out->writeShort(item->textureFind[i]);
				out->writeShort(item->textureReplace[i]);
			}
		}
		out->writeByte(42);
		out->writeByte(item->shiftClickDropIndex);
		if (item->isTradeable)
		{
			out->writeByte(65);
		}
		if (item->maleModel2 != -1)
		{
			out->writeByte(78);
			out->writeShort(item->maleModel2);
		}
		if (item->femaleModel2 != -1)
		{
			out->writeByte(79);
			out->writeShort(item->femaleModel2);
		}
		if (item->maleHeadModel != -1)
		{
			out->writeByte(90);
			out->writeShort(item->maleHeadModel);
		}
		if (item->femaleHeadModel != -1)
		{
			out->writeByte(91);
			out->writeShort(item->femaleHeadModel);
		}
		if (item->maleHeadModel2 != -1)
		{
			out->writeByte(92);
			out->writeShort(item->maleHeadModel2);
		}
		if (item->femaleHeadModel2 != -1)
		{
			out->writeByte(93);
			out->writeShort(item->femaleHeadModel2);
		}
		out->writeByte(95);
		out->writeShort(item->zan2d);
		if (item->notedID != -1)
		{
			out->writeByte(97);
			out->writeShort(item->notedID);
		}
		if (item->notedTemplate != -1)
		{
			out->writeByte(98);
			out->writeShort(item->notedTemplate);
		}
		if (!item->countObj.empty())
		{
			for (int i = 0; i < 10; ++i)
			{
				out->writeByte(100 + i);
				out->writeShort(item->countObj[i]);
				out->writeShort(item->countCo[i]);
			}
		}
		out->writeByte(110);
		out->writeShort(item->resizeX);
		out->writeByte(111);
		out->writeShort(item->resizeY);
		out->writeByte(112);
		out->writeShort(item->resizeZ);
		out->writeByte(113);
		out->writeByte(item->ambient);
		out->writeByte(114);
		out->writeByte(item->contrast);
		out->writeByte(115);
		out->writeByte(item->team);
		if (item->boughtId != -1)
		{
			out->writeByte(139);
			out->writeShort(item->boughtId);
		}
		if (item->boughtTemplateId != -1)
		{
			out->writeByte(140);
			out->writeShort(item->boughtTemplateId);
		}
		if (item->placeholderId != -1)
		{
			out->writeByte(148);
			out->writeShort(item->placeholderId);
		}
		if (item->placeholderTemplateId != -1)
		{
			out->writeByte(149);
			out->writeShort(item->placeholderTemplateId);
		}
		if (!item->params.empty())
		{
			out->writeByte(249);
			out->writeByte(item->params.size());
			for (auto entry : item->params)
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
