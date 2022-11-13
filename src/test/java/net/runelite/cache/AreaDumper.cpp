#include "AreaDumper.h"
#include "../../../../../main/java/net/runelite/cache/AreaManager.h"

namespace net::runelite::cache
{
	using Files = com::google::common::io::Files;
	using Gson = com::google::gson::Gson;
	using GsonBuilder = com::google::gson::GsonBuilder;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using Charset = java::nio::charset::Charset;
	using AreaDefinition = net::runelite::cache::definitions::AreaDefinition;
	using Store = net::runelite::cache::fs::Store;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> AreaDumper::logger = org::slf4j::LoggerFactory::getLogger(AreaDumper::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void extract() throws java.io.IOException
	void AreaDumper::extract()
	{
		std::shared_ptr<File> __super = StoreLocation::LOCATION, outDir = folder->newFolder();

		int count = 0;

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(super))
		{
			Store store = Store(base);
			store.load();

			std::shared_ptr<AreaManager> areaManager = std::make_shared<AreaManager>(store);
			areaManager->load();

			for (auto area : areaManager->getAreas())
			{
				Files::asCharSink(std::make_shared<File>(outDir, std::to_wstring(area->id) + L".json"), Charset::defaultCharset()).write(gson->toJson(area));
				++count;
			}
		}

		logger->info(L"Dumped {} areas to {}", count, outDir);
	}
}
