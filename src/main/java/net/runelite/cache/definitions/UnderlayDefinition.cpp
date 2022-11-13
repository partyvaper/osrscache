#include "UnderlayDefinition.h"

namespace net::runelite::cache::definitions
{
	using Data = lombok::Data;

	void UnderlayDefinition::calculateHsl()
	{
		int var1 = color;
		double var2 = static_cast<double>(var1 >> 16 & 255) / 256.0;
		double var4 = static_cast<double>(var1 >> 8 & 255) / 256.0;
		double var6 = static_cast<double>(var1 & 255) / 256.0;
		double var8 = var2;
		if (var4 < var2)
		{
			var8 = var4;
		}

		if (var6 < var8)
		{
			var8 = var6;
		}

		double var10 = var2;
		if (var4 > var2)
		{
			var10 = var4;
		}

		if (var6 > var10)
		{
			var10 = var6;
		}

		double var12 = 0.0;
		double var14 = 0.0;
		double var16 = (var10 + var8) / 2.0;
		if (var8 != var10)
		{
			if (var16 < 0.5)
			{
				var14 = (var10 - var8) / (var8 + var10);
			}

			if (var16 >= 0.5)
			{
				var14 = (var10 - var8) / (2.0 - var10 - var8);
			}

			if (var2 == var10)
			{
				var12 = (var4 - var6) / (var10 - var8);
			}
			else if (var10 == var4)
			{
				var12 = 2.0 + (var6 - var2) / (var10 - var8);
			}
			else if (var10 == var6)
			{
				var12 = 4.0 + (var2 - var4) / (var10 - var8);
			}
		}

		var12 /= 6.0;
		this->saturation = static_cast<int>(var14 * 256.0);
		this->lightness = static_cast<int>(var16 * 256.0);
		if (this->saturation < 0)
		{
			this->saturation = 0;
		}
		else if (this->saturation > 255)
		{
			this->saturation = 255;
		}

		if (this->lightness < 0)
		{
			this->lightness = 0;
		}
		else if (this->lightness > 255)
		{
			this->lightness = 255;
		}

		if (var16 > 0.5)
		{
			this->hueMultiplier = static_cast<int>(var14 * (1.0 - var16) * 512.0);
		}
		else
		{
			this->hueMultiplier = static_cast<int>(var14 * var16 * 512.0);
		}

		if (this->hueMultiplier < 1)
		{
			this->hueMultiplier = 1;
		}

		this->hue = static_cast<int>(static_cast<double>(this->hueMultiplier) * var12);
	}
}
