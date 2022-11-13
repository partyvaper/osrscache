#include "HeightMapDumperTest.h"
#include "../../../../../main/java/net/runelite/cache/HeightMapDumper.h"

namespace net::runelite::cache
{
	using BufferedImage = java::awt::image::BufferedImage;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using ImageIO = javax::imageio::ImageIO;
	using Store = net::runelite::cache::fs::Store;
	using Rule = org::junit::Rule;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> HeightMapDumperTest::logger = org::slf4j::LoggerFactory::getLogger(HeightMapDumperTest::class);

	void HeightMapDumperTest::extract()
	{
		std::shared_ptr<File> __super = StoreLocation::LOCATION, outDir = folder->newFolder();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(super))
		{
			Store store = Store(base);
			store.load();

			std::shared_ptr<HeightMapDumper> dumper = std::make_shared<HeightMapDumper>(store);
			dumper->load(nullptr);

			std::shared_ptr<BufferedImage> image = dumper->drawHeightMap(0);

			std::shared_ptr<File> imageFile = std::make_shared<File>(outDir, L"heightmap-0.png");

			ImageIO::write(image, L"png", imageFile);
			logger->info(L"Wrote image {}", imageFile);
		}
	}
}
