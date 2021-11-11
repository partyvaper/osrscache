using System;

namespace OSRSCache.definitions
{
	using SpriteProvider = OSRSCache.definitions.providers.SpriteProvider;

	public class TextureDefinition
	{
		public int field1777;
		public bool field1778;
		public int id; // was private, is now public
		public int[] fileIds; // was private, is now public
		public int[] field1780;
		public int[] field1781;
		public int[] field1786;
		public int field1782;
		public int field1783;

		[NonSerialized]
		public int[] pixels;

		public virtual bool method2680(double var1, int var3, SpriteProvider spriteProvider)
		{
			int var5 = var3 * var3;
			this.pixels = new int[var5];

			for (int var6 = 0; var6 < this.fileIds.Length; ++var6)
			{
				SpriteDefinition var7 = spriteProvider.provide(fileIds[var6], 0);
				var7.normalize();
				byte[] var8 = var7.pixelIdx;
				int[] var9 = var7.palette;
				int var10 = this.field1786[var6];

				int var11;
				int var12;
				int var13;
				int var14;
				if ((var10 & -16777216) == 50331648)
				{
					var11 = var10 & 16711935;
					var12 = var10 >> 8 & 255;

					for (var13 = 0; var13 < var9.Length; ++var13)
					{
						var14 = var9[var13];
						if (var14 >> 8 == (var14 & 65535))
						{
							var14 &= 255;
							var9[var13] = var11 * var14 >> 8 & 16711935 | var12 * var14 & 65280;
						}
					}
				}

				for (var11 = 0; var11 < var9.Length; ++var11)
				{
					var9[var11] = adjustRGB(var9[var11], var1);
				}

				if (var6 == 0)
				{
					var11 = 0;
				}
				else
				{
					var11 = this.field1780[var6 - 1];
				}

				if (var11 == 0)
				{
					if (var3 == var7.maxWidth)
					{
						for (var12 = 0; var12 < var5; ++var12)
						{
							this.pixels[var12] = var9[var8[var12] & 255];
						}
					}
					else if (var7.maxWidth == 64 && var3 == 128)
					{
						var12 = 0;

						for (var13 = 0; var13 < var3; ++var13)
						{
							for (var14 = 0; var14 < var3; ++var14)
							{
								this.pixels[var12++] = var9[var8[(var13 >> 1 << 6) + (var14 >> 1)] & 255];
							}
						}
					}
					else
					{
						if (var7.maxWidth != 128 || var3 != 64)
						{
							throw new Exception();
						}

						var12 = 0;

						for (var13 = 0; var13 < var3; ++var13)
						{
							for (var14 = 0; var14 < var3; ++var14)
							{
								this.pixels[var12++] = var9[var8[(var14 << 1) + (var13 << 1 << 7)] & 255];
							}
						}
					}
				}
			}

			return true;
		}

		internal static int adjustRGB(int var0, double var1)
		{
			double var3 = (double)(var0 >> 16) / 256.0D;
			double var5 = (double)(var0 >> 8 & 255) / 256.0D;
			double var7 = (double)(var0 & 255) / 256.0D;
			var3 = Math.Pow(var3, var1);
			var5 = Math.Pow(var5, var1);
			var7 = Math.Pow(var7, var1);
			int var9 = (int)(var3 * 256.0D);
			int var10 = (int)(var5 * 256.0D);
			int var11 = (int)(var7 * 256.0D);
			return var11 + (var10 << 8) + (var9 << 16);
		}
	}

}