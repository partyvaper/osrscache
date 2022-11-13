#include "StructManager.h"
#include "IndexType.h"
#include "ConfigType.h"

namespace net::runelite::cache
{
	using IOException = java::io::IOException;
	using Collections = java::util::Collections;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using StructDefinition = net::runelite::cache::definitions::StructDefinition;
	using StructLoader = net::runelite::cache::definitions::loaders::StructLoader;
	using StructProvider = net::runelite::cache::definitions::providers::StructProvider;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;

	StructManager::StructManager(std::shared_ptr<Store> store) : store(store)
	{
	}

	void StructManager::load()
	{
		std::shared_ptr<StructLoader> loader = std::make_shared<StructLoader>();

		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::CONFIGS);
		std::shared_ptr<Archive> archive = index->getArchive(ConfigType::STRUCT.getId());

		std::vector<signed char> archiveData = storage->loadArchive(archive);
		std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

		for (auto f : files->getFiles())
		{
			std::shared_ptr<StructDefinition> def = loader->load(f->getFileId(), f->getContents());
			structs.emplace(f->getFileId(), def);
		}
	}

	std::unordered_map<int, std::shared_ptr<StructDefinition>> StructManager::getStructs()
	{
		return Collections::unmodifiableMap(structs);
	}

	std::shared_ptr<StructDefinition> StructManager::getStruct(int structId)
	{
		return structs[structId];
	}

	std::shared_ptr<StructDefinition> StructManager::provide(int structId)
	{
		return getStruct(structId);
	}
}
