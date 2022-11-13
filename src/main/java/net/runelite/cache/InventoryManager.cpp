#include "InventoryManager.h"
#include "IndexType.h"
#include "ConfigType.h"

namespace net::runelite::cache
{
	using IOException = java::io::IOException;
	using ArrayList = java::util::ArrayList;
	using Collections = java::util::Collections;
	using List = java::util::List;
	using InventoryDefinition = net::runelite::cache::definitions::InventoryDefinition;
	using InventoryLoader = net::runelite::cache::definitions::loaders::InventoryLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;

	InventoryManager::InventoryManager(std::shared_ptr<Store> store) : store(store)
	{
	}

	void InventoryManager::load()
	{
		std::shared_ptr<InventoryLoader> loader = std::make_shared<InventoryLoader>();

		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::CONFIGS);
		std::shared_ptr<Archive> archive = index->getArchive(ConfigType::INV.getId());

		std::vector<signed char> archiveData = storage->loadArchive(archive);
		std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

		for (auto file : files->getFiles())
		{
			std::shared_ptr<InventoryDefinition> inv = loader->load(file->getFileId(), file->getContents());
			inventories.push_back(inv);
		}
	}

	std::vector<std::shared_ptr<InventoryDefinition>> InventoryManager::getInventories()
	{
		return Collections::unmodifiableList(inventories);
	}

	std::shared_ptr<InventoryDefinition> InventoryManager::findInventory(int id)
	{
		for (auto def : inventories)
		{
			if (def->id == id)
			{
				return def;
			}
		}
		return nullptr;
	}
}
