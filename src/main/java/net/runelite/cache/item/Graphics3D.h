#pragma once

#include "../models/JagexColor.h"
#include "Rasterizer2D.h"
#include "RSTextureProvider.h"
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


	class Graphics3D : public Rasterizer2D
	{
	private:
		static const double UNIT; // How much of the circle each unit of SINE/COSINE is

	public:
		static const std::vector<int> SINE; // sine angles for each of the 2048 units, * 65536 and stored as an int
		static const std::vector<int> COSINE; // cosine

	private:
		static std::vector<int> field1932;
	public:
		static std::vector<int> field1933;

		private:
			class StaticConstructor : public std::enable_shared_from_this<StaticConstructor>
			{
			public:
				StaticConstructor();
			};

		private:
			static Graphics3D::StaticConstructor staticConstructor;


		const std::shared_ptr<RSTextureProvider> textureProvider;
	public:
		bool rasterClipEnable = false;
		bool field1909 = false;
		bool lowMem = false;
		bool rasterGouraudLowRes = true;
		int rasterAlpha = 0;
		int Rasterizer3D_zoom = 512;
		int centerX = 0;
		int centerY = 0;
		int rasterClipX = 0;
		int Rasterizer3D_clipHeight = 0;
		int Rasterizer3D_clipNegativeMidX = 0;
		int Rasterizer3D_clipMidX2 = 0;
		int Rasterizer3D_clipNegativeMidY = 0;
		int Rasterizer3D_clipMidY2 = 0;
		std::vector<int> rasterClipY = std::vector<int>(1024);
		std::vector<int> colorPalette;

		Graphics3D(std::shared_ptr<RSTextureProvider> textureProvider);

		void setRasterClipping();

		void setRasterClipping(int var0, int var1, int var2, int var3);

		void Rasterizer3D_method3();

		void setOffset(int x, int y);

		void setBrightness(double brightness);

		void rasterGouraud(int var0, int var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8);


		void method2778(std::vector<int> &var0, int var1, int var2, int var3, int var4, int var5, int var6, int var7);


		void rasterFlat(int var0, int var1, int var2, int var3, int var4, int var5, int var6);


		void method2842(std::vector<int> &var0, int var1, int var2, int var3, int var4, int var5);


		void rasterTextureAffine(int var0, int var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, int var10, int var11, int var12, int var13, int var14, int var15, int var16, int var17, int var18);


		void method2791(std::vector<int> &var0, std::vector<int> &var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, int var10, int var11, int var12, int var13, int var14);

		static int method2794(int var0, int var1) final;

	protected:
		std::shared_ptr<Graphics3D> shared_from_this()
		{
			return std::static_pointer_cast<Graphics3D>(Rasterizer2D::shared_from_this());
		}
	};

}
