using System;
using System.Diagnostics;

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
namespace OSRSCache
{
	using Store = OSRSCache.fs.Store;
	using Region = OSRSCache.region.Region;
	using RegionLoader = OSRSCache.region.RegionLoader;


	public class HeightMapDumper
	{
		private const int MAP_SCALE = 1;
		private const float MAX_HEIGHT = 2048f;

		private readonly Store store;
		private RegionLoader regionLoader;

		public HeightMapDumper(Store store)
		{
			this.store = store;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void load() throws java.io.IOException
		public virtual void load()
		{
			regionLoader = new RegionLoader(store);
			regionLoader.loadRegions();
			regionLoader.calculateBounds();
		}

		public virtual BufferedImage drawHeightMap(int z)
		{
			int minX = regionLoader.LowestX.BaseX;
			int minY = regionLoader.LowestY.BaseY;

			int maxX = regionLoader.HighestX.BaseX + Region.X;
			int maxY = regionLoader.HighestY.BaseY + Region.Y;

			int dimX = maxX - minX;
			int dimY = maxY - minY;

			dimX *= MAP_SCALE;
			dimY *= MAP_SCALE;

			Console.WriteLine("Map image dimensions: {}px x {}px, {}px per map square ({} MB)", dimX, dimY, MAP_SCALE, (dimX * dimY / 1024 / 1024));

			BufferedImage image = new BufferedImage(dimX, dimY, BufferedImage.TYPE_INT_RGB);
			draw(image, z);
			return image;
		}

		private void draw(BufferedImage image, int z)
		{
			int max = int.MinValue;
			int min = int.MaxValue;

			foreach (Region region in regionLoader.Regions)
			{
				int baseX = region.BaseX;
				int baseY = region.BaseY;

				// to pixel X
				int drawBaseX = baseX - regionLoader.LowestX.BaseX;

				// to pixel Y. top most y is 0, but the top most
				// region has the greatest y, so invert
				int drawBaseY = regionLoader.HighestY.BaseY - baseY;

				for (int x = 0; x < Region.X; ++x)
				{
					int drawX = drawBaseX + x;

					for (int y = 0; y < Region.Y; ++y)
					{
						int drawY = drawBaseY + (Region.Y - 1 - y);

						int height = region.getTileHeight(z, x, y);
						if (height > max)
						{
							max = height;
						}
						if (height < min)
						{
							min = height;
						}

						int rgb = toColor(height);

						drawMapSquare(image, drawX, drawY, rgb);
					}
				}
			}
			Console.WriteLine("max " + max);
			Console.WriteLine("min " + min);
		}

		private int toColor(int height)
		{
			// height seems to be between -2040 and 0, inclusive
			height = -height;
			// Convert to between 0 and 1
			float color = (float) height / MAX_HEIGHT;

			Debug.Assert(color >= 0.0f && color <= 1.0f);

			return (new Color(color, color, color)).getRGB();
		}

		private void drawMapSquare(BufferedImage image, int x, int y, int rgb)
		{
			x *= MAP_SCALE;
			y *= MAP_SCALE;

			for (int i = 0; i < MAP_SCALE; ++i)
			{
				for (int j = 0; j < MAP_SCALE; ++j)
				{
					image.setRGB(x + i, y + j, rgb);
				}
			}
		}
	}

}