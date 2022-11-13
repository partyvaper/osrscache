#include "ModelDumperTest.h"
#include "../../../../../main/java/net/runelite/cache/IndexType.h"

namespace net::runelite::cache
{
	using Files = com::google::common::io::Files;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using ModelLoader = net::runelite::cache::definitions::loaders::ModelLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
	using Ignore = org::junit::Ignore;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> ModelDumperTest::logger = org::slf4j::LoggerFactory::getLogger(ModelDumperTest::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void test() throws java.io.IOException
	void ModelDumperTest::test()
	{
		std::shared_ptr<File> modelDir = folder->newFolder(L"models");
		int count = 0;

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(StoreLocation.LOCATION))
		{
			Store store = Store(StoreLocation::LOCATION);
			store.load();

			std::shared_ptr<Storage> storage = store.getStorage();
			std::shared_ptr<Index> index = store.getIndex(IndexType::MODELS);

			for (auto archive : index->getArchives())
			{
				std::vector<signed char> contents = archive->decompress(storage->loadArchive(archive));

				std::shared_ptr<ModelLoader> loader = std::make_shared<ModelLoader>();
				loader->load(archive->getArchiveId(), contents);

				Files::write(contents, std::make_shared<File>(modelDir, std::to_wstring(archive->getArchiveId()) + L".model"));
				++count;
			}
		}

		logger->info(L"Dumped {} models to {}", count, modelDir);
	}
}
