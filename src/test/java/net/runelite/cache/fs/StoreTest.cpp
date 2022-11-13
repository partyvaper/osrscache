#include "StoreTest.h"
#include "../../../../../../main/java/net/runelite/cache/fs/Index.h"
#include "../../../../../../main/java/net/runelite/cache/fs/Archive.h"

namespace net::runelite::cache::fs
{
	using File = java::io::File;
	using IOException = java::io::IOException;
	using Random = java::util::Random;
	using StoreLocation = net::runelite::cache::StoreLocation;
	using FileData = net::runelite::cache::index::FileData;
	using Assert = org::junit::Assert;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testOneFile() throws java.io.IOException
	void StoreTest::testOneFile()
	{
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (Store store = new Store(folder.getRoot()))
		{
			Store store = Store(folder->getRoot());
			std::shared_ptr<Index> index = store.addIndex(0);
			std::shared_ptr<Archive> archive = index->addArchive(0);
			archive->setFileData(std::vector<std::shared_ptr<FileData>>(1));
			std::shared_ptr<FileData> fileData = archive->getFileData()[0] = std::make_shared<FileData>();
			fileData->setId(42);
			fileData->setNameHash(7);

			store.save();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (Store store2 = new Store(folder.getRoot()))
			{
				Store store2 = Store(folder->getRoot());
				store2.load();

				Assert::assertEquals(store, store2);
			}
		}
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testManyFiles() throws java.io.IOException
	void StoreTest::testManyFiles()
	{
		std::shared_ptr<Random> random = std::make_shared<Random>(42LL);
		std::shared_ptr<File> root = folder->newFolder();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (Store store = new Store(root))
		{
			Store store = Store(root);
			std::shared_ptr<Index> index = store.addIndex(0);
			std::shared_ptr<Archive> archive = index->addArchive(0);
			archive->setNameHash(random->nextInt());
			archive->setFileData(std::vector<std::shared_ptr<FileData>>(NUMBER_OF_FILES));

			for (int i = 0; i < NUMBER_OF_FILES; ++i)
			{
				std::vector<std::shared_ptr<FileData>> fileData = archive->getFileData();
				std::shared_ptr<FileData> file = fileData[i] = std::make_shared<FileData>();
				file->setId(i);
				file->setNameHash(random->nextInt());
			}

			store.save();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (Store store2 = new Store(root))
			{
				Store store2 = Store(root);
				store2.load();

				Assert::assertEquals(store, store2);
			}
		}
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testMultipleArchives() throws java.io.IOException
	void StoreTest::testMultipleArchives()
	{
		std::shared_ptr<Random> random = std::make_shared<Random>(43LL);
		std::shared_ptr<File> root = folder->newFolder();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (Store store = new Store(root))
		{
			Store store = Store(root);
			std::shared_ptr<Index> index = store.addIndex(0);
			std::shared_ptr<Index> index2 = store.addIndex(1);

			std::shared_ptr<Archive> archive = index->addArchive(0);
			archive->setNameHash(random->nextInt(std::numeric_limits<int>::max()));
			archive->setFileData(std::vector<std::shared_ptr<FileData>>(NUMBER_OF_FILES));

			std::shared_ptr<Archive> archive2 = index->addArchive(1);
			archive2->setFileData(std::vector<std::shared_ptr<FileData>>(NUMBER_OF_FILES));

			std::shared_ptr<Archive> archive3 = index2->addArchive(0);
			archive3->setFileData(std::vector<std::shared_ptr<FileData>>(NUMBER_OF_FILES));

			for (int i = 0; i < NUMBER_OF_FILES; ++i)
			{
				std::vector<std::shared_ptr<FileData>> fileData = archive->getFileData();
				std::shared_ptr<FileData> file = fileData[i] = std::make_shared<FileData>();
				file->setNameHash(random->nextInt(std::numeric_limits<int>::max()));
			}

			for (int i = 0; i < NUMBER_OF_FILES; ++i)
			{
				std::vector<std::shared_ptr<FileData>> fileData = archive2->getFileData();
				std::shared_ptr<FileData> file = fileData[i] = std::make_shared<FileData>();
				file->setNameHash(random->nextInt(std::numeric_limits<int>::max()));
			}

			for (int i = 0; i < NUMBER_OF_FILES; ++i)
			{
				std::vector<std::shared_ptr<FileData>> fileData = archive3->getFileData();
				std::shared_ptr<FileData> file = fileData[i] = std::make_shared<FileData>();
				file->setNameHash(random->nextInt(std::numeric_limits<int>::max()));
			}

			store.save();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (Store store2 = new Store(root))
			{
				Store store2 = Store(root);
				store2.load();

				Assert::assertEquals(store, store2);
			}
		}
	}
}
