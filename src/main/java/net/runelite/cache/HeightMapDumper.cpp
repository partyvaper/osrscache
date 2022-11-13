#include "HeightMapDumper.h"

namespace net::runelite::cache
{
	using Color = java::awt::Color;
	using BufferedImage = java::awt::image::BufferedImage;
	using IOException = java::io::IOException;
	using Store = net::runelite::cache::fs::Store;
	using Region = net::runelite::cache::region::Region;
	using RegionLoader = net::runelite::cache::region::RegionLoader;
	using KeyProvider = net::runelite::cache::util::KeyProvider;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> HeightMapDumper::logger = org::slf4j::LoggerFactory::getLogger(HeightMapDumper::class);

	HeightMapDumper::HeightMapDumper(std::shared_ptr<Store> store) : store(store)
	{
	}

	void HeightMapDumper::load(std::shared_ptr<KeyProvider> keyProvider)
	{
		regionLoader = std::make_shared<RegionLoader>(store, keyProvider);
		regionLoader->loadRegions();
		regionLoader->calculateBounds();
	}

	std::shared_ptr<BufferedImage> HeightMapDumper::drawHeightMap(int z)
	{
		int minX = regionLoader->getLowestX()->getBaseX();
		int minY = regionLoader->getLowestY()->getBaseY();

		int maxX = regionLoader->getHighestX()->getBaseX() + Region::X;
		int maxY = regionLoader->getHighestY()->getBaseY() + Region::Y;

		int dimX = maxX - minX;
		int dimY = maxY - minY;

		dimX *= MAP_SCALE;
		dimY *= MAP_SCALE;

		logger->info(L"Map image dimensions: {}px x {}px, {}px per map square ({} MB)", dimX, dimY, MAP_SCALE, (dimX * dimY / 1024 / 1024));

		std::shared_ptr<BufferedImage> image = std::make_shared<BufferedImage>(dimX, dimY, BufferedImage::TYPE_INT_RGB);
		draw(image, z);
		return image;
	}

	void HeightMapDumper::draw(std::shared_ptr<BufferedImage> image, int z)
	{
		int max = std::numeric_limits<int>::min();
		int min = std::numeric_limits<int>::max();

		for (auto region : regionLoader->getRegions())
		{
			int baseX = region->getBaseX();
			int baseY = region->getBaseY();

			// to pixel X
			int drawBaseX = baseX - regionLoader->getLowestX()->getBaseX();

			// to pixel Y. top most y is 0, but the top most
			// region has the greatest y, so invert
			int drawBaseY = regionLoader->getHighestY()->getBaseY() - baseY;

			for (int x = 0; x < Region::X; ++x)
			{
				int drawX = drawBaseX + x;

				for (int y = 0; y < Region::Y; ++y)
				{
					int drawY = drawBaseY + (Region::Y - 1 - y);

					int height = region->getTileHeight(z, x, y);
					if (height > max)
					{
						max = height;
					}
					if (height < min)
					{
						min = height;
					}

					int rgb = toColor(height);

					drawMapSquare(image, drawX, drawY, rgb);
				}
			}
		}
		std::wcout << L"max " << max << std::endl;
		std::wcout << L"min " << min << std::endl;
	}

	int HeightMapDumper::toColor(int height)
	{
		// height seems to be between -2040 and 0, inclusive
		height = -height;
		// Convert to between 0 and 1
		float color = static_cast<float>(height) / MAX_HEIGHT;

		assert(color >= 0.0f && color <= 1.0f);

		return (std::make_shared<Color>(color, color, color))->getRGB();
	}

	void HeightMapDumper::drawMapSquare(std::shared_ptr<BufferedImage> image, int x, int y, int rgb)
	{
		x *= MAP_SCALE;
		y *= MAP_SCALE;

		for (int i = 0; i < MAP_SCALE; ++i)
		{
			for (int j = 0; j < MAP_SCALE; ++j)
			{
				image->setRGB(x + i, y + j, rgb);
			}
		}
	}
}
