#include "MapImageDumper.h"
#include "TextureManager.h"
#include "IndexType.h"
#include "ConfigType.h"

namespace net::runelite::cache
{
	using Color = java::awt::Color;
	using Graphics2D = java::awt::Graphics2D;
	using BufferedImage = java::awt::image::BufferedImage;
	using File = java::io::File;
	using FileInputStream = java::io::FileInputStream;
	using IOException = java::io::IOException;
	using ArrayList = java::util::ArrayList;
	using Arrays = java::util::Arrays;
	using HashMap = java::util::HashMap;
	using List = java::util::List;
	using Map = java::util::Map;
	using ImageIO = javax::imageio::ImageIO;
	using Getter = lombok::Getter;
	using Setter = lombok::Setter;
	using Accessors = lombok::experimental::Accessors;
	using Slf4j = lombok::extern_Keyword::slf4j::Slf4j;
	using AreaDefinition = net::runelite::cache::definitions::AreaDefinition;
	using ObjectDefinition = net::runelite::cache::definitions::ObjectDefinition;
	using OverlayDefinition = net::runelite::cache::definitions::OverlayDefinition;
	using SpriteDefinition = net::runelite::cache::definitions::SpriteDefinition;
	using UnderlayDefinition = net::runelite::cache::definitions::UnderlayDefinition;
	using OverlayLoader = net::runelite::cache::definitions::loaders::OverlayLoader;
	using SpriteLoader = net::runelite::cache::definitions::loaders::SpriteLoader;
	using UnderlayLoader = net::runelite::cache::definitions::loaders::UnderlayLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
	using RSTextureProvider = net::runelite::cache::item::RSTextureProvider;
	using JagexColor = net::runelite::cache::models::JagexColor;
	using Location = net::runelite::cache::region::Location;
	using Position = net::runelite::cache::region::Position;
	using Region = net::runelite::cache::region::Region;
	using RegionLoader = net::runelite::cache::region::RegionLoader;
	using BigBufferedImage = net::runelite::cache::util::BigBufferedImage;
	using KeyProvider = net::runelite::cache::util::KeyProvider;
	using XteaKeyManager = net::runelite::cache::util::XteaKeyManager;
	using CommandLine = org::apache::commons::cli::CommandLine;
	using CommandLineParser = org::apache::commons::cli::CommandLineParser;
	using DefaultParser = org::apache::commons::cli::DefaultParser;
	using Option = org::apache::commons::cli::Option;
	using Options = org::apache::commons::cli::Options;
	using ParseException = org::apache::commons::cli::ParseException;
std::vector<int> MapImageDumper::colorPalette = net::runelite::cache::models::JagexColor::createPalette(net::runelite::cache::models::JagexColor::BRIGHTNESS_MIN);
std::vector<std::vector<int>> MapImageDumper::TILE_SHAPE_2D =
{
	std::vector<int> {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	std::vector<int> {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	std::vector<int> {1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1},
	std::vector<int> {1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
	std::vector<int> {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
	std::vector<int> {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	std::vector<int> {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	std::vector<int> {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
	std::vector<int> {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
	std::vector<int> {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1},
	std::vector<int> {1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
	std::vector<int> {0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
	std::vector<int> {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1}
};
std::vector<std::vector<int>> MapImageDumper::TILE_ROTATION_2D =
{
	std::vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
	std::vector<int> {12, 8, 4, 0, 13, 9, 5, 1, 14, 10, 6, 2, 15, 11, 7, 3},
	std::vector<int> {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
	std::vector<int> {3, 7, 11, 15, 2, 6, 10, 14, 1, 5, 9, 13, 0, 4, 8, 12}
};

	MapImageDumper::MapImageDumper(std::shared_ptr<Store> store, std::shared_ptr<KeyProvider> keyProvider) : MapImageDumper(store, std::make_shared<RegionLoader>(store, keyProvider))
	{
	}

	MapImageDumper::MapImageDumper(std::shared_ptr<Store> store, std::shared_ptr<RegionLoader> regionLoader) : store(store), regionLoader(regionLoader), areas(std::make_shared<AreaManager>(store)), sprites(std::make_shared<SpriteManager>(store)), objectManager(std::make_shared<ObjectManager>(store))
	{
	}

	void MapImageDumper::main(std::vector<std::wstring> &args)
	{
		std::shared_ptr<Options> options = std::make_shared<Options>();
		options->addOption(Option::builder().longOpt(L"cachedir").hasArg().required().build());
		options->addOption(Option::builder().longOpt(L"xteapath").hasArg().required().build());
		options->addOption(Option::builder().longOpt(L"outputdir").hasArg().required().build());

		std::shared_ptr<CommandLineParser> parser = std::make_shared<DefaultParser>();
		std::shared_ptr<CommandLine> cmd;
		try
		{
			cmd = parser->parse(options, args);
		}
		catch (const ParseException &ex)
		{
			System::err::println(L"Error parsing command line options: " + ex->getMessage());
			exit(-1);
			return;
		}

		const std::wstring cacheDirectory = cmd->getOptionValue(L"cachedir");
		const std::wstring xteaJSONPath = cmd->getOptionValue(L"xteapath");
		const std::wstring outputDirectory = cmd->getOptionValue(L"outputdir");

		std::shared_ptr<XteaKeyManager> xteaKeyManager = std::make_shared<XteaKeyManager>();
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (java.io.FileInputStream fin = new java.io.FileInputStream(xteaJSONPath))
		{
			FileInputStream fin = FileInputStream(xteaJSONPath);
			xteaKeyManager->loadKeys(fin);
		}

		std::shared_ptr<File> __super = std::make_shared<File>(cacheDirectory);
		std::shared_ptr<File> outDir = std::make_shared<File>(outputDirectory);
		outDir->mkdirs();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(super))
		{
			Store store = Store(base);
			store.load();

			std::shared_ptr<MapImageDumper> dumper = std::make_shared<MapImageDumper>(store, xteaKeyManager);
			dumper->load();

			for (int i = 0; i < Region::Z; ++i)
			{
				std::shared_ptr<BufferedImage> image = dumper->drawMap(i);

				std::shared_ptr<File> imageFile = std::make_shared<File>(outDir, L"img-" + std::to_wstring(i) + L".png");

				ImageIO::write(image, L"png", imageFile);
				log::info(L"Wrote image {}", imageFile);
			}
		}
	}

	double MapImageDumper::random()
	{
		// the client would use a random value here, but we prefer determinism
		return 0.5;
	}

	std::shared_ptr<MapImageDumper> MapImageDumper::setBrightness(double brightness)
	{
		colorPalette = JagexColor::createPalette(brightness);
		return shared_from_this();
	}

	std::shared_ptr<MapImageDumper> MapImageDumper::load()
	{
		loadUnderlays(store);
		loadOverlays(store);
		objectManager->load();

		std::shared_ptr<TextureManager> textureManager = std::make_shared<TextureManager>(store);
		textureManager->load();
		rsTextureProvider = std::make_shared<RSTextureProvider>(textureManager, sprites);

		loadRegions();
		areas->load();
		sprites->load();
		loadSprites();

		return shared_from_this();
	}

	std::shared_ptr<BufferedImage> MapImageDumper::drawMap(int z)
	{
		int minX = regionLoader->getLowestX()->getBaseX();
		int minY = regionLoader->getLowestY()->getBaseY();

		int maxX = regionLoader->getHighestX()->getBaseX() + Region::X;
		int maxY = regionLoader->getHighestY()->getBaseY() + Region::Y;

		int dimX = maxX - minX;
		int dimY = maxY - minY;

		int pixelsX = dimX * MAP_SCALE;
		int pixelsY = dimY * MAP_SCALE;

		log::info(L"Map image dimensions: {}px x {}px, {}px per map square ({} MB). Max memory: {}mb", pixelsX, pixelsY, MAP_SCALE, (pixelsX * pixelsY * 3 / 1024 / 1024), Runtime::getRuntime().maxMemory() / 1024LL / 1024LL);

		std::shared_ptr<BufferedImage> image;
		if (lowMemory)
		{
			image = BigBufferedImage::create(pixelsX, pixelsY, transparency ? BufferedImage::TYPE_INT_ARGB : BufferedImage::TYPE_INT_RGB);
		}
		else
		{
			image = std::make_shared<BufferedImage>(pixelsX, pixelsY, transparency ? BufferedImage::TYPE_INT_ARGB : BufferedImage::TYPE_INT_RGB);
		}

		drawMap(image, z);
		drawObjects(image, z);
		drawMapIcons(image, z);

		return image;
	}

	void MapImageDumper::drawNeighborObjects(std::shared_ptr<BufferedImage> image, int rx, int ry, int dx, int dy, int z)
	{
		std::shared_ptr<Region> neighbor = regionLoader->findRegionForRegionCoordinates(rx + dx, ry + dy);
		if (neighbor == nullptr)
		{
			return;
		}

		drawObjects(image, Region::X * dx, Region::Y * -dy, neighbor, z);
	}

	std::shared_ptr<BufferedImage> MapImageDumper::drawRegion(std::shared_ptr<Region> region, int z)
	{
		int pixelsX = Region::X * MAP_SCALE;
		int pixelsY = Region::Y * MAP_SCALE;

		std::shared_ptr<BufferedImage> image = std::make_shared<BufferedImage>(pixelsX, pixelsY, transparency ? BufferedImage::TYPE_INT_ARGB : BufferedImage::TYPE_INT_RGB);

		drawMap(image, 0, 0, z, region);

		drawNeighborObjects(image, region->getRegionX(), region->getRegionY(), -1, -1, z);
		drawNeighborObjects(image, region->getRegionX(), region->getRegionY(), -1, 0, z);
		drawNeighborObjects(image, region->getRegionX(), region->getRegionY(), -1, 1, z);
		drawNeighborObjects(image, region->getRegionX(), region->getRegionY(), 0, -1, z);
		drawObjects(image, 0, 0, region, z);
		drawNeighborObjects(image, region->getRegionX(), region->getRegionY(), 0, 1, z);
		drawNeighborObjects(image, region->getRegionX(), region->getRegionY(), 1, -1, z);
		drawNeighborObjects(image, region->getRegionX(), region->getRegionY(), 1, 0, z);
		drawNeighborObjects(image, region->getRegionX(), region->getRegionY(), 1, 1, z);
		drawMapIcons(image, 0, 0, region, z);

		return image;
	}

	void MapImageDumper::drawMap(std::shared_ptr<BufferedImage> image, int drawBaseX, int drawBaseY, int z, std::shared_ptr<Region> region)
	{
		if (!renderMap)
		{
			return;
		}

		std::vector<std::vector<std::vector<int>>> map(4);

		for (int x = 0; x < Region::X; ++x)
		{
			for (int y = 0; y < Region::Y; ++y)
			{
				bool isBridge = (region->getTileSetting(1, x, Region::Y - y - 1) & 2) != 0;
				int tileZ = z + (isBridge ? 1 : 0);
				if (tileZ >= Region::Z)
				{
					continue;
				}

				int tileSetting = region->getTileSetting(z, x, Region::Y - y - 1);
				if ((tileSetting & 24) == 0)
				{
					if (z == 0 && isBridge)
					{
						drawTile(image, map, region, drawBaseX, drawBaseY, 0, x, y);
					}
					drawTile(image, map, region, drawBaseX, drawBaseY, tileZ, x, y);
				}

				if (tileZ < 3)
				{
					int upTileSetting = region->getTileSetting(z + 1, x, Region::Y - y - 1);
					if ((upTileSetting & 8) != 0)
					{
						drawTile(image, map, region, drawBaseX, drawBaseY, tileZ + 1, x, y);
					}
				}
			}
		}
	}

	void MapImageDumper::drawMap(std::shared_ptr<BufferedImage> image, int z)
	{
		for (auto region : regionLoader->getRegions())
		{
			int baseX = region->getBaseX();
			int baseY = region->getBaseY();

			// to pixel X
			int drawBaseX = baseX - regionLoader->getLowestX()->getBaseX();

			// to pixel Y. top most y is 0, but the top most
			// region has the greatest y, so invert
			int drawBaseY = regionLoader->getHighestY()->getBaseY() - baseY;

			drawMap(image, drawBaseX, drawBaseY, z, region);
		}
	}

	void MapImageDumper::drawTile(std::shared_ptr<BufferedImage> to, std::vector<std::vector<std::vector<int>>> &planes, std::shared_ptr<Region> region, int drawBaseX, int drawBaseY, int z, int x, int y)
	{
		std::vector<std::vector<int>> pixels = planes[z];

		if (pixels.empty())
		{
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: pixels = planes[z] = new int[net.runelite.cache.region.Region.X * MAP_SCALE][net.runelite.cache.region.Region.Y * MAP_SCALE];
			pixels = planes[z] = RectangularVectors::RectangularIntVector(Region::X * MAP_SCALE, Region::Y * MAP_SCALE);
			drawMap(pixels, region, z);
		}

		for (int i = 0; i < MAP_SCALE; ++i)
		{
			for (int j = 0; j < MAP_SCALE; ++j)
			{
				int argb = pixels[x * MAP_SCALE + i][y * MAP_SCALE + j];
				if (argb != 0)
				{
					to->setRGB(drawBaseX * MAP_SCALE + x * MAP_SCALE + i, drawBaseY * MAP_SCALE + y * MAP_SCALE + j, argb);
				}
			}
		}
	}

	void MapImageDumper::drawMap(std::vector<std::vector<int>> &pixels, std::shared_ptr<Region> region, int z)
	{
		int baseX = region->getBaseX();
		int baseY = region->getBaseY();

		int len = Region::X + BLEND * 2;
		std::vector<int> hues(len);
		std::vector<int> sats(len);
		std::vector<int> light(len);
		std::vector<int> mul(len);
		std::vector<int> num(len);

		bool hasLeftRegion = regionLoader->findRegionForWorldCoordinates(baseX - 1, baseY) != nullptr;
		bool hasRightRegion = regionLoader->findRegionForWorldCoordinates(baseX + Region::X, baseY) != nullptr;
		bool hasUpRegion = regionLoader->findRegionForWorldCoordinates(baseX, baseY + Region::Y) != nullptr;
		bool hasDownRegion = regionLoader->findRegionForWorldCoordinates(baseX, baseY - 1) != nullptr;

		for (int xi = (hasLeftRegion ? -BLEND * 2 : -BLEND); xi < Region::X + (hasRightRegion ? BLEND * 2 : BLEND); ++xi)
		{
			for (int yi = (hasDownRegion ? -BLEND : 0); yi < Region::Y + (hasUpRegion ? BLEND : 0); ++yi)
			{
				int xr = xi + BLEND;
				if (xr >= (hasLeftRegion ? -BLEND : 0) && xr < Region::X + (hasRightRegion ? BLEND : 0))
				{
					std::shared_ptr<Region> r = regionLoader->findRegionForWorldCoordinates(baseX + xr, baseY + yi);
					if (r != nullptr)
					{
						int underlayId = r->getUnderlayId(z, convert(xr), convert(yi));
						if (underlayId > 0)
						{
							std::shared_ptr<UnderlayDefinition> underlay = findUnderlay(underlayId - 1);
							hues[yi + BLEND] += underlay->getHue();
							sats[yi + BLEND] += underlay->getSaturation();
							light[yi + BLEND] += underlay->getLightness();
							mul[yi + BLEND] += underlay->getHueMultiplier();
							num[yi + BLEND]++;
						}
					}
				}

				int xl = xi - BLEND;
				if (xl >= (hasLeftRegion ? -BLEND : 0) && xl < Region::X + (hasRightRegion ? BLEND : 0))
				{
					std::shared_ptr<Region> r = regionLoader->findRegionForWorldCoordinates(baseX + xl, baseY + yi);
					if (r != nullptr)
					{
						int underlayId = r->getUnderlayId(z, convert(xl), convert(yi));
						if (underlayId > 0)
						{
							std::shared_ptr<UnderlayDefinition> underlay = findUnderlay(underlayId - 1);
							hues[yi + BLEND] -= underlay->getHue();
							sats[yi + BLEND] -= underlay->getSaturation();
							light[yi + BLEND] -= underlay->getLightness();
							mul[yi + BLEND] -= underlay->getHueMultiplier();
							num[yi + BLEND]--;
						}
					}
				}
			}

			if (xi >= 0 && xi < Region::X)
			{
				int runningHues = 0;
				int runningSat = 0;
				int runningLight = 0;
				int runningMultiplier = 0;
				int runningNumber = 0;

				for (int yi = (hasDownRegion ? -BLEND * 2 : -BLEND); yi < Region::Y + (hasUpRegion ? BLEND * 2 : BLEND); ++yi)
				{
					int yu = yi + BLEND;
					if (yu >= (hasDownRegion ? -BLEND : 0) && yu < Region::Y + (hasUpRegion ? BLEND : 0))
					{
						runningHues += hues[yu + BLEND];
						runningSat += sats[yu + BLEND];
						runningLight += light[yu + BLEND];
						runningMultiplier += mul[yu + BLEND];
						runningNumber += num[yu + BLEND];
					}

					int yd = yi - BLEND;
					if (yd >= (hasDownRegion ? -BLEND : 0) && yd < Region::Y + (hasUpRegion ? BLEND : 0))
					{
						runningHues -= hues[yd + BLEND];
						runningSat -= sats[yd + BLEND];
						runningLight -= light[yd + BLEND];
						runningMultiplier -= mul[yd + BLEND];
						runningNumber -= num[yd + BLEND];
					}

					if (yi >= 0 && yi < Region::Y)
					{
						std::shared_ptr<Region> r = regionLoader->findRegionForWorldCoordinates(baseX + xi, baseY + yi);
						if (r != nullptr)
						{
							int underlayId = r->getUnderlayId(z, convert(xi), convert(yi));
							int overlayId = r->getOverlayId(z, convert(xi), convert(yi));

							if (underlayId > 0 || overlayId > 0)
							{
								int underlayHsl = -1;
								if (underlayId > 0)
								{
									int avgHue = runningHues * 256 / runningMultiplier;
									int avgSat = runningSat / runningNumber;
									int avgLight = runningLight / runningNumber;
									// randomness is added to avgHue here

									if (avgLight < 0)
									{
										avgLight = 0;
									}
									else if (avgLight > 255)
									{
										avgLight = 255;
									}

									underlayHsl = packHsl(avgHue, avgSat, avgLight);
								}

								int underlayRgb = 0;
								if (underlayHsl != -1)
								{
									int var0 = method1792(underlayHsl, 96);
									underlayRgb = colorPalette[var0] | 0xFF000000;
								}

								int shape, rotation;
								int overlayRgb = 0;
								if (overlayId == 0)
								{
									shape = rotation = 0;
								}
								else
								{
									shape = r->getOverlayPath(z, convert(xi), convert(yi)) + 1;
									rotation = r->getOverlayRotation(z, convert(xi), convert(yi));

									std::shared_ptr<OverlayDefinition> overlayDefinition = findOverlay(overlayId - 1);
									int overlayTexture = overlayDefinition->getTexture();
									int hsl;

									if (overlayTexture >= 0)
									{
										hsl = rsTextureProvider->getAverageTextureRGB(overlayTexture);
									}
									else if (overlayDefinition->getRgbColor() == 0xFF'00FF)
									{
										hsl = -2;
									}
									else
									{
										// randomness added here
										int overlayHsl = packHsl(overlayDefinition->getHue(), overlayDefinition->getSaturation(), overlayDefinition->getLightness());
										hsl = overlayHsl;
									}

									if (hsl != -2)
									{
										int var0 = adjustHSLListness0(hsl, 96);
										overlayRgb = colorPalette[var0] | 0xFF000000;
									}

									if (overlayDefinition->getSecondaryRgbColor() != -1)
									{
										int hue = overlayDefinition->getOtherHue();
										int sat = overlayDefinition->getOtherSaturation();
										int olight = overlayDefinition->getOtherLightness();
										hsl = packHsl(hue, sat, olight);
										int var0 = adjustHSLListness0(hsl, 96);
										overlayRgb = colorPalette[var0] | 0xFF000000;
									}
								}

								if (shape == 0)
								{
									int drawX = xi;
									int drawY = Region::Y - 1 - yi;
									if (underlayRgb != 0)
									{
										drawMapSquare(pixels, drawX, drawY, underlayRgb);
									}
								}
								else if (shape == 1)
								{
									int drawX = xi;
									int drawY = Region::Y - 1 - yi;
									drawMapSquare(pixels, drawX, drawY, overlayRgb);
								}
								else
								{
									int drawX = xi * MAP_SCALE;
									int drawY = (Region::Y - 1 - yi) * MAP_SCALE;
									std::vector<int> tileShapes = TILE_SHAPE_2D[shape];
									std::vector<int> tileRotations = TILE_ROTATION_2D[rotation];
									if (underlayRgb != 0)
									{
										int rotIdx = 0;
										for (int i = 0; i < Region::Z; ++i)
										{
											int p1 = tileShapes[tileRotations[rotIdx++]] == 0 ? underlayRgb : overlayRgb;
											int p2 = tileShapes[tileRotations[rotIdx++]] == 0 ? underlayRgb : overlayRgb;
											int p3 = tileShapes[tileRotations[rotIdx++]] == 0 ? underlayRgb : overlayRgb;
											int p4 = tileShapes[tileRotations[rotIdx++]] == 0 ? underlayRgb : overlayRgb;
											pixels[drawX + 0][drawY + i] = p1;
											pixels[drawX + 1][drawY + i] = p2;
											pixels[drawX + 2][drawY + i] = p3;
											pixels[drawX + 3][drawY + i] = p4;
										}
									}
									else
									{
										int rotIdx = 0;
										for (int i = 0; i < Region::Z; ++i)
										{
											int p1 = tileShapes[tileRotations[rotIdx++]];
											int p2 = tileShapes[tileRotations[rotIdx++]];
											int p3 = tileShapes[tileRotations[rotIdx++]];
											int p4 = tileShapes[tileRotations[rotIdx++]];

											if (p1 != 0)
											{
												pixels[drawX + 0][drawY + i] = overlayRgb;
											}

											if (p2 != 0)
											{
												pixels[drawX + 1][drawY + i] = overlayRgb;
											}

											if (p3 != 0)
											{
												pixels[drawX + 2][drawY + i] = overlayRgb;
											}

											if (p4 != 0)
											{
												pixels[drawX + 3][drawY + i] = overlayRgb;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	int MapImageDumper::convert(int d)
	{
		if (d >= 0)
		{
			return d % 64;
		}
		else
		{
			return 64 - -(d % 64) - 1;
		}
	}

	void MapImageDumper::drawObjects(std::shared_ptr<BufferedImage> image, int drawBaseX, int drawBaseY, std::shared_ptr<Region> region, int z)
	{
		if (!renderObjects)
		{
			return;
		}

		std::vector<std::shared_ptr<Location>> planeLocs;
		std::vector<std::shared_ptr<Location>> pushDownLocs;
		std::vector<std::vector<std::shared_ptr<Location>>> layers = std::vector<std::vector<Location>> {planeLocs, pushDownLocs};
		for (int localX = 0; localX < Region::X; localX++)
		{
			int regionX = localX + region->getBaseX();
			for (int localY = 0; localY < Region::Y; localY++)
			{
				int regionY = localY + region->getBaseY();

				planeLocs.clear();
				pushDownLocs.clear();
				bool isBridge = (region->getTileSetting(1, localX, localY) & 2) != 0;
				int tileZ = z + (isBridge ? 1 : 0);

				for (auto loc : region->getLocations())
				{
					std::shared_ptr<Position> pos = loc->getPosition();
					if (pos->getX() != regionX || pos->getY() != regionY)
					{
						continue;
					}

					if (pos->getZ() == tileZ && (region->getTileSetting(z, localX, localY) & 24) == 0)
					{
						planeLocs.push_back(loc);
					}
					else if (z < 3 && pos->getZ() == tileZ + 1 && (region->getTileSetting(z + 1, localX, localY) & 8) != 0)
					{
						pushDownLocs.push_back(loc);
					}
				}

				for (auto locs : layers)
				{
					for (auto location : locs)
					{
						int type = location->getType();
						if (type >= 0 && type <= 3)
						{
							int rotation = location->getOrientation();

							std::shared_ptr<ObjectDefinition> object = findObject(location->getId());

							int drawX = (drawBaseX + localX) * MAP_SCALE;
							int drawY = (drawBaseY + (Region::Y - object->getSizeY() - localY)) * MAP_SCALE;

							int rgb = wallColor;
							if (object->getWallOrDoor() != 0)
							{
								rgb = doorColor;
							}
							rgb |= 0xFF000000;

							if (object->getMapSceneID() != -1)
							{
								blitMapDecoration(image, drawX, drawY, object);
							}
							else if (drawX >= 0 && drawY >= 0 && drawX < image->getWidth() && drawY < image->getHeight())
							{
								if (type == 0 || type == 2)
								{
									if (rotation == 0)
									{
										image->setRGB(drawX + 0, drawY + 0, rgb);
										image->setRGB(drawX + 0, drawY + 1, rgb);
										image->setRGB(drawX + 0, drawY + 2, rgb);
										image->setRGB(drawX + 0, drawY + 3, rgb);
									}
									else if (rotation == 1)
									{
										image->setRGB(drawX + 0, drawY + 0, rgb);
										image->setRGB(drawX + 1, drawY + 0, rgb);
										image->setRGB(drawX + 2, drawY + 0, rgb);
										image->setRGB(drawX + 3, drawY + 0, rgb);
									}
									else if (rotation == 2)
									{
										image->setRGB(drawX + 3, drawY + 0, rgb);
										image->setRGB(drawX + 3, drawY + 1, rgb);
										image->setRGB(drawX + 3, drawY + 2, rgb);
										image->setRGB(drawX + 3, drawY + 3, rgb);
									}
									else if (rotation == 3)
									{
										image->setRGB(drawX + 0, drawY + 3, rgb);
										image->setRGB(drawX + 1, drawY + 3, rgb);
										image->setRGB(drawX + 2, drawY + 3, rgb);
										image->setRGB(drawX + 3, drawY + 3, rgb);
									}
								}

								if (type == 3)
								{
									if (rotation == 0)
									{
										image->setRGB(drawX + 0, drawY + 0, rgb);
									}
									else if (rotation == 1)
									{
										image->setRGB(drawX + 3, drawY + 0, rgb);
									}
									else if (rotation == 2)
									{
										image->setRGB(drawX + 3, drawY + 3, rgb);
									}
									else if (rotation == 3)
									{
										image->setRGB(drawX + 0, drawY + 3, rgb);
									}
								}

								if (type == 2)
								{
									if (rotation == 3)
									{
										image->setRGB(drawX + 0, drawY + 0, rgb);
										image->setRGB(drawX + 0, drawY + 1, rgb);
										image->setRGB(drawX + 0, drawY + 2, rgb);
										image->setRGB(drawX + 0, drawY + 3, rgb);
									}
									else if (rotation == 0)
									{
										image->setRGB(drawX + 0, drawY + 0, rgb);
										image->setRGB(drawX + 1, drawY + 0, rgb);
										image->setRGB(drawX + 2, drawY + 0, rgb);
										image->setRGB(drawX + 3, drawY + 0, rgb);
									}
									else if (rotation == 1)
									{
										image->setRGB(drawX + 3, drawY + 0, rgb);
										image->setRGB(drawX + 3, drawY + 1, rgb);
										image->setRGB(drawX + 3, drawY + 2, rgb);
										image->setRGB(drawX + 3, drawY + 3, rgb);
									}
									else if (rotation == 2)
									{
										image->setRGB(drawX + 0, drawY + 3, rgb);
										image->setRGB(drawX + 1, drawY + 3, rgb);
										image->setRGB(drawX + 2, drawY + 3, rgb);
										image->setRGB(drawX + 3, drawY + 3, rgb);
									}
								}
							}
						}
					}

					for (auto location : locs)
					{
						int type = location->getType();
						if (type == 9)
						{
							int rotation = location->getOrientation();

							std::shared_ptr<ObjectDefinition> object = findObject(location->getId());

							int drawX = (drawBaseX + localX) * MAP_SCALE;
							int drawY = (drawBaseY + (Region::Y - object->getSizeY() - localY)) * MAP_SCALE;

							if (object->getMapSceneID() != -1)
							{
								blitMapDecoration(image, drawX, drawY, object);
								continue;
							}

							if (drawX >= 0 && drawY >= 0 && drawX < image->getWidth() && drawY < image->getHeight())
							{
								int rgb = 0xFFEE'EEEE;
								if (object->getWallOrDoor() != 0)
								{
									rgb = 0xFFEE'0000;
								}

								if (rotation != 0 && rotation != 2)
								{
									image->setRGB(drawX + 0, drawY + 0, rgb);
									image->setRGB(drawX + 1, drawY + 1, rgb);
									image->setRGB(drawX + 2, drawY + 2, rgb);
									image->setRGB(drawX + 3, drawY + 3, rgb);
								}
								else
								{
									image->setRGB(drawX + 0, drawY + 3, rgb);
									image->setRGB(drawX + 1, drawY + 2, rgb);
									image->setRGB(drawX + 2, drawY + 1, rgb);
									image->setRGB(drawX + 3, drawY + 0, rgb);
								}
							}
						}
					}

					for (auto location : locs)
					{
						int type = location->getType();
						if (type == 22 || (type >= 9 && type <= 11))
						{
							std::shared_ptr<ObjectDefinition> object = findObject(location->getId());

							int drawX = (drawBaseX + localX) * MAP_SCALE;
							int drawY = (drawBaseY + (Region::Y - object->getSizeY() - localY)) * MAP_SCALE;

							if (object->getMapSceneID() != -1)
							{
								blitMapDecoration(image, drawX, drawY, object);
							}
						}
					}
				}
			}
		}
	}

	void MapImageDumper::drawObjects(std::shared_ptr<BufferedImage> image, int z)
	{
		for (auto region : regionLoader->getRegions())
		{
			int baseX = region->getBaseX();
			int baseY = region->getBaseY();

			// to pixel X
			int drawBaseX = baseX - regionLoader->getLowestX()->getBaseX();

			// to pixel Y. top most y is 0, but the top most
			// region has the greatest y, so invert
			int drawBaseY = regionLoader->getHighestY()->getBaseY() - baseY;

			drawObjects(image, drawBaseX, drawBaseY, region, z);
		}
	}

	void MapImageDumper::drawMapIcons(std::shared_ptr<BufferedImage> image, int drawBaseX, int drawBaseY, std::shared_ptr<Region> region, int z)
	{
		int baseX = region->getBaseX();
		int baseY = region->getBaseY();

		std::shared_ptr<Graphics2D> graphics = image->createGraphics();

		drawMapIcons(image, region, z, drawBaseX, drawBaseY);

		if (labelRegions)
		{
			graphics->setColor(Color::WHITE);
			std::wstring str = std::to_wstring(baseX) + L"," + std::to_wstring(baseY) + L" (" + std::to_wstring(region->getRegionX()) + L"," + std::to_wstring(region->getRegionY()) + L")";
			graphics->drawString(str, drawBaseX * MAP_SCALE, drawBaseY * MAP_SCALE + graphics->getFontMetrics().getHeight());
		}

		if (outlineRegions)
		{
			graphics->setColor(Color::WHITE);
			graphics->drawRect(drawBaseX * MAP_SCALE, drawBaseY * MAP_SCALE, Region::X * MAP_SCALE, Region::Y * MAP_SCALE);
		}

		graphics->dispose();
	}

	void MapImageDumper::drawMapIcons(std::shared_ptr<BufferedImage> image, int z)
	{
		// map icons
		for (auto region : regionLoader->getRegions())
		{
			int baseX = region->getBaseX();
			int baseY = region->getBaseY();

			// to pixel X
			int drawBaseX = baseX - regionLoader->getLowestX()->getBaseX();

			// to pixel Y. top most y is 0, but the top most
			// region has the greatest y, so invert
			int drawBaseY = regionLoader->getHighestY()->getBaseY() - baseY;

			drawMapIcons(image, drawBaseX, drawBaseY, region, z);
		}
	}

	std::shared_ptr<ObjectDefinition> MapImageDumper::findObject(int id)
	{
		return objectManager->getObject(id);
	}

	int MapImageDumper::packHsl(int var0, int var1, int var2)
	{
		if (var2 > 179)
		{
			var1 /= 2;
		}

		if (var2 > 192)
		{
			var1 /= 2;
		}

		if (var2 > 217)
		{
			var1 /= 2;
		}

		if (var2 > 243)
		{
			var1 /= 2;
		}

		int var3 = (var1 / 32 << 7) + (var0 / 4 << 10) + var2 / 2;
		return var3;
	}

	int MapImageDumper::method1792(int var0, int var1)
	{
		if (var0 == -1)
		{
			return 12345678;
		}
		else
		{
			var1 = (var0 & 127) * var1 / 128;
			if (var1 < 2)
			{
				var1 = 2;
			}
			else if (var1 > 126)
			{
				var1 = 126;
			}

			return (var0 & 65408) + var1;
		}
	}

	int MapImageDumper::adjustHSLListness0(int var0, int var1)
	{
		if (var0 == -2)
		{
			return 12345678;
		}
		else if (var0 == -1)
		{
			if (var1 < 2)
			{
				var1 = 2;
			}
			else if (var1 > 126)
			{
				var1 = 126;
			}

			return var1;
		}
		else
		{
			var1 = (var0 & 127) * var1 / 128;
			if (var1 < 2)
			{
				var1 = 2;
			}
			else if (var1 > 126)
			{
				var1 = 126;
			}

			return (var0 & 65408) + var1;
		}
	}

	void MapImageDumper::drawMapSquare(std::vector<std::vector<int>> &pixels, int x, int y, int rgb)
	{
		x *= MAP_SCALE;
		y *= MAP_SCALE;

		for (int i = 0; i < MAP_SCALE; ++i)
		{
			for (int j = 0; j < MAP_SCALE; ++j)
			{
				pixels[x + i][y + j] = rgb;
			}
		}
	}

	void MapImageDumper::drawMapIcons(std::shared_ptr<BufferedImage> img, std::shared_ptr<Region> region, int z, int drawBaseX, int drawBaseY)
	{
		if (!renderIcons)
		{
			return;
		}

		for (auto location : region->getLocations())
		{
			int localX = location->getPosition().getX() - region->getBaseX();
			int localY = location->getPosition().getY() - region->getBaseY();
			bool isBridge = (region->getTileSetting(1, localX, localY) & 2) != 0;

			int tileZ = z + (isBridge ? 1 : 0);
			int localZ = location->getPosition().getZ();
			if (z != 0 && localZ != tileZ)
			{
				// draw all icons on z=0
				continue;
			}

			std::shared_ptr<ObjectDefinition> od = findObject(location->getId());

			assert(od != nullptr);

			int drawX = drawBaseX + localX;
			int drawY = drawBaseY + (Region::Y - 1 - localY);

			if (od->getMapAreaId() != -1)
			{
				std::shared_ptr<AreaDefinition> area = areas->getArea(od->getMapAreaId());
				assert(area != nullptr);

				std::shared_ptr<SpriteDefinition> sprite = sprites->findSprite(area->spriteId, 0);
				assert(sprite != nullptr);

				blitIcon(img, 2 + (drawX * MAP_SCALE) - (sprite->getMaxWidth() / 2), 2 + (drawY * MAP_SCALE) - (sprite->getMaxHeight() / 2), sprite);
			}
		}
	}

	void MapImageDumper::loadRegions()
	{
		regionLoader->loadRegions();
		regionLoader->calculateBounds();

		log::debug(L"North most region: {}", regionLoader->getLowestY()->getBaseY());
		log::debug(L"South most region: {}", regionLoader->getHighestY()->getBaseY());
		log::debug(L"West most region:  {}", regionLoader->getLowestX()->getBaseX());
		log::debug(L"East most region:  {}", regionLoader->getHighestX()->getBaseX());
	}

	void MapImageDumper::loadUnderlays(std::shared_ptr<Store> store)
	{
		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::CONFIGS);
		std::shared_ptr<Archive> archive = index->getArchive(ConfigType::UNDERLAY.getId());

		std::vector<signed char> archiveData = storage->loadArchive(archive);
		std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

		for (auto file : files->getFiles())
		{
			std::shared_ptr<UnderlayLoader> loader = std::make_shared<UnderlayLoader>();
			std::shared_ptr<UnderlayDefinition> underlay = loader->load(file->getFileId(), file->getContents());

			underlays.emplace(underlay->getId(), underlay);
		}
	}

	std::shared_ptr<UnderlayDefinition> MapImageDumper::findUnderlay(int id)
	{
		return underlays[id];
	}

	void MapImageDumper::loadOverlays(std::shared_ptr<Store> store)
	{
		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::CONFIGS);
		std::shared_ptr<Archive> archive = index->getArchive(ConfigType::OVERLAY.getId());

		std::vector<signed char> archiveData = storage->loadArchive(archive);
		std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

		for (auto file : files->getFiles())
		{
			std::shared_ptr<OverlayLoader> loader = std::make_shared<OverlayLoader>();
			std::shared_ptr<OverlayDefinition> overlay = loader->load(file->getFileId(), file->getContents());

			overlays.emplace(overlay->getId(), overlay);
		}
	}

	std::shared_ptr<OverlayDefinition> MapImageDumper::findOverlay(int id)
	{
		return overlays[id];
	}

	void MapImageDumper::loadSprites()
	{
		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::SPRITES);
		std::shared_ptr<Archive> a = index->findArchiveByName(L"mapscene");
		std::vector<signed char> contents = a->decompress(storage->loadArchive(a));

		std::shared_ptr<SpriteLoader> loader = std::make_shared<SpriteLoader>();
		mapDecorations = loader->load(a->getArchiveId(), contents);
	}

	void MapImageDumper::blitMapDecoration(std::shared_ptr<BufferedImage> dst, int x, int y, std::shared_ptr<ObjectDefinition> object)
	{
		std::shared_ptr<SpriteDefinition> sprite = mapDecorations[object->getMapSceneID()];
		int ox = (object->getSizeX() * MAP_SCALE - sprite->getWidth()) / 2;
		int oy = (object->getSizeY() * MAP_SCALE - sprite->getHeight()) / 2;
		blitIcon(dst, x + ox, y + oy, sprite);
	}

	void MapImageDumper::blitIcon(std::shared_ptr<BufferedImage> dst, int x, int y, std::shared_ptr<SpriteDefinition> sprite)
	{
		x += sprite->getOffsetX();
		y += sprite->getOffsetY();

		int ymin = std::max(0, -y);
		int ymax = std::min(sprite->getHeight(), dst->getHeight() - y);

		int xmin = std::max(0, -x);
		int xmax = std::min(sprite->getWidth(), dst->getWidth() - x);

		for (int yo = ymin; yo < ymax; yo++)
		{
			for (int xo = xmin; xo < xmax; xo++)
			{
				int rgb = sprite->getPixels()[xo + (yo * sprite->getWidth())];
				if (rgb != 0)
				{
					dst->setRGB(x + xo, y + yo, rgb | 0xFF000000);
				}
			}
		}
	}
}
