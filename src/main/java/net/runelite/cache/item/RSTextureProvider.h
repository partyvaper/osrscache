#pragma once

#include "../definitions/TextureDefinition.h"
#include "../definitions/providers/SpriteProvider.h"
#include "../definitions/providers/TextureProvider.h"
#include <vector>
#include <mutex>
#include <memory>

/*
 * Copyright (c) 2018, Adam <Adam@sigterm.info>
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
namespace net::runelite::cache::item
{

	using TextureDefinition = net::runelite::cache::definitions::TextureDefinition;
	using SpriteProvider = net::runelite::cache::definitions::providers::SpriteProvider;
	using TextureProvider = net::runelite::cache::definitions::providers::TextureProvider;

	class RSTextureProvider : public std::enable_shared_from_this<RSTextureProvider>
	{
	private:
		const std::shared_ptr<SpriteProvider> spriteProvider;
	public:
		std::vector<std::shared_ptr<TextureDefinition>> textures;
		int maxSize = 0;
		int size = 0;
		double brightness = 0.0;
		int width = 0;

		RSTextureProvider(std::shared_ptr<TextureProvider> textureProvider, std::shared_ptr<SpriteProvider> spriteProvider);

		virtual std::vector<int> load(int var1);


		virtual int getAverageTextureRGB(int var1);


		virtual bool vmethod3057(int var1);


		virtual bool vmethod3066(int var1);
	};

}
