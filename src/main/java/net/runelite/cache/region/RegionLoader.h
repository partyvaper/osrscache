#pragma once

#include "../IndexType.h"
#include "../definitions/LocationsDefinition.h"
#include "../definitions/MapDefinition.h"
#include "../definitions/loaders/LocationsLoader.h"
#include "../definitions/loaders/MapLoader.h"
#include "../fs/Archive.h"
#include "../fs/Index.h"
#include "../fs/Storage.h"
#include "../fs/Store.h"
#include "../util/KeyProvider.h"
#include "Region.h"
#include <unordered_map>
#include <vector>
#include "tangible_exception_helper.h"
#include <cassert>
#include <memory>

/*
 * Copyright (c) 2016-2017, Adam <Adam@sigterm.info>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
namespace net::runelite::cache::region
{

	using IOException = java::io::IOException;
	using Collection = java::util::Collection;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using LocationsDefinition = net::runelite::cache::definitions::LocationsDefinition;
	using MapDefinition = net::runelite::cache::definitions::MapDefinition;
	using Index = net::runelite::cache::fs::Index;
	using Store = net::runelite::cache::fs::Store;
	using KeyProvider = net::runelite::cache::util::KeyProvider;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Slf4j public class RegionLoader
	class RegionLoader : public std::enable_shared_from_this<RegionLoader>
	{
	private:
		static constexpr int MAX_REGION = 32768;

		const std::shared_ptr<Store> store;
		const std::shared_ptr<Index> index;
		const std::shared_ptr<KeyProvider> keyProvider;

//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final java.util.Map<int, Region> regions = new java.util.HashMap<>();
		std::unordered_map<int, std::shared_ptr<Region>> regions = std::unordered_map<int, std::shared_ptr<Region>>();
		std::shared_ptr<Region> lowestX = nullptr, lowestY = nullptr;
		std::shared_ptr<Region> highestX = nullptr, highestY = nullptr;

	public:
		RegionLoader(std::shared_ptr<Store> store, std::shared_ptr<KeyProvider> keyProvider);

		virtual void loadRegions();

		virtual std::shared_ptr<Region> loadRegionFromArchive(int i);

		virtual std::shared_ptr<Region> loadRegion(int id, std::shared_ptr<MapDefinition> map, std::shared_ptr<LocationsDefinition> locs);

		virtual void calculateBounds();

		virtual std::shared_ptr<Collection<std::shared_ptr<Region>>> getRegions();

		virtual std::shared_ptr<Region> findRegionForWorldCoordinates(int x, int y);

		virtual std::shared_ptr<Region> findRegionForRegionCoordinates(int x, int y);

		virtual std::shared_ptr<Region> getLowestX();

		virtual std::shared_ptr<Region> getLowestY();

		virtual std::shared_ptr<Region> getHighestX();

		virtual std::shared_ptr<Region> getHighestY();
	};

}
