#include "NpcManagerTest.h"
#include "../../../../../main/java/net/runelite/cache/NpcManager.h"

namespace net::runelite::cache
{
	using File = java::io::File;
	using IOException = java::io::IOException;
	using Store = net::runelite::cache::fs::Store;
	using Ignore = org::junit::Ignore;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> NpcManagerTest::logger = org::slf4j::LoggerFactory::getLogger(NpcManagerTest::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void test() throws java.io.IOException
	void NpcManagerTest::test()
	{
		std::shared_ptr<File> dumpDir = folder->newFolder(), javaDir = folder->newFolder();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(StoreLocation.LOCATION))
		{
			Store store = Store(StoreLocation::LOCATION);
			store.load();

			std::shared_ptr<NpcManager> dumper = std::make_shared<NpcManager>(store);
			dumper->load();
			dumper->dump(dumpDir);
			dumper->java(javaDir);
		}

		logger->info(L"Dumped to {}, java {}", dumpDir, javaDir);
	}
}
