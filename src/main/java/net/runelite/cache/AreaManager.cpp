#include "AreaManager.h"
#include "IndexType.h"
#include "ConfigType.h"

namespace net::runelite::cache
{
	using IOException = java::io::IOException;
	using Collection = java::util::Collection;
	using Collections = java::util::Collections;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using AreaDefinition = net::runelite::cache::definitions::AreaDefinition;
	using AreaLoader = net::runelite::cache::definitions::loaders::AreaLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;

	AreaManager::AreaManager(std::shared_ptr<Store> store) : store(store)
	{
	}

	void AreaManager::load()
	{
		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::CONFIGS);
		std::shared_ptr<Archive> archive = index->getArchive(ConfigType::AREA.getId());

		std::vector<signed char> archiveData = storage->loadArchive(archive);
		std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

		for (auto file : files->getFiles())
		{
			std::shared_ptr<AreaLoader> loader = std::make_shared<AreaLoader>();
			std::shared_ptr<AreaDefinition> area = loader->load(file->getContents(), file->getFileId());
			areas.emplace(area->id, area);
		}
	}

	std::shared_ptr<Collection<std::shared_ptr<AreaDefinition>>> AreaManager::getAreas()
	{
		return Collections::unmodifiableCollection(areas.values());
	}

	std::shared_ptr<AreaDefinition> AreaManager::getArea(int areaId)
	{
		return areas[areaId];
	}
}
