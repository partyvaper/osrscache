#include "FrameDumper.h"
#include "../../../../../main/java/net/runelite/cache/IndexType.h"

namespace net::runelite::cache
{
	using Files = com::google::common::io::Files;
	using Gson = com::google::gson::Gson;
	using GsonBuilder = com::google::gson::GsonBuilder;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using Charset = java::nio::charset::Charset;
	using ArrayList = java::util::ArrayList;
	using List = java::util::List;
	using FrameDefinition = net::runelite::cache::definitions::FrameDefinition;
	using FramemapDefinition = net::runelite::cache::definitions::FramemapDefinition;
	using FrameLoader = net::runelite::cache::definitions::loaders::FrameLoader;
	using FramemapLoader = net::runelite::cache::definitions::loaders::FramemapLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
	using Ignore = org::junit::Ignore;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> FrameDumper::logger = org::slf4j::LoggerFactory::getLogger(FrameDumper::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void extract() throws java.io.IOException
	void FrameDumper::extract()
	{
		std::shared_ptr<File> __super = StoreLocation::LOCATION, outDir = folder->newFolder();

		int count = 0;

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(super))
		{
			Store store = Store(base);
			store.load();

			std::shared_ptr<Storage> storage = store.getStorage();
			std::shared_ptr<Index> frameIndex = store.getIndex(IndexType::ANIMATIONS);
			std::shared_ptr<Index> framemapIndex = store.getIndex(IndexType::SKELETONS);

			for (auto archive : frameIndex->getArchives())
			{
				std::vector<std::shared_ptr<FrameDefinition>> frames;

				std::vector<signed char> archiveData = storage->loadArchive(archive);

				std::shared_ptr<ArchiveFiles> archiveFiles = archive->getFiles(archiveData);
				for (auto archiveFile : archiveFiles->getFiles())
				{
					std::vector<signed char> contents = archiveFile->getContents();

					int framemapArchiveId = (contents[0] & 0xff) << 8 | contents[1] & 0xff;

					std::shared_ptr<Archive> framemapArchive = framemapIndex->getArchive(framemapArchiveId);
					archiveData = storage->loadArchive(framemapArchive);
					std::vector<signed char> framemapContents = framemapArchive->decompress(archiveData);

					std::shared_ptr<FramemapLoader> fmloader = std::make_shared<FramemapLoader>();
					std::shared_ptr<FramemapDefinition> framemap = fmloader->load(framemapArchive->getArchiveId(), framemapContents);

					std::shared_ptr<FrameLoader> frameLoader = std::make_shared<FrameLoader>();
					std::shared_ptr<FrameDefinition> frame = frameLoader->load(framemap, archiveFile->getFileId(), contents);

					frames.push_back(frame);
				}

				Files::asCharSink(std::make_shared<File>(outDir, std::to_wstring(archive->getArchiveId()) + L".json"), Charset::defaultCharset()).write(gson->toJson(frames));
				++count;
			}
		}

		logger->info(L"Dumped {} frames to {}", count, outDir);
	}
}
