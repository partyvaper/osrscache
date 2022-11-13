#include "WorldMapDumperTest.h"
#include "../../../../../main/java/net/runelite/cache/IndexType.h"

namespace net::runelite::cache
{
	using Files = com::google::common::io::Files;
	using Gson = com::google::gson::Gson;
	using GsonBuilder = com::google::gson::GsonBuilder;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using Charset = java::nio::charset::Charset;
	using WorldMapDefinition = net::runelite::cache::definitions::WorldMapDefinition;
	using WorldMapLoader = net::runelite::cache::definitions::loaders::WorldMapLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> WorldMapDumperTest::logger = org::slf4j::LoggerFactory::getLogger(WorldMapDumperTest::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void extract() throws java.io.IOException
	void WorldMapDumperTest::extract()
	{
		std::shared_ptr<File> __super = StoreLocation::LOCATION, outDir = folder->newFolder();

		int count = 0;

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(super))
		{
			Store store = Store(base);
			store.load();

			std::shared_ptr<Storage> storage = store.getStorage();
			std::shared_ptr<Index> index = store.getIndex(IndexType::WORLDMAP_OLD);
			std::shared_ptr<Archive> archive = index->getArchive(0); // there is also archive 1/2, but their data format is not this

			std::vector<signed char> archiveData = storage->loadArchive(archive);
			std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

			for (auto file : files->getFiles())
			{
				std::shared_ptr<WorldMapLoader> loader = std::make_shared<WorldMapLoader>();
				std::shared_ptr<WorldMapDefinition> def = loader->load(file->getContents(), file->getFileId());

				Files::asCharSink(std::make_shared<File>(outDir, std::to_wstring(file->getFileId()) + L".json"), Charset::defaultCharset()).write(gson->toJson(def));
				++count;
			}
		}

		logger->info(L"Dumped {} world map data to {}", count, outDir);
	}
}
