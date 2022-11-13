#include "TextureDumper.h"
#include "../../../../../main/java/net/runelite/cache/TextureManager.h"

namespace net::runelite::cache
{
	using Files = com::google::common::io::Files;
	using Gson = com::google::gson::Gson;
	using GsonBuilder = com::google::gson::GsonBuilder;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using Charset = java::nio::charset::Charset;
	using TextureDefinition = net::runelite::cache::definitions::TextureDefinition;
	using Store = net::runelite::cache::fs::Store;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> TextureDumper::logger = org::slf4j::LoggerFactory::getLogger(TextureDumper::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void extract() throws java.io.IOException
	void TextureDumper::extract()
	{
		std::shared_ptr<File> __super = StoreLocation::LOCATION, outDir = folder->newFolder();

		int count = 0;

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(super))
		{
			Store store = Store(base);
			store.load();

			std::shared_ptr<TextureManager> tm = std::make_shared<TextureManager>(store);
			tm->load();

			for (auto texture : tm->getTextures())
			{
				Files::asCharSink(std::make_shared<File>(outDir, texture->getId() + L".json"), Charset::defaultCharset()).write(gson->toJson(texture));
				++count;
			}
		}

		logger->info(L"Dumped {} textures to {}", count, outDir);
	}
}
