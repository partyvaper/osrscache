#include "StructManagerTest.h"
#include "../../../../../main/java/net/runelite/cache/StructManager.h"

namespace net::runelite::cache
{
	using Files = com::google::common::io::Files;
	using Gson = com::google::gson::Gson;
	using GsonBuilder = com::google::gson::GsonBuilder;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using Charset = java::nio::charset::Charset;
	using Map = java::util::Map;
	using StructDefinition = net::runelite::cache::definitions::StructDefinition;
	using Store = net::runelite::cache::fs::Store;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> StructManagerTest::logger = org::slf4j::LoggerFactory::getLogger(StructManagerTest::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void test() throws java.io.IOException
	void StructManagerTest::test()
	{
		std::shared_ptr<File> dumpDir = folder->newFolder();
		int count = 0;

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(StoreLocation.LOCATION))
		{
			Store store = Store(StoreLocation::LOCATION);
			store.load();
			std::shared_ptr<StructManager> loader = std::make_shared<StructManager>(store);
			loader->load();

			for (auto struct_Keyword : loader->getStructs())
			{
				std::shared_ptr<StructDefinition> def = struct_Keyword.second;

				Files::asCharSink(std::make_shared<File>(dumpDir, struct_Keyword.first + L".json"), Charset::defaultCharset()).write(gson->toJson(def));
				++count;
			}
		}

		logger->info(L"Dumped {} structs to {}", count, dumpDir);
	}
}
