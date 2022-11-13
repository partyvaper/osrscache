#include "TitleDumper.h"
#include "../../../../../main/java/net/runelite/cache/IndexType.h"

namespace net::runelite::cache
{
	using File = java::io::File;
	using IOException = java::io::IOException;
	using Files = java::nio::file::Files;
	using Archive = net::runelite::cache::fs::Archive;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> TitleDumper::logger = org::slf4j::LoggerFactory::getLogger(TitleDumper::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void extract() throws java.io.IOException
	void TitleDumper::extract()
	{
		std::shared_ptr<File> __super = StoreLocation::LOCATION, outFile = folder->newFile();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(super))
		{
			Store store = Store(base);
			store.load();

			std::shared_ptr<Storage> storage = store.getStorage();
			std::shared_ptr<Index> index = store.getIndex(IndexType::BINARY);
			std::shared_ptr<Archive> archive = index->findArchiveByName(L"title.jpg");
			std::vector<signed char> contents = archive->decompress(storage->loadArchive(archive));

			Files::write(outFile->toPath(), contents);
		}

		logger->info(L"Dumped to {}", outFile);
	}
}
