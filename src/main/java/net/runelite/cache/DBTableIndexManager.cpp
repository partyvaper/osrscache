#include "DBTableIndexManager.h"
#include "IndexType.h"

namespace net::runelite::cache
{
	using IOException = java::io::IOException;
	using Collection = java::util::Collection;
	using Collections = java::util::Collections;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using DBTableIndex = net::runelite::cache::definitions::DBTableIndex;
	using DBTableIndexLoader = net::runelite::cache::definitions::loaders::DBTableIndexLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;

	DBTableIndexManager::DBTableIndexManager(std::shared_ptr<Store> store) : store(store)
	{
	}

	void DBTableIndexManager::load()
	{
		std::shared_ptr<DBTableIndexLoader> loader = std::make_shared<DBTableIndexLoader>();

		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::DBTABLEINDEX);
		if (index == nullptr)
		{
			return;
		}

		for (auto archive : index->getArchives())
		{
			std::vector<signed char> archiveData = storage->loadArchive(archive);
			std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

			for (auto f : files->getFiles())
			{
				// file 0 = master index, all others are fileId - 1 = columnId
				std::shared_ptr<DBTableIndex> row = loader->load(archive->getArchiveId(), f->getFileId() - 1, f->getContents());
				indexes.emplace(archive->getArchiveId() << 16 | f->getFileId(), row);
			}
		}
	}

	std::shared_ptr<Collection<std::shared_ptr<DBTableIndex>>> DBTableIndexManager::getIndexes()
	{
		return Collections::unmodifiableCollection(indexes.values());
	}

	std::shared_ptr<DBTableIndex> DBTableIndexManager::getMaster(int tableId)
	{
		return indexes[tableId << 16];
	}

	std::shared_ptr<DBTableIndex> DBTableIndexManager::get(int tableId, int columnId)
	{
		return indexes[tableId << 16 | columnId + 1];
	}
}
