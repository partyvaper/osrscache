#pragma once

#include "definitions/AreaDefinition.h"
#include "definitions/ObjectDefinition.h"
#include "definitions/OverlayDefinition.h"
#include "definitions/SpriteDefinition.h"
#include "definitions/UnderlayDefinition.h"
#include "definitions/loaders/OverlayLoader.h"
#include "definitions/loaders/SpriteLoader.h"
#include "definitions/loaders/UnderlayLoader.h"
#include "fs/Archive.h"
#include "fs/ArchiveFiles.h"
#include "fs/FSFile.h"
#include "fs/Index.h"
#include "fs/Storage.h"
#include "fs/Store.h"
#include "item/RSTextureProvider.h"
#include "models/JagexColor.h"
#include "region/Location.h"
#include "region/Position.h"
#include "region/Region.h"
#include "region/RegionLoader.h"
#include "util/BigBufferedImage.h"
#include "util/KeyProvider.h"
#include "util/XteaKeyManager.h"
#include "AreaManager.h"
#include "SpriteManager.h"
#include "ObjectManager.h"
#include <string>
#include <unordered_map>
#include <vector>
#include "tangible_exception_helper.h"
#include <cassert>
#include <memory>
#include "../../../../../../tangible_rectangular_vectors.h"

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

	using BufferedImage = java::awt::image::BufferedImage;
	using IOException = java::io::IOException;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using ObjectDefinition = net::runelite::cache::definitions::ObjectDefinition;
	using OverlayDefinition = net::runelite::cache::definitions::OverlayDefinition;
	using SpriteDefinition = net::runelite::cache::definitions::SpriteDefinition;
	using UnderlayDefinition = net::runelite::cache::definitions::UnderlayDefinition;
	using Store = net::runelite::cache::fs::Store;
	using RSTextureProvider = net::runelite::cache::item::RSTextureProvider;
	using JagexColor = net::runelite::cache::models::JagexColor;
	using Region = net::runelite::cache::region::Region;
	using RegionLoader = net::runelite::cache::region::RegionLoader;
	using KeyProvider = net::runelite::cache::util::KeyProvider;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Slf4j @Accessors(chain = true) public class MapImageDumper
	class MapImageDumper : public std::enable_shared_from_this<MapImageDumper>
	{
	private:
		static constexpr int MAP_SCALE = 4; // this squared is the number of pixels per map square
		static constexpr int BLEND = 5; // number of surrounding tiles for ground blending

		static std::vector<int> colorPalette;

		static std::vector<std::vector<int>> TILE_SHAPE_2D;
		static std::vector<std::vector<int>> TILE_ROTATION_2D;

		const int wallColor = (238 + static_cast<int>(random() * 20.0) - 10 << 16) + (238 + static_cast<int>(random() * 20.0) - 10 << 8) + (238 + static_cast<int>(random() * 20.0) - 10);
		const int doorColor = 238 + static_cast<int>(random() * 20.0) - 10 << 16;

		const std::shared_ptr<Store> store;

//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final java.util.Map<int, net.runelite.cache.definitions.UnderlayDefinition> underlays = new java.util.HashMap<>();
		std::unordered_map<int, std::shared_ptr<UnderlayDefinition>> underlays = std::unordered_map<int, std::shared_ptr<UnderlayDefinition>>();
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final java.util.Map<int, net.runelite.cache.definitions.OverlayDefinition> overlays = new java.util.HashMap<>();
		std::unordered_map<int, std::shared_ptr<OverlayDefinition>> overlays = std::unordered_map<int, std::shared_ptr<OverlayDefinition>>();
		std::vector<std::shared_ptr<SpriteDefinition>> mapDecorations;

		const std::shared_ptr<RegionLoader> regionLoader;
		const std::shared_ptr<AreaManager> areas;
		const std::shared_ptr<SpriteManager> sprites;
		std::shared_ptr<RSTextureProvider> rsTextureProvider;
		const std::shared_ptr<ObjectManager> objectManager;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Getter @Setter private boolean labelRegions;
		bool labelRegions = false;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Getter @Setter private boolean outlineRegions;
		bool outlineRegions = false;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Getter @Setter private boolean renderMap = true;
		bool renderMap = true;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Getter @Setter private boolean renderObjects = true;
		bool renderObjects = true;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Getter @Setter private boolean renderIcons = true;
		bool renderIcons = true;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Getter @Setter private boolean transparency = false;
		bool transparency = false;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Getter @Setter private boolean lowMemory = true;
		bool lowMemory = true;

	public:
		MapImageDumper(std::shared_ptr<Store> store, std::shared_ptr<KeyProvider> keyProvider);

		MapImageDumper(std::shared_ptr<Store> store, std::shared_ptr<RegionLoader> regionLoader);

		static void main(std::vector<std::wstring> &args);

	protected:
		virtual double random();

	public:
		virtual std::shared_ptr<MapImageDumper> setBrightness(double brightness);

		virtual std::shared_ptr<MapImageDumper> load();

		virtual std::shared_ptr<BufferedImage> drawMap(int z);

	private:
		void drawNeighborObjects(std::shared_ptr<BufferedImage> image, int rx, int ry, int dx, int dy, int z);

	public:
		virtual std::shared_ptr<BufferedImage> drawRegion(std::shared_ptr<Region> region, int z);

	private:
		void drawMap(std::shared_ptr<BufferedImage> image, int drawBaseX, int drawBaseY, int z, std::shared_ptr<Region> region);

		void drawMap(std::shared_ptr<BufferedImage> image, int z);

		void drawTile(std::shared_ptr<BufferedImage> to, std::vector<std::vector<std::vector<int>>> &planes, std::shared_ptr<Region> region, int drawBaseX, int drawBaseY, int z, int x, int y);

		void drawMap(std::vector<std::vector<int>> &pixels, std::shared_ptr<Region> region, int z);

		static int convert(int d);

		void drawObjects(std::shared_ptr<BufferedImage> image, int drawBaseX, int drawBaseY, std::shared_ptr<Region> region, int z);

		void drawObjects(std::shared_ptr<BufferedImage> image, int z);

		void drawMapIcons(std::shared_ptr<BufferedImage> image, int drawBaseX, int drawBaseY, std::shared_ptr<Region> region, int z);

		void drawMapIcons(std::shared_ptr<BufferedImage> image, int z);

		std::shared_ptr<ObjectDefinition> findObject(int id);

		int packHsl(int var0, int var1, int var2);

	public:
		static int method1792(int var0, int var1);

		static int adjustHSLListness0(int var0, int var1) final;

	private:
		void drawMapSquare(std::vector<std::vector<int>> &pixels, int x, int y, int rgb);

		void drawMapIcons(std::shared_ptr<BufferedImage> img, std::shared_ptr<Region> region, int z, int drawBaseX, int drawBaseY);

		void loadRegions();

		void loadUnderlays(std::shared_ptr<Store> store);

		std::shared_ptr<UnderlayDefinition> findUnderlay(int id);

		void loadOverlays(std::shared_ptr<Store> store);

		std::shared_ptr<OverlayDefinition> findOverlay(int id);

		void loadSprites();

		void blitMapDecoration(std::shared_ptr<BufferedImage> dst, int x, int y, std::shared_ptr<ObjectDefinition> object);

		void blitIcon(std::shared_ptr<BufferedImage> dst, int x, int y, std::shared_ptr<SpriteDefinition> sprite);
	};

}
