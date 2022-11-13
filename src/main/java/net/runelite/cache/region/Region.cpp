#include "Region.h"
#include "HeightCalc.h"
#include "Position.h"

namespace net::runelite::cache::region
{
	using ArrayList = java::util::ArrayList;
	using List = java::util::List;
	using LocationsDefinition = net::runelite::cache::definitions::LocationsDefinition;
	using MapDefinition = net::runelite::cache::definitions::MapDefinition;
	using Tile = net::runelite::cache::definitions::MapDefinition::Tile;

	Region::Region(int id) : regionID(id), baseX(((id >> 8) & 0xFF) << 6) / * local coords are in bottom 6 bits (64*64) */, baseY((id & 0xFF) << 6)
	{
	}

	Region::Region(int x, int y) : regionID(x << 8 | y), baseX(x << 6), baseY(y << 6)
	{
	}

	void Region::loadTerrain(std::shared_ptr<MapDefinition> map)
	{
		std::vector<std::vector<std::vector<std::shared_ptr<MapDefinition::Tile>>>> tiles = map->getTiles();
		for (int z = 0; z < Z; z++)
		{
			for (int x = 0; x < X; x++)
			{
				for (int y = 0; y < Y; y++)
				{
					std::shared_ptr<MapDefinition::Tile> tile = tiles[z][x][y];

					if (!tile->height)
					{
						if (z == 0)
						{
							tileHeights[0][x][y] = -HeightCalc::calculate(baseX + x + 0xe3b7b, baseY + y + 0x87cce) * 8;
						}
						else
						{
							tileHeights[z][x][y] = tileHeights[z - 1][x][y] - 240;
						}
					}
					else
					{
						int height = tile->getHeight();
						if (height == 1)
						{
							height = 0;
						}

						if (z == 0)
						{
							tileHeights[0][x][y] = -height * 8;
						}
						else
						{
							tileHeights[z][x][y] = tileHeights[z - 1][x][y] - height * 8;
						}
					}

					overlayIds[z][x][y] = tile->getOverlayId();
					overlayPaths[z][x][y] = tile->getOverlayPath();
					overlayRotations[z][x][y] = tile->getOverlayRotation();

					tileSettings[z][x][y] = tile->getSettings();
					underlayIds[z][x][y] = tile->getUnderlayId();
				}
			}
		}
	}

	void Region::loadLocations(std::shared_ptr<LocationsDefinition> locs)
	{
		for (std::shared_ptr<Location> loc : locs->getLocations())
		{
			std::shared_ptr<Location> newLoc = std::make_shared<Location>(loc->getId(), loc->getType(), loc->getOrientation(), std::make_shared<Position>(getBaseX() + loc->getPosition().getX(), getBaseY() + loc->getPosition().getY(), loc->getPosition().getZ()));
			locations.push_back(newLoc);
		}
	}

	int Region::getRegionID()
	{
		return regionID;
	}

	int Region::getBaseX()
	{
		return baseX;
	}

	int Region::getBaseY()
	{
		return baseY;
	}

	int Region::getTileHeight(int z, int x, int y)
	{
		return tileHeights[z][x][y];
	}

	signed char Region::getTileSetting(int z, int x, int y)
	{
		return tileSettings[z][x][y];
	}

	int Region::getOverlayId(int z, int x, int y)
	{
		return overlayIds[z][x][y] & 0x7FFF;
	}

	signed char Region::getOverlayPath(int z, int x, int y)
	{
		return overlayPaths[z][x][y];
	}

	signed char Region::getOverlayRotation(int z, int x, int y)
	{
		return overlayRotations[z][x][y];
	}

	int Region::getUnderlayId(int z, int x, int y)
	{
		return underlayIds[z][x][y] & 0x7FFF;
	}

	std::vector<std::shared_ptr<Location>> Region::getLocations()
	{
		return locations;
	}

	int Region::getRegionX()
	{
		return baseX >> 6;
	}

	int Region::getRegionY()
	{
		return baseY >> 6;
	}
}
