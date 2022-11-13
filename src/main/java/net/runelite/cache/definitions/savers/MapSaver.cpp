#include "MapSaver.h"

namespace net::runelite::cache::definitions::savers
{
	using MapDefinition = net::runelite::cache::definitions::MapDefinition;
	using Tile = net::runelite::cache::definitions::MapDefinition::Tile;
	using OutputStream = net::runelite::cache::io::OutputStream;
//	import static net.runelite.cache.region.Region.X;
//	import static net.runelite.cache.region.Region.Y;
//	import static net.runelite.cache.region.Region.Z;

	std::vector<signed char> MapSaver::save(std::shared_ptr<MapDefinition> map)
	{
		std::vector<std::vector<std::vector<std::shared_ptr<MapDefinition::Tile>>>> tiles = map->getTiles();
		std::shared_ptr<OutputStream> out = std::make_shared<OutputStream>();
		for (int z = 0; z < Z; z++)
		{
			for (int x = 0; x < X; x++)
			{
				for (int y = 0; y < Y; y++)
				{
					std::shared_ptr<MapDefinition::Tile> tile = tiles[z][x][y];
					if (tile->attrOpcode != 0)
					{
						out->writeByte(tile->attrOpcode);
						out->writeByte(tile->overlayId);
					}
					if (tile->settings != 0)
					{
						out->writeByte(tile->settings + 49);
					}
					if (tile->underlayId != 0)
					{
						out->writeByte(tile->underlayId + 81);
					}
					if (!tile->height)
					{
						out->writeByte(0);
					}
					else
					{
						out->writeByte(1);
						out->writeByte(tile->height.value());
					}
				}
			}
		}
		return out->flip();
	}
}
