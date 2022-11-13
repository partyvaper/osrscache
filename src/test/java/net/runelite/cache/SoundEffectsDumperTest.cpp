#include "SoundEffectsDumperTest.h"
#include "../../../../../main/java/net/runelite/cache/IndexType.h"

namespace net::runelite::cache
{
	using Files = com::google::common::io::Files;
	using Gson = com::google::gson::Gson;
	using GsonBuilder = com::google::gson::GsonBuilder;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using Charset = java::nio::charset::Charset;
	using SoundEffectLoader = net::runelite::cache::definitions::loaders::sound::SoundEffectLoader;
	using SoundEffectDefinition = net::runelite::cache::definitions::sound::SoundEffectDefinition;
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
const std::shared_ptr<org::slf4j::Logger> SoundEffectsDumperTest::logger = org::slf4j::LoggerFactory::getLogger(SoundEffectsDumperTest::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void test() throws java.io.IOException
	void SoundEffectsDumperTest::test()
	{
		std::shared_ptr<File> dumpDir = folder->newFolder();
		int count = 0;

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(StoreLocation.LOCATION))
		{
			Store store = Store(StoreLocation::LOCATION);
			store.load();

			std::shared_ptr<Storage> storage = store.getStorage();
			std::shared_ptr<Index> index = store.getIndex(IndexType::SOUNDEFFECTS);

			for (auto archive : index->getArchives())
			{
				std::vector<signed char> contents = archive->decompress(storage->loadArchive(archive));

				std::shared_ptr<SoundEffectLoader> soundEffectLoader = std::make_shared<SoundEffectLoader>();
				std::shared_ptr<SoundEffectDefinition> soundEffect = soundEffectLoader->load(contents);

				Files::asCharSink(std::make_shared<File>(dumpDir, std::to_wstring(archive->getArchiveId()) + L".json"), Charset::defaultCharset()).write(gson->toJson(soundEffect));
				++count;
			}
		}

		logger->info(L"Dumped {} sound effects to {}", count, dumpDir);
	}
}
