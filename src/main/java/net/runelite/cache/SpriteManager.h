#pragma once

#include "definitions/SpriteDefinition.h"
#include "definitions/exporters/SpriteExporter.h"
#include "definitions/loaders/SpriteLoader.h"
#include "definitions/providers/SpriteProvider.h"
#include "fs/Archive.h"
#include "fs/Index.h"
#include "fs/Storage.h"
#include "fs/Store.h"
#include <vector>
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

	using LinkedListMultimap = com::google::common::collect::LinkedListMultimap;
	using Multimap = com::google::common::collect::Multimap;
	using BufferedImage = java::awt::image::BufferedImage;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using Collection = java::util::Collection;
	using SpriteDefinition = net::runelite::cache::definitions::SpriteDefinition;
	using SpriteProvider = net::runelite::cache::definitions::providers::SpriteProvider;
	using Store = net::runelite::cache::fs::Store;

	class SpriteManager : public std::enable_shared_from_this<SpriteManager>, public SpriteProvider
	{
	private:
		const std::shared_ptr<Store> store;
		const std::shared_ptr<Multimap<int, std::shared_ptr<SpriteDefinition>>> sprites = LinkedListMultimap::create();

	public:
		SpriteManager(std::shared_ptr<Store> store);

		virtual void load();

		virtual std::shared_ptr<Collection<std::shared_ptr<SpriteDefinition>>> getSprites();

		virtual std::shared_ptr<SpriteDefinition> findSprite(int spriteId, int frameId);

		virtual std::shared_ptr<BufferedImage> getSpriteImage(std::shared_ptr<SpriteDefinition> sprite);

		virtual void export_Keyword(std::shared_ptr<File> outDir);

		std::shared_ptr<SpriteDefinition> provide(int spriteId, int frameId) override;
	};

}
