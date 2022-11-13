#include "ItemManagerTest.h"
#include "../../../../../main/java/net/runelite/cache/ItemManager.h"

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
const std::shared_ptr<org::slf4j::Logger> ItemManagerTest::logger = org::slf4j::LoggerFactory::getLogger(ItemManagerTest::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void test() throws java.io.IOException
	void ItemManagerTest::test()
	{
		std::shared_ptr<File> dumpDir = folder->newFolder(), javaDir = folder->newFolder();

		std::shared_ptr<Store> store = std::make_shared<Store>(StoreLocation::LOCATION);
		store->load();

		std::shared_ptr<ItemManager> dumper = std::make_shared<ItemManager>(store);
		dumper->load();
		dumper->export_Keyword(dumpDir);
		dumper->java(javaDir);

		logger->info(L"Dumped to {}, java {}", dumpDir, javaDir);
	}
}
