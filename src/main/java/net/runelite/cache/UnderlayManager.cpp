#include "UnderlayManager.h"
#include "IndexType.h"
#include "ConfigType.h"

namespace net::runelite::cache
{
	using IOException = java::io::IOException;
	using Collection = java::util::Collection;
	using Collections = java::util::Collections;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using UnderlayDefinition = net::runelite::cache::definitions::UnderlayDefinition;
	using UnderlayLoader = net::runelite::cache::definitions::loaders::UnderlayLoader;
	using UnderlayProvider = net::runelite::cache::definitions::providers::UnderlayProvider;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;

	UnderlayManager::UnderlayManager(std::shared_ptr<Store> store) : store(store)
	{
	}

	void UnderlayManager::load()
	{
		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::CONFIGS);
		std::shared_ptr<Archive> archive = index->getArchive(ConfigType::UNDERLAY.getId());

		std::vector<signed char> archiveData = storage->loadArchive(archive);
		std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

		for (auto file : files->getFiles())
		{
			std::shared_ptr<UnderlayLoader> loader = std::make_shared<UnderlayLoader>();
			std::shared_ptr<UnderlayDefinition> underlay = loader->load(file->getFileId(), file->getContents());

			underlays.emplace(underlay->getId(), underlay);
		}
	}

	std::shared_ptr<Collection<std::shared_ptr<UnderlayDefinition>>> UnderlayManager::getUnderlays()
	{
		return Collections::unmodifiableCollection(underlays.values());
	}

	std::shared_ptr<UnderlayDefinition> UnderlayManager::provide(int underlayId)
	{
		return underlays[underlayId];
	}
}
