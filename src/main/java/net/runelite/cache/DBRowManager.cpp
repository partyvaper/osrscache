#include "DBRowManager.h"
#include "IndexType.h"
#include "ConfigType.h"

namespace net::runelite::cache
{
	using IOException = java::io::IOException;
	using Collection = java::util::Collection;
	using Collections = java::util::Collections;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using DBRowDefinition = net::runelite::cache::definitions::DBRowDefinition;
	using DBRowLoader = net::runelite::cache::definitions::loaders::DBRowLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;

	DBRowManager::DBRowManager(std::shared_ptr<Store> store) : store(store)
	{
	}

	void DBRowManager::load()
	{
		std::shared_ptr<DBRowLoader> loader = std::make_shared<DBRowLoader>();

		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::CONFIGS);
		std::shared_ptr<Archive> archive = index->getArchive(ConfigType::DBROW.getId());

		// just in case the loader is being run on a cache that doesn't have them
		if (archive == nullptr)
		{
			return;
		}

		std::vector<signed char> archiveData = storage->loadArchive(archive);
		std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

		for (auto f : files->getFiles())
		{
			std::shared_ptr<DBRowDefinition> row = loader->load(f->getFileId(), f->getContents());
			rows.emplace(f->getFileId(), row);
		}
	}

	std::shared_ptr<Collection<std::shared_ptr<DBRowDefinition>>> DBRowManager::getRows()
	{
		return Collections::unmodifiableCollection(rows.values());
	}

	std::shared_ptr<DBRowDefinition> DBRowManager::get(int rowId)
	{
		return rows[rowId];
	}
}
