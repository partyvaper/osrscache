#include "MapDumperTest.h"
#include "../../../../../main/java/net/runelite/cache/IndexType.h"

namespace net::runelite::cache
{
	using Files = com::google::common::io::Files;
	using Gson = com::google::gson::Gson;
	using GsonBuilder = com::google::gson::GsonBuilder;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using Entry = java::util::Map::Entry;
	using LocationsDefinition = net::runelite::cache::definitions::LocationsDefinition;
	using MapDefinition = net::runelite::cache::definitions::MapDefinition;
	using LocationsLoader = net::runelite::cache::definitions::loaders::LocationsLoader;
	using MapLoader = net::runelite::cache::definitions::loaders::MapLoader;
	using Archive = net::runelite::cache::fs::Archive;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
	using XteaKeyManager = net::runelite::cache::util::XteaKeyManager;
	using Ignore = org::junit::Ignore;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> MapDumperTest::logger = org::slf4j::LoggerFactory::getLogger(MapDumperTest::class);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void dumpRaw() throws java.io.IOException
	void MapDumperTest::dumpRaw()
	{
		std::shared_ptr<File> __super = StoreLocation::LOCATION, outDir = folder->newFolder();
		std::shared_ptr<XteaKeyManager> keyManager = std::make_shared<XteaKeyManager>();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(super))
		{
			Store store = Store(base);
			store.load();

			std::shared_ptr<Storage> storage = store.getStorage();
			std::shared_ptr<Index> index = store.getIndex(IndexType::MAPS);

			for (int i = 0; i < MAX_REGIONS; i++)
			{
				std::vector<int> keys = keyManager->getKey(i);

				int x = i >> 8;
				int y = i & 0xFF;

				std::shared_ptr<Archive> map = index->findArchiveByName(L"m" + std::to_wstring(x) + L"_" + std::to_wstring(y));
				std::shared_ptr<Archive> land = index->findArchiveByName(L"l" + std::to_wstring(x) + L"_" + std::to_wstring(y));

				assert((map == nullptr) == (land == nullptr));

				if (map == nullptr || land == nullptr)
				{
					continue;
				}

				std::vector<signed char> data = map->decompress(storage->loadArchive(map));

				Files::write(data, std::make_shared<File>(outDir, L"m" + std::to_wstring(x) + L"_" + std::to_wstring(y) + L".dat"));

				if (!keys.empty())
				{
					try
					{
						data = land->decompress(storage->loadArchive(land), keys);
					}
					catch (const IOException &ex)
					{
						logger->info(L"Unable to decompress and load land " + std::to_wstring(x) + L"," + std::to_wstring(y) + L" (bad keys?)", ex);
						continue;
					}

					logger->info(L"Decrypted region {} coords {},{}", i, x, y);

					Files::write(data, std::make_shared<File>(outDir, L"l" + std::to_wstring(x) + L"_" + std::to_wstring(y) + L".dat"));
				}
			}
		}
	}

	std::unordered_map<std::shared_ptr<MapDefinition>, std::shared_ptr<LocationsDefinition>> MapDumperTest::loadRegions(std::shared_ptr<Store> store)
	{
		std::unordered_map<std::shared_ptr<MapDefinition>, std::shared_ptr<LocationsDefinition>> mapMap;
		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::MAPS);
		std::shared_ptr<XteaKeyManager> keyManager = std::make_shared<XteaKeyManager>();

		for (int i = 0; i < MAX_REGIONS; ++i)
		{
			int x = i >> 8;
			int y = i & 0xFF;

			std::shared_ptr<Archive> map = index->findArchiveByName(L"m" + std::to_wstring(x) + L"_" + std::to_wstring(y));
			std::shared_ptr<Archive> land = index->findArchiveByName(L"l" + std::to_wstring(x) + L"_" + std::to_wstring(y));

			assert((map == nullptr) == (land == nullptr));

			if (map == nullptr || land == nullptr)
			{
				continue;
			}

			std::vector<signed char> data = map->decompress(storage->loadArchive(map));
			std::shared_ptr<MapDefinition> mapDef = (std::make_shared<MapLoader>())->load(x, y, data);
			std::shared_ptr<LocationsDefinition> locDef = nullptr;

			std::vector<int> keys = keyManager->getKey(i);
			if (!keys.empty())
			{
				try
				{
					data = land->decompress(storage->loadArchive(land), keys);
				}
				catch (const IOException &ex)
				{
					continue;
				}

				locDef = (std::make_shared<LocationsLoader>())->load(x, y, data);
			}

			mapMap.emplace(mapDef, locDef);
		}

		return mapMap;
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void dumpJson() throws java.io.IOException
	void MapDumperTest::dumpJson()
	{
		std::shared_ptr<File> __super = StoreLocation::LOCATION, outDir = folder->newFolder();

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(super))
		{
			Store store = Store(base);
			store.load();

			std::unordered_map<std::shared_ptr<MapDefinition>, std::shared_ptr<LocationsDefinition>> regions = loadRegions(store);

			for (auto entry : regions)
			{
				std::shared_ptr<MapDefinition> key = entry.first;
				std::shared_ptr<LocationsDefinition> value = entry.second;

				int x = key->getRegionX();
				int y = key->getRegionY();
				Files::write(gson->toJson(key).getBytes(), std::make_shared<File>(outDir, L"m" + std::to_wstring(x) + L"_" + std::to_wstring(y) + L".json"));
				if (value != nullptr)
				{
					Files::write(gson->toJson(value).getBytes(), std::make_shared<File>(outDir, L"l" + std::to_wstring(x) + L"_" + std::to_wstring(y) + L".json"));
				}
			}
		}

		logger->info(L"Dumped regions to {}", outDir);
	}
}
