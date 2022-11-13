#include "StoreLoadTest.h"

namespace net::runelite::cache::fs
{
	using Files = com::google::common::io::Files;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using StoreLocation = net::runelite::cache::StoreLocation;
	using Assert = org::junit::Assert;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testLoad() throws java.io.IOException
	void StoreLoadTest::testLoad()
	{
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (Store store = new Store(net.runelite.cache.StoreLocation.LOCATION))
		{
			Store store = Store(StoreLocation::LOCATION);
			store.load();
		}
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testSave() throws java.io.IOException
	void StoreLoadTest::testSave()
	{
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (Store store = new Store(net.runelite.cache.StoreLocation.LOCATION))
		{
			Store store = Store(StoreLocation::LOCATION);
			store.load();

			std::shared_ptr<File> testStoreFile = folder->newFolder();
			for (std::shared_ptr<File> f : StoreLocation::LOCATION->listFiles())
			{
				Files::copy(f, std::make_shared<File>(testStoreFile, f->getName()));
			}

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (Store testStore = new Store(testStoreFile))
			{
				Store testStore = Store(testStoreFile);
				testStore.load();

				Assert::assertTrue(store.equals(testStore));

				testStore.save();
			}

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (Store testStore = new Store(testStoreFile))
			{
				Store testStore = Store(testStoreFile);
				testStore.load();

				Assert::assertTrue(store.equals(testStore));
			}
		}
	}
}
