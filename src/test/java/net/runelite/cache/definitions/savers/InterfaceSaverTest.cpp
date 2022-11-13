#include "InterfaceSaverTest.h"
#include "../../../../../../../main/java/net/runelite/cache/definitions/savers/InterfaceSaver.h"

namespace net::runelite::cache::definitions::savers
{
	using File = java::io::File;
	using IndexType = net::runelite::cache::IndexType;
	using StoreLocation = net::runelite::cache::StoreLocation;
	using InterfaceDefinition = net::runelite::cache::definitions::InterfaceDefinition;
	using InterfaceLoader = net::runelite::cache::definitions::loaders::InterfaceLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
//	import static org.junit.Assert.assertArrayEquals;
	using Test = org::junit::Test;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testSave() throws Exception
	void InterfaceSaverTest::testSave()
	{
		std::shared_ptr<File> __super = StoreLocation::LOCATION;
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(super))
		{
			Store store = Store(base);
			store.load();

			std::shared_ptr<Storage> storage = store.getStorage();
			std::shared_ptr<Index> index = store.getIndex(IndexType::INTERFACES);
			std::shared_ptr<Archive> archive = index->getArchive(31);
			std::vector<signed char> archiveData = storage->loadArchive(archive);
			std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);
			std::shared_ptr<FSFile> file = files->findFile(76);
			std::vector<signed char> contents = file->getContents();

			std::shared_ptr<InterfaceDefinition> def = (std::make_shared<InterfaceLoader>())->load(0, contents);
			std::vector<signed char> b = (std::make_shared<InterfaceSaver>())->save(def);
			assertArrayEquals(contents, b);
		}
	}
}
