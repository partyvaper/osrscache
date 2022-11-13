#include "ObjectManagerTest.h"
#include "../../../../../main/java/net/runelite/cache/ObjectManager.h"

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
const std::shared_ptr<org::slf4j::Logger> ObjectManagerTest::logger = org::slf4j::LoggerFactory::getLogger(ObjectManagerTest::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void test() throws java.io.IOException
	void ObjectManagerTest::test()
	{
		std::shared_ptr<File> dumpDir = folder->newFolder(), javaDir = folder->newFolder();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(StoreLocation.LOCATION))
		{
			Store store = Store(StoreLocation::LOCATION);
			store.load();

			std::shared_ptr<ObjectManager> dumper = std::make_shared<ObjectManager>(store);
			dumper->load();
			dumper->dump(dumpDir);
			dumper->java(javaDir);
		}

		logger->info(L"Dumped to {}, java {}", dumpDir, javaDir);
	}
}
