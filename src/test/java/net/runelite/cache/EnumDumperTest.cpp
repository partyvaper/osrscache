#include "EnumDumperTest.h"
#include "../../../../../main/java/net/runelite/cache/IndexType.h"
#include "../../../../../main/java/net/runelite/cache/ConfigType.h"

namespace net::runelite::cache
{
	using Files = com::google::common::io::Files;
	using Gson = com::google::gson::Gson;
	using GsonBuilder = com::google::gson::GsonBuilder;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using Charset = java::nio::charset::Charset;
	using EnumDefinition = net::runelite::cache::definitions::EnumDefinition;
	using EnumLoader = net::runelite::cache::definitions::loaders::EnumLoader;
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
const std::shared_ptr<org::slf4j::Logger> EnumDumperTest::logger = org::slf4j::LoggerFactory::getLogger(EnumDumperTest::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void test() throws java.io.IOException
	void EnumDumperTest::test()
	{
		std::shared_ptr<File> dumpDir = folder->newFolder();
		int count = 0;

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(StoreLocation.LOCATION))
		{
			Store store = Store(StoreLocation::LOCATION);
			store.load();

			std::shared_ptr<Storage> storage = store.getStorage();
			std::shared_ptr<Index> index = store.getIndex(IndexType::CONFIGS);
			std::shared_ptr<Archive> archive = index->getArchive(ConfigType::ENUM.getId());

			std::vector<signed char> archiveData = storage->loadArchive(archive);
			std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

			std::shared_ptr<EnumLoader> loader = std::make_shared<EnumLoader>();

			for (auto file : files->getFiles())
			{
				std::vector<signed char> b = file->getContents();

				std::shared_ptr<EnumDefinition> def = loader->load(file->getFileId(), b);

				if (def != nullptr)
				{
					Files::asCharSink(std::make_shared<File>(dumpDir, std::to_wstring(file->getFileId()) + L".json"), Charset::defaultCharset()).write(gson->toJson(def));
					++count;
				}
			}
		}

		logger->info(L"Dumped {} enums to {}", count, dumpDir);
	}
}
