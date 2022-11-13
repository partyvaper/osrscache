#include "ObjectManager.h"
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
	using ObjectDefinition = net::runelite::cache::definitions::ObjectDefinition;
	using ObjectExporter = net::runelite::cache::definitions::exporters::ObjectExporter;
	using ObjectLoader = net::runelite::cache::definitions::loaders::ObjectLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
	using IDClass = net::runelite::cache::util::IDClass;

	ObjectManager::ObjectManager(std::shared_ptr<Store> store) : store(store)
	{
	}

	void ObjectManager::load()
	{
		std::shared_ptr<ObjectLoader> loader = std::make_shared<ObjectLoader>();

		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::CONFIGS);
		std::shared_ptr<Archive> archive = index->getArchive(ConfigType::OBJECT.getId());

		std::vector<signed char> archiveData = storage->loadArchive(archive);
		std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

		for (auto f : files->getFiles())
		{
			std::shared_ptr<ObjectDefinition> def = loader->load(f->getFileId(), f->getContents());
			objects.emplace(f->getFileId(), def);
		}
	}

	std::shared_ptr<Collection<std::shared_ptr<ObjectDefinition>>> ObjectManager::getObjects()
	{
		return Collections::unmodifiableCollection(objects.values());
	}

	std::shared_ptr<ObjectDefinition> ObjectManager::getObject(int id)
	{
		return objects[id];
	}

	void ObjectManager::dump(std::shared_ptr<File> out)
	{
		out->mkdirs();

		for (auto def : objects)
		{
			std::shared_ptr<ObjectExporter> exporter = std::make_shared<ObjectExporter>(def->second);

			std::shared_ptr<File> targ = std::make_shared<File>(out, def->second.getId() + L".json");
			exporter->exportTo(targ);
		}
	}

	void ObjectManager::java(std::shared_ptr<File> java)
	{
		java->mkdirs();
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.util.IDClass ids = net.runelite.cache.util.IDClass.create(java, "ObjectID"); net.runelite.cache.util.IDClass nulls = net.runelite.cache.util.IDClass.create(java, "NullObjectID"))
		{
			IDClass ids = IDClass::create(java, L"ObjectID");
			IDClass nulls = IDClass::create(java, L"NullObjectID");
			for (auto def : objects)
			{
				if (L"null" == def->second.getName())
				{
					nulls.add(def->second.getName(), def->second.getId());
				}
				else
				{
					ids.add(def->second.getName(), def->second.getId());
				}
			}
		}
	}
}
