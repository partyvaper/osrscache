#include "MapLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using MapDefinition = net::runelite::cache::definitions::MapDefinition;
	using Tile = net::runelite::cache::definitions::MapDefinition::Tile;
	using InputStream = net::runelite::cache::io::InputStream;
//	import static net.runelite.cache.region.Region.X;
//	import static net.runelite.cache.region.Region.Y;
//	import static net.runelite.cache.region.Region.Z;

	std::shared_ptr<MapDefinition> MapLoader::load(int regionX, int regionY, std::vector<signed char> &b)
	{
		std::shared_ptr<MapDefinition> map = std::make_shared<MapDefinition>();
		map->setRegionX(regionX);
		map->setRegionY(regionY);
		loadTerrain(map, b);
		return map;
	}

	void MapLoader::loadTerrain(std::shared_ptr<MapDefinition> map, std::vector<signed char> &buf)
	{
		std::vector<std::vector<std::vector<std::shared_ptr<MapDefinition::Tile>>>> tiles = map->getTiles();

		std::shared_ptr<InputStream> in = std::make_shared<InputStream>(buf);

		for (int z = 0; z < Z; z++)
		{
			for (int x = 0; x < X; x++)
			{
				for (int y = 0; y < Y; y++)
				{
					std::shared_ptr<MapDefinition::Tile> tile = tiles[z][x][y] = std::make_shared<MapDefinition::Tile>();
					while (true)
					{
						int attribute = in->readUnsignedShort();
						if (attribute == 0)
						{
							break;
						}
						else if (attribute == 1)
						{
							int height = in->readUnsignedByte();
							tile->height = height;
							break;
						}
						else if (attribute <= 49)
						{
							tile->attrOpcode = attribute;
							tile->overlayId = in->readShort();
							tile->overlayPath = static_cast<signed char>((attribute - 2) / 4);
							tile->overlayRotation = static_cast<signed char>(attribute - 2 & 3);
						}
						else if (attribute <= 81)
						{
							tile->settings = static_cast<signed char>(attribute - 49);
						}
						else
						{
							tile->underlayId = static_cast<short>(attribute - 81);
						}
					}
				}
			}
		}
	}
}
