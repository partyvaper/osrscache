#include "TextureDefinition.h"
#include "SpriteDefinition.h"

namespace net::runelite::cache::definitions
{
	using Data = lombok::Data;
	using SpriteProvider = net::runelite::cache::definitions::providers::SpriteProvider;

	bool TextureDefinition::method2680(double var1, int var3, std::shared_ptr<SpriteProvider> spriteProvider)
	{
		int var5 = var3 * var3;
		this->pixels = std::vector<int>(var5);

		for (int var6 = 0; var6 < this->fileIds.size(); ++var6)
		{
			std::shared_ptr<SpriteDefinition> var7 = spriteProvider->provide(fileIds[var6], 0);
			var7->normalize();
			std::vector<signed char> var8 = var7->pixelIdx;
			std::vector<int> var9 = var7->palette;
			int var10 = this->field1786[var6];

			int var11;
			int var12;
			int var13;
			int var14;
			if ((var10 & -16777216) == 50331648)
			{
				var11 = var10 & 16711935;
				var12 = var10 >> 8 & 255;

				for (var13 = 0; var13 < var9.size(); ++var13)
				{
					var14 = var9[var13];
					if (var14 >> 8 == (var14 & 65535))
					{
						var14 &= 255;
						var9[var13] = var11 * var14 >> 8 & 16711935 | var12 * var14 & 65280;
					}
				}
			}

			for (var11 = 0; var11 < var9.size(); ++var11)
			{
				var9[var11] = adjustRGB(var9[var11], var1);
			}

			if (var6 == 0)
			{
				var11 = 0;
			}
			else
			{
				var11 = this->field1780[var6 - 1];
			}

			if (var11 == 0)
			{
				if (var3 == var7->getMaxWidth())
				{
					for (var12 = 0; var12 < var5; ++var12)
					{
						this->pixels[var12] = var9[var8[var12] & 255];
					}
				}
				else if (var7->getMaxWidth() == 64 && var3 == 128)
				{
					var12 = 0;

					for (var13 = 0; var13 < var3; ++var13)
					{
						for (var14 = 0; var14 < var3; ++var14)
						{
							this->pixels[var12++] = var9[var8[(var13 >> 1 << 6) + (var14 >> 1)] & 255];
						}
					}
				}
				else
				{
					if (var7->getMaxWidth() != 128 || var3 != 64)
					{
//JAVA TO C++ CONVERTER TODO TASK: This exception's constructor requires an argument:
//ORIGINAL LINE: throw new RuntimeException();
						throw std::runtime_error();
					}

					var12 = 0;

					for (var13 = 0; var13 < var3; ++var13)
					{
						for (var14 = 0; var14 < var3; ++var14)
						{
							this->pixels[var12++] = var9[var8[(var14 << 1) + (var13 << 1 << 7)] & 255];
						}
					}
				}
			}
		}

		return true;
	}

	int TextureDefinition::adjustRGB(int var0, double var1)
	{
		double var3 = static_cast<double>(var0 >> 16) / 256.0;
		double var5 = static_cast<double>(var0 >> 8 & 255) / 256.0;
		double var7 = static_cast<double>(var0 & 255) / 256.0;
		var3 = std::pow(var3, var1);
		var5 = std::pow(var5, var1);
		var7 = std::pow(var7, var1);
		int var9 = static_cast<int>(var3 * 256.0);
		int var10 = static_cast<int>(var5 * 256.0);
		int var11 = static_cast<int>(var7 * 256.0);
		return var11 + (var10 << 8) + (var9 << 16);
	}
}
