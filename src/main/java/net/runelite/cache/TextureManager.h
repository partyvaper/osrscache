#pragma once

#include "definitions/TextureDefinition.h"
#include "definitions/loaders/TextureLoader.h"
#include "definitions/providers/TextureProvider.h"
#include "fs/Archive.h"
#include "fs/ArchiveFiles.h"
#include "fs/FSFile.h"
#include "fs/Index.h"
#include "fs/Storage.h"
#include "fs/Store.h"
#include <vector>
#include <memory>

/*
 * Copyright (c) 2017, Adam <Adam@sigterm.info>
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

	using IOException = java::io::IOException;
	using ArrayList = java::util::ArrayList;
	using List = java::util::List;
	using TextureDefinition = net::runelite::cache::definitions::TextureDefinition;
	using TextureProvider = net::runelite::cache::definitions::providers::TextureProvider;
	using Store = net::runelite::cache::fs::Store;

	class TextureManager : public std::enable_shared_from_this<TextureManager>, public TextureProvider
	{
	private:
		const std::shared_ptr<Store> store;
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final java.util.List<net.runelite.cache.definitions.TextureDefinition> textures = new java.util.ArrayList<>();
		std::vector<std::shared_ptr<TextureDefinition>> textures = std::vector<std::shared_ptr<TextureDefinition>>();

	public:
		TextureManager(std::shared_ptr<Store> store);

		virtual void load();

		virtual std::vector<std::shared_ptr<TextureDefinition>> getTextures();

		virtual std::shared_ptr<TextureDefinition> findTexture(int id);

		std::vector<std::shared_ptr<TextureDefinition>> provide() override;
	};

}
