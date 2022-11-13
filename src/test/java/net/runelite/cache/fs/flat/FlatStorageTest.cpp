#include "FlatStorageTest.h"

namespace net::runelite::cache::fs::flat
{
	using File = java::io::File;
	using Archive = net::runelite::cache::fs::Archive;
	using Container = net::runelite::cache::fs::Container;
	using Index = net::runelite::cache::fs::Index;
	using Store = net::runelite::cache::fs::Store;
	using DiskStorage = net::runelite::cache::fs::jagex::DiskStorage;
	using FileData = net::runelite::cache::index::FileData;
	using Test = org::junit::Test;
//	import static org.junit.Assert.*;
	using Rule = org::junit::Rule;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testSaveArchive() throws Exception
	void FlatStorageTest::testSaveArchive()
	{
		std::shared_ptr<File> file = folder->newFolder();
		std::shared_ptr<DiskStorage> storage = std::make_shared<DiskStorage>(file);
		std::shared_ptr<Archive> archive;
		std::shared_ptr<Archive> archive2;
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(storage))
		{
			Store store = Store(storage);
			std::shared_ptr<Index> index = store.addIndex(0);
			archive = index->addArchive(0);
			archive2 = index->addArchive(1);

			std::vector<std::shared_ptr<FileData>> fileData(1);
			archive->setFileData(fileData);
			fileData[0] = std::make_shared<FileData>();

			std::vector<std::shared_ptr<FileData>> fileData2(1);
			archive2->setFileData(fileData2);
			fileData2[0] = std::make_shared<FileData>();

			std::vector<signed char> data = (std::wstring(L"test")).getBytes();
			std::shared_ptr<Container> container = std::make_shared<Container>(archive->getCompression(), -1);
			container->compress(data, std::vector<int>());
			std::vector<signed char> compressedData = container->data;
			storage->saveArchive(archive, compressedData);

			container = std::make_shared<Container>(archive->getCompression(), 42);
			container->compress(data, std::vector<int>());
			compressedData = container->data;
			archive2->setRevision(42);
			storage->saveArchive(archive2, compressedData);

			store.save();
		}

		storage = std::make_shared<DiskStorage>(file);
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(storage))
		{
			Store store = Store(storage);
			store.load();
			std::shared_ptr<Index> index = store.findIndex(0);
			std::shared_ptr<Archive> archive2_1 = index->getArchive(0);
			std::shared_ptr<Archive> archive2_2 = index->getArchive(1);

			std::vector<signed char> comprsesedData = storage->loadArchive(archive2_1);
			std::vector<signed char> data = archive2_1->decompress(comprsesedData);
			assertArrayEquals((std::wstring(L"test")).getBytes(), data);
			assertEquals(archive->getCrc(), archive2_1->getCrc());
			assertEquals(archive->getRevision(), archive2_1->getRevision());

			comprsesedData = storage->loadArchive(archive2_2);
			data = archive2_2->decompress(comprsesedData);
			assertArrayEquals((std::wstring(L"test")).getBytes(), data);
			assertEquals(archive2->getCrc(), archive2_2->getCrc());
			assertEquals(archive2->getRevision(), archive2_2->getRevision());
		}
	}
}
