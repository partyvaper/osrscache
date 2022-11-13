#include "MapImageDumperTest.h"
#include "../../../../../main/java/net/runelite/cache/MapImageDumper.h"

namespace net::runelite::cache
{
	using BufferedImage = java::awt::image::BufferedImage;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using ImageIO = javax::imageio::ImageIO;
	using Store = net::runelite::cache::fs::Store;
	using Region = net::runelite::cache::region::Region;
	using RegionLoader = net::runelite::cache::region::RegionLoader;
	using XteaKeyManager = net::runelite::cache::util::XteaKeyManager;
	using Ignore = org::junit::Ignore;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> MapImageDumperTest::logger = org::slf4j::LoggerFactory::getLogger(MapImageDumperTest::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void dumpMap() throws java.io.IOException
	void MapImageDumperTest::dumpMap()
	{
		std::shared_ptr<File> __super = StoreLocation::LOCATION, outDir = folder->newFolder();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(super))
		{
			Store store = Store(base);
			store.load();

			std::shared_ptr<XteaKeyManager> keyManager = std::make_shared<XteaKeyManager>();
			keyManager->loadKeys(nullptr);

			std::shared_ptr<MapImageDumper> dumper = std::make_shared<MapImageDumper>(store, keyManager);
			dumper->load();

			for (int i = 0; i < Region::Z; ++i)
			{
				std::shared_ptr<BufferedImage> image = dumper->drawMap(i);

				std::shared_ptr<File> imageFile = std::make_shared<File>(outDir, L"img-" + std::to_wstring(i) + L".png");

				ImageIO::write(image, L"png", imageFile);
				logger->info(L"Wrote image {}", imageFile);
			}
		}
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void dumpRegions() throws Exception
	void MapImageDumperTest::dumpRegions()
	{
		std::shared_ptr<File> __super = StoreLocation::LOCATION, outDir = folder->newFolder();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(super))
		{
			Store store = Store(base);
			store.load();

			std::shared_ptr<XteaKeyManager> keyManager = std::make_shared<XteaKeyManager>();
			keyManager->loadKeys(nullptr);

			std::shared_ptr<RegionLoader> regionLoader = std::make_shared<RegionLoader>(store, keyManager);
			regionLoader->loadRegions();

			std::shared_ptr<MapImageDumper> dumper = std::make_shared<MapImageDumper>(store, regionLoader);
			dumper->load();

			int z = 0;
			for (auto region : regionLoader->getRegions())
			{
				std::shared_ptr<File> imageFile = std::make_shared<File>(outDir, L"img-" + std::to_wstring(z) + L"-" + std::to_wstring(region->getRegionID()) + L".png");
				std::shared_ptr<BufferedImage> image = dumper->drawRegion(region, z);
				ImageIO::write(image, L"png", imageFile);
			}
		}
	}
}
