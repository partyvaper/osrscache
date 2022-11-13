#include "NpcManager.h"
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
	using NpcDefinition = net::runelite::cache::definitions::NpcDefinition;
	using NpcExporter = net::runelite::cache::definitions::exporters::NpcExporter;
	using NpcLoader = net::runelite::cache::definitions::loaders::NpcLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
	using IDClass = net::runelite::cache::util::IDClass;

	NpcManager::NpcManager(std::shared_ptr<Store> store) : store(store)
	{
	}

	void NpcManager::load()
	{
		std::shared_ptr<NpcLoader> loader = std::make_shared<NpcLoader>();

		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::CONFIGS);
		std::shared_ptr<Archive> archive = index->getArchive(ConfigType::NPC.getId());

		std::vector<signed char> archiveData = storage->loadArchive(archive);
		std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

		for (auto f : files->getFiles())
		{
			std::shared_ptr<NpcDefinition> npc = loader->load(f->getFileId(), f->getContents());
			npcs.emplace(f->getFileId(), npc);
		}
	}

	std::shared_ptr<Collection<std::shared_ptr<NpcDefinition>>> NpcManager::getNpcs()
	{
		return Collections::unmodifiableCollection(npcs.values());
	}

	std::shared_ptr<NpcDefinition> NpcManager::get(int npcId)
	{
		return npcs[npcId];
	}

	void NpcManager::dump(std::shared_ptr<File> out)
	{
		out->mkdirs();

		for (auto def : npcs)
		{
			std::shared_ptr<NpcExporter> exporter = std::make_shared<NpcExporter>(def->second);

			std::shared_ptr<File> targ = std::make_shared<File>(out, def->second.id + L".json");
			exporter->exportTo(targ);
		}
	}

	void NpcManager::java(std::shared_ptr<File> java)
	{
		java->mkdirs();
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.util.IDClass ids = net.runelite.cache.util.IDClass.create(java, "NpcID"); net.runelite.cache.util.IDClass nulls = net.runelite.cache.util.IDClass.create(java, "NullNpcID"))
		{
			IDClass ids = IDClass::create(java, L"NpcID");
			IDClass nulls = IDClass::create(java, L"NullNpcID");
			for (auto def : npcs)
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
}
