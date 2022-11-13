#include "ItemDefinition.h"

namespace net::runelite::cache::definitions
{
	using Map = java::util::Map;
	using Data = lombok::Data;

	void ItemDefinition::linkNote(std::shared_ptr<ItemDefinition> notedItem, std::shared_ptr<ItemDefinition> unnotedItem)
	{
		this->inventoryModel = notedItem->inventoryModel;
		this->zoom2d = notedItem->zoom2d;
		this->xan2d = notedItem->xan2d;
		this->yan2d = notedItem->yan2d;
		this->zan2d = notedItem->zan2d;
		this->xOffset2d = notedItem->xOffset2d;
		this->yOffset2d = notedItem->yOffset2d;
		this->colorFind = notedItem->colorFind;
		this->colorReplace = notedItem->colorReplace;
		this->textureFind = notedItem->textureFind;
		this->textureReplace = notedItem->textureReplace;
		this->name = unnotedItem->name;
		this->members = unnotedItem->members;
		this->cost = unnotedItem->cost;
		this->stackable = 1;
	}

	void ItemDefinition::linkBought(std::shared_ptr<ItemDefinition> var1, std::shared_ptr<ItemDefinition> var2)
	{
		this->inventoryModel = var1->inventoryModel;
		this->zoom2d = var1->zoom2d;
		this->xan2d = var1->xan2d;
		this->yan2d = var1->yan2d;
		this->zan2d = var1->zan2d;
		this->xOffset2d = var1->xOffset2d;
		this->yOffset2d = var1->yOffset2d;
		this->colorFind = var2->colorFind;
		this->colorReplace = var2->colorReplace;
		this->textureFind = var2->textureFind;
		this->textureReplace = var2->textureReplace;
		this->name = var2->name;
		this->members = var2->members;
		this->stackable = var2->stackable;
		this->maleModel0 = var2->maleModel0;
		this->maleModel1 = var2->maleModel1;
		this->maleModel2 = var2->maleModel2;
		this->femaleModel0 = var2->femaleModel0;
		this->femaleModel1 = var2->femaleModel1;
		this->femaleModel2 = var2->femaleModel2;
		this->maleHeadModel = var2->maleHeadModel;
		this->maleHeadModel2 = var2->maleHeadModel2;
		this->femaleHeadModel = var2->femaleHeadModel;
		this->femaleHeadModel2 = var2->femaleHeadModel2;
		this->team = var2->team;
		this->options = var2->options;
		this->interfaceOptions = std::vector<std::wstring>(5);
		if (!var2->interfaceOptions.empty())
		{
			for (int var3 = 0; var3 < 4; ++var3)
			{
				this->interfaceOptions[var3] = var2->interfaceOptions[var3];
			}
		}

		this->interfaceOptions[4] = L"Discard";
		this->cost = 0;
	}

	void ItemDefinition::linkPlaceholder(std::shared_ptr<ItemDefinition> var1, std::shared_ptr<ItemDefinition> var2)
	{
		this->inventoryModel = var1->inventoryModel;
		this->zoom2d = var1->zoom2d;
		this->xan2d = var1->xan2d;
		this->yan2d = var1->yan2d;
		this->zan2d = var1->zan2d;
		this->xOffset2d = var1->xOffset2d;
		this->yOffset2d = var1->yOffset2d;
		this->colorFind = var1->colorFind;
		this->colorReplace = var1->colorReplace;
		this->textureFind = var1->textureFind;
		this->textureReplace = var1->textureReplace;
		this->stackable = var1->stackable;
		this->name = var2->name;
		this->cost = 0;
		this->members = false;
		this->isTradeable = false;
	}
}
