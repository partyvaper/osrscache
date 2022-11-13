#include "OverlayManager.h"
#include "IndexType.h"
#include "ConfigType.h"

namespace net::runelite::cache
{
	using IOException = java::io::IOException;
	using Collection = java::util::Collection;
	using Collections = java::util::Collections;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using OverlayDefinition = net::runelite::cache::definitions::OverlayDefinition;
	using OverlayLoader = net::runelite::cache::definitions::loaders::OverlayLoader;
	using OverlayProvider = net::runelite::cache::definitions::providers::OverlayProvider;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;

	OverlayManager::OverlayManager(std::shared_ptr<Store> store) : store(store)
	{
	}

	void OverlayManager::load()
	{
		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::CONFIGS);
		std::shared_ptr<Archive> archive = index->getArchive(ConfigType::OVERLAY.getId());

		std::vector<signed char> archiveData = storage->loadArchive(archive);
		std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

		for (auto file : files->getFiles())
		{
			std::shared_ptr<OverlayLoader> loader = std::make_shared<OverlayLoader>();
			std::shared_ptr<OverlayDefinition> overlay = loader->load(file->getFileId(), file->getContents());

			overlays.emplace(overlay->getId(), overlay);
		}
	}

	std::shared_ptr<Collection<std::shared_ptr<OverlayDefinition>>> OverlayManager::getOverlays()
	{
		return Collections::unmodifiableCollection(overlays.values());
	}

	std::shared_ptr<OverlayDefinition> OverlayManager::provide(int overlayId)
	{
		return overlays[overlayId];
	}
}
