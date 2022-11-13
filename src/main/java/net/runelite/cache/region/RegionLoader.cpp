#include "RegionLoader.h"

namespace net::runelite::cache::region
{
	using IOException = java::io::IOException;
	using Collection = java::util::Collection;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using Slf4j = lombok::extern_Keyword::slf4j::Slf4j;
	using IndexType = net::runelite::cache::IndexType;
	using LocationsDefinition = net::runelite::cache::definitions::LocationsDefinition;
	using MapDefinition = net::runelite::cache::definitions::MapDefinition;
	using LocationsLoader = net::runelite::cache::definitions::loaders::LocationsLoader;
	using MapLoader = net::runelite::cache::definitions::loaders::MapLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
	using KeyProvider = net::runelite::cache::util::KeyProvider;

	RegionLoader::RegionLoader(std::shared_ptr<Store> store, std::shared_ptr<KeyProvider> keyProvider) : store(store), index(store->getIndex(IndexType::MAPS)), keyProvider(keyProvider)
	{
	}

	void RegionLoader::loadRegions()
	{
		if (!this->regions.empty())
		{
			return;
		}

		for (int i = 0; i < MAX_REGION; ++i)
		{
			try
			{
				this->loadRegionFromArchive(i);
			}
			catch (const IOException &ex)
			{
				log::debug(L"Can't decrypt region " + std::to_wstring(i), ex);
			}
		}
	}

	std::shared_ptr<Region> RegionLoader::loadRegionFromArchive(int i)
	{
		int x = i >> 8;
		int y = i & 0xFF;

		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Archive> map = index->findArchiveByName(L"m" + std::to_wstring(x) + L"_" + std::to_wstring(y));
		std::shared_ptr<Archive> land = index->findArchiveByName(L"l" + std::to_wstring(x) + L"_" + std::to_wstring(y));

		assert((map == nullptr) == (land == nullptr));

		if (map == nullptr || land == nullptr)
		{
			return nullptr;
		}

		std::vector<signed char> data = map->decompress(storage->loadArchive(map));

		std::shared_ptr<MapDefinition> mapDef = (std::make_shared<MapLoader>())->load(x, y, data);

		std::shared_ptr<Region> region = std::make_shared<Region>(i);
		region->loadTerrain(mapDef);

		std::vector<int> keys = keyProvider->getKey(i);
		if (!keys.empty())
		{
			data = land->decompress(storage->loadArchive(land), keys);
			std::shared_ptr<LocationsDefinition> locDef = (std::make_shared<LocationsLoader>())->load(x, y, data);
			region->loadLocations(locDef);
		}

		regions.emplace(i, region);

		return region;
	}

	std::shared_ptr<Region> RegionLoader::loadRegion(int id, std::shared_ptr<MapDefinition> map, std::shared_ptr<LocationsDefinition> locs)
	{
		std::shared_ptr<Region> r = std::make_shared<Region>(id);
		r->loadTerrain(map);
		if (locs != nullptr)
		{
			r->loadLocations(locs);
		}
		regions.emplace(id, r);
		return r;
	}

	void RegionLoader::calculateBounds()
	{
		for (auto region : regions)
		{
			if (lowestX == nullptr || region->second.getBaseX() < lowestX->getBaseX())
			{
				lowestX = region->second;
			}

			if (highestX == nullptr || region->second.getBaseX() > highestX->getBaseX())
			{
				highestX = region->second;
			}

			if (lowestY == nullptr || region->second.getBaseY() < lowestY->getBaseY())
			{
				lowestY = region->second;
			}

			if (highestY == nullptr || region->second.getBaseY() > highestY->getBaseY())
			{
				highestY = region->second;
			}
		}
	}

	std::shared_ptr<Collection<std::shared_ptr<Region>>> RegionLoader::getRegions()
	{
		return regions.values();
	}

	std::shared_ptr<Region> RegionLoader::findRegionForWorldCoordinates(int x, int y)
	{
		x = static_cast<int>(static_cast<unsigned int>(x) >> 6);
		y = static_cast<int>(static_cast<unsigned int>(y) >> 6);
		return regions[(x << 8) | y];
	}

	std::shared_ptr<Region> RegionLoader::findRegionForRegionCoordinates(int x, int y)
	{
		return regions[(x << 8) | y];
	}

	std::shared_ptr<Region> RegionLoader::getLowestX()
	{
		return lowestX;
	}

	std::shared_ptr<Region> RegionLoader::getLowestY()
	{
		return lowestY;
	}

	std::shared_ptr<Region> RegionLoader::getHighestX()
	{
		return highestX;
	}

	std::shared_ptr<Region> RegionLoader::getHighestY()
	{
		return highestY;
	}
}
