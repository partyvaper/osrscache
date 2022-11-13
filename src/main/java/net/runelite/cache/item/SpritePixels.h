#pragma once

#include "Rasterizer2D.h"
#include <vector>
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

	class SpritePixels : public std::enable_shared_from_this<SpritePixels>
	{
	public:
		std::vector<int> pixels;
		int width = 0;
		int height = 0;
		int offsetX = 0;
		int offsetY = 0;

		SpritePixels(std::vector<int> &var1, int var2, int var3);

		SpritePixels(int var1, int var2);

		virtual void drawBorder(int color);


		virtual void drawShadow(int color);

		virtual void drawAtOn(std::shared_ptr<Rasterizer2D> graphics, int x, int y);

		static void method5843(std::vector<int> &rasterizerPixels, std::vector<int> &spritePixels, int var2, int var3, int pixelIndex, int width, int height, int var7, int var8);

		virtual std::shared_ptr<BufferedImage> toBufferedImage();

	};

}
