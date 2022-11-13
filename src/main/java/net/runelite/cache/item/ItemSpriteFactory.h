#pragma once

#include "../definitions/ItemDefinition.h"
#include "../definitions/ModelDefinition.h"
#include "../definitions/providers/ItemProvider.h"
#include "../definitions/providers/ModelProvider.h"
#include "../definitions/providers/SpriteProvider.h"
#include "../definitions/providers/TextureProvider.h"
#include "../models/FaceNormal.h"
#include "../models/JagexColor.h"
#include "../models/VertexNormal.h"
#include "SpritePixels.h"
#include "Model.h"
#include <vector>
#include <cmath>
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

	using BufferedImage = java::awt::image::BufferedImage;
	using IOException = java::io::IOException;
	using ItemDefinition = net::runelite::cache::definitions::ItemDefinition;
	using ModelDefinition = net::runelite::cache::definitions::ModelDefinition;
	using ItemProvider = net::runelite::cache::definitions::providers::ItemProvider;
	using ModelProvider = net::runelite::cache::definitions::providers::ModelProvider;
	using SpriteProvider = net::runelite::cache::definitions::providers::SpriteProvider;
	using TextureProvider = net::runelite::cache::definitions::providers::TextureProvider;

	class ItemSpriteFactory : public std::enable_shared_from_this<ItemSpriteFactory>
	{
	public:
		static std::shared_ptr<BufferedImage> createSprite(std::shared_ptr<ItemProvider> itemProvider, std::shared_ptr<ModelProvider> modelProvider, std::shared_ptr<SpriteProvider> spriteProvider, std::shared_ptr<TextureProvider> textureProvider, int itemId, int quantity, int border, int shadowColor, bool noted) final;

	private:
		static std::shared_ptr<SpritePixels> createSpritePixels(std::shared_ptr<ItemProvider> itemProvider, std::shared_ptr<ModelProvider> modelProvider, std::shared_ptr<SpriteProvider> spriteProvider, std::shared_ptr<TextureProvider> textureProvider, int itemId, int quantity, int border, int shadowColor, bool noted) final;

		static std::shared_ptr<Model> getModel(std::shared_ptr<ModelProvider> modelProvider, std::shared_ptr<ItemDefinition> item);

		static std::shared_ptr<Model> light(std::shared_ptr<ModelDefinition> def, int ambient, int contrast, int x, int y, int z);

	public:
		static int method2608(int var0, int var1) final;

		static int bound2to126(int var0) final;
	};

}
