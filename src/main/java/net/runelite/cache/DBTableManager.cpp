#include "DBTableManager.h"
#include "IndexType.h"
#include "ConfigType.h"

namespace net::runelite::cache
{
	using IOException = java::io::IOException;
	using Collection = java::util::Collection;
	using Collections = java::util::Collections;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using DBTableDefinition = net::runelite::cache::definitions::DBTableDefinition;
	using DBTableLoader = net::runelite::cache::definitions::loaders::DBTableLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;

	DBTableManager::DBTableManager(std::shared_ptr<Store> store) : store(store)
	{
	}

	void DBTableManager::load()
	{
		std::shared_ptr<DBTableLoader> loader = std::make_shared<DBTableLoader>();

		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::CONFIGS);
		std::shared_ptr<Archive> archive = index->getArchive(ConfigType::DBTABLE.getId());

		// just in case the loader is being run on a cache that doesn't have them
		if (archive == nullptr)
		{
			return;
		}

		std::vector<signed char> archiveData = storage->loadArchive(archive);
		std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

		for (auto f : files->getFiles())
		{
			std::shared_ptr<DBTableDefinition> table = loader->load(f->getFileId(), f->getContents());
			tables.emplace(f->getFileId(), table);
		}
	}

	std::shared_ptr<Collection<std::shared_ptr<DBTableDefinition>>> DBTableManager::getTables()
	{
		return Collections::unmodifiableCollection(tables.values());
	}

	std::shared_ptr<DBTableDefinition> DBTableManager::get(int tableId)
	{
		return tables[tableId];
	}
}
