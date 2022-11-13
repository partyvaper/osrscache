#pragma once

#include "../../../../../main/java/net/runelite/cache/definitions/LocationsDefinition.h"
#include "../../../../../main/java/net/runelite/cache/definitions/MapDefinition.h"
#include "../../../../../main/java/net/runelite/cache/definitions/loaders/LocationsLoader.h"
#include "../../../../../main/java/net/runelite/cache/definitions/loaders/MapLoader.h"
#include "../../../../../main/java/net/runelite/cache/fs/Archive.h"
#include "../../../../../main/java/net/runelite/cache/fs/Index.h"
#include "../../../../../main/java/net/runelite/cache/fs/Storage.h"
#include "../../../../../main/java/net/runelite/cache/fs/Store.h"
#include "../../../../../main/java/net/runelite/cache/util/XteaKeyManager.h"
#include "StoreLocation.h"
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
namespace net::runelite::cache
{

	using Gson = com::google::gson::Gson;
	using GsonBuilder = com::google::gson::GsonBuilder;
	using IOException = java::io::IOException;
	using Map = java::util::Map;
	using LocationsDefinition = net::runelite::cache::definitions::LocationsDefinition;
	using MapDefinition = net::runelite::cache::definitions::MapDefinition;
	using Store = net::runelite::cache::fs::Store;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;

	class MapDumperTest : public std::enable_shared_from_this<MapDumperTest>
	{
	private:
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		static const std::shared_ptr<Logger> logger;

		static constexpr int MAX_REGIONS = 32768;
		const std::shared_ptr<Gson> gson = (std::make_shared<GsonBuilder>())->setPrettyPrinting().create();

	public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Rule public org.junit.rules.TemporaryFolder folder = StoreLocation.getTemporaryFolder();
		std::shared_ptr<TemporaryFolder> folder = StoreLocation::getTemporaryFolder();

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void dumpRaw() throws java.io.IOException
		virtual void dumpRaw();

	private:
		std::unordered_map<std::shared_ptr<MapDefinition>, std::shared_ptr<LocationsDefinition>> loadRegions(std::shared_ptr<Store> store);

	public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void dumpJson() throws java.io.IOException
		virtual void dumpJson();
	};

}
