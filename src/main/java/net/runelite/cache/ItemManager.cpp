#include "ItemManager.h"
#include "IndexType.h"
#include "ConfigType.h"

namespace net::runelite::cache
{
	using File = java::io::File;
	using IOException = java::io::IOException;
	using Collection = java::util::Collection;
	using Collections = java::util::Collections;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using ItemDefinition = net::runelite::cache::definitions::ItemDefinition;
	using ItemExporter = net::runelite::cache::definitions::exporters::ItemExporter;
	using ItemLoader = net::runelite::cache::definitions::loaders::ItemLoader;
	using ItemProvider = net::runelite::cache::definitions::providers::ItemProvider;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
	using IDClass = net::runelite::cache::util::IDClass;

	ItemManager::ItemManager(std::shared_ptr<Store> store) : store(store)
	{
	}

	void ItemManager::load()
	{
		std::shared_ptr<ItemLoader> loader = std::make_shared<ItemLoader>();

		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::CONFIGS);
		std::shared_ptr<Archive> archive = index->getArchive(ConfigType::ITEM.getId());

		std::vector<signed char> archiveData = storage->loadArchive(archive);
		std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

		for (auto f : files->getFiles())
		{
			std::shared_ptr<ItemDefinition> def = loader->load(f->getFileId(), f->getContents());
			items.emplace(f->getFileId(), def);
		}
	}

	void ItemManager::link()
	{
		for (auto oc : items)
		{
			link(oc->second);
		}
	}

	void ItemManager::link(std::shared_ptr<ItemDefinition> item)
	{
		if (item->notedTemplate != -1)
		{
			item->linkNote(getItem(item->notedTemplate), getItem(item->notedID));
		}
		if (item->boughtTemplateId != -1)
		{
			item->linkBought(getItem(item->boughtTemplateId), getItem(item->boughtId));
		}
		if (item->placeholderTemplateId != -1)
		{
			item->linkPlaceholder(getItem(item->placeholderTemplateId), getItem(item->placeholderId));
		}
	}

	std::shared_ptr<Collection<std::shared_ptr<ItemDefinition>>> ItemManager::getItems()
	{
		return Collections::unmodifiableCollection(items.values());
	}

	std::shared_ptr<ItemDefinition> ItemManager::getItem(int itemId)
	{
		return items[itemId];
	}

	void ItemManager::export_Keyword(std::shared_ptr<File> out)
	{
		out->mkdirs();

		for (auto def : items)
		{
			std::shared_ptr<ItemExporter> exporter = std::make_shared<ItemExporter>(def->second);

			std::shared_ptr<File> targ = std::make_shared<File>(out, def->second.id + L".json");
			exporter->exportTo(targ);
		}
	}

	void ItemManager::java(std::shared_ptr<File> java)
	{
		java->mkdirs();
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.util.IDClass ids = net.runelite.cache.util.IDClass.create(java, "ItemID"); net.runelite.cache.util.IDClass nulls = net.runelite.cache.util.IDClass.create(java, "NullItemID"))
		{
			IDClass ids = IDClass::create(java, L"ItemID");
			IDClass nulls = IDClass::create(java, L"NullItemID");
			for (auto def : items)
			{
				if (def->second.name.equalsIgnoreCase(L"NULL"))
				{
					nulls.add(def->second.name, def->second.id);
				}
				else
				{
					ids.add(def->second.name, def->second.id);
				}
			}
		}
	}

	std::shared_ptr<ItemDefinition> ItemManager::provide(int itemId)
	{
		return getItem(itemId);
	}
}
