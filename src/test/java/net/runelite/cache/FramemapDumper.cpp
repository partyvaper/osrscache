#include "FramemapDumper.h"
#include "../../../../../main/java/net/runelite/cache/IndexType.h"

namespace net::runelite::cache
{
	using Files = com::google::common::io::Files;
	using Gson = com::google::gson::Gson;
	using GsonBuilder = com::google::gson::GsonBuilder;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using Charset = java::nio::charset::Charset;
	using FramemapDefinition = net::runelite::cache::definitions::FramemapDefinition;
	using FramemapLoader = net::runelite::cache::definitions::loaders::FramemapLoader;
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
const std::shared_ptr<org::slf4j::Logger> FramemapDumper::logger = org::slf4j::LoggerFactory::getLogger(FramemapDumper::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void extract() throws java.io.IOException
	void FramemapDumper::extract()
	{
		std::shared_ptr<File> __super = StoreLocation::LOCATION, outDir = folder->newFolder();

		int count = 0;

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(super))
		{
			Store store = Store(base);
			store.load();

			std::shared_ptr<Storage> storage = store.getStorage();
			std::shared_ptr<Index> index = store.getIndex(IndexType::SKELETONS);

			for (auto archive : index->getArchives())
			{
				std::vector<signed char> archiveData = storage->loadArchive(archive);
				std::vector<signed char> contents = archive->decompress(archiveData);

				std::shared_ptr<FramemapLoader> loader = std::make_shared<FramemapLoader>();
				std::shared_ptr<FramemapDefinition> framemap = loader->load(0, contents);

				Files::asCharSink(std::make_shared<File>(outDir, std::to_wstring(archive->getArchiveId()) + L".json"), Charset::defaultCharset()).write(gson->toJson(framemap));
				++count;
			}
		}

		logger->info(L"Dumped {} framemaps to {}", count, outDir);
	}
}
