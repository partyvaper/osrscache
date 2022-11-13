#include "JagexColorTest.h"
#include "../../../../../../main/java/net/runelite/cache/models/JagexColor.h"

namespace net::runelite::cache::models
{
//	import static org.junit.Assert.assertEquals;
	using Test = org::junit::Test;
const std::vector<double> JagexColorTest::BRIGHTNESS_LEVELS = {JagexColor::BRIGHTNESS_MIN, JagexColor::BRIGHTNESS_LOW, JagexColor::BRIGHTNESS_HIGH, JagexColor::BRIGHTNESS_MAX};

	std::vector<int> JagexColorTest::computeColorTable(double brightness, int min, int max)
	{
		std::vector<int> colorPalette(65536);
		int var4 = min * 128;

		for (int var5 = min; var5 < max; ++var5)
		{
			double var6 = static_cast<double>(var5 >> 3) / 64.0 + 0.0078125;
			double var8 = static_cast<double>(var5 & 7) / 8.0 + 0.0625;

			for (int var10 = 0; var10 < 128; ++var10)
			{
				double var11 = static_cast<double>(var10) / 128.0;
				double var13 = var11;
				double var15 = var11;
				double var17 = var11;
				if (var8 != 0.0)
				{
					double var19;
					if (var11 < 0.5)
					{
						var19 = var11 * (1.0 + var8);
					}
					else
					{
						var19 = var11 + var8 - var11 * var8;
					}

					double var21 = 2.0 * var11 - var19;
					double var23 = var6 + 0.3333333333333333;
					if (var23 > 1.0)
					{
						--var23;
					}

					double var27 = var6 - 0.3333333333333333;
					if (var27 < 0.0)
					{
						++var27;
					}

					if (6.0 * var23 < 1.0)
					{
						var13 = var21 + (var19 - var21) * 6.0 * var23;
					}
					else if (2.0 * var23 < 1.0)
					{
						var13 = var19;
					}
					else if (3.0 * var23 < 2.0)
					{
						var13 = var21 + (var19 - var21) * (0.6666666666666666 - var23) * 6.0;
					}
					else
					{
						var13 = var21;
					}

					if (6.0 * var6 < 1.0)
					{
						var15 = var21 + (var19 - var21) * 6.0 * var6;
					}
					else if (2.0 * var6 < 1.0)
					{
						var15 = var19;
					}
					else if (3.0 * var6 < 2.0)
					{
						var15 = var21 + (var19 - var21) * (0.6666666666666666 - var6) * 6.0;
					}
					else
					{
						var15 = var21;
					}

					if (6.0 * var27 < 1.0)
					{
						var17 = var21 + (var19 - var21) * 6.0 * var27;
					}
					else if (2.0 * var27 < 1.0)
					{
						var17 = var19;
					}
					else if (3.0 * var27 < 2.0)
					{
						var17 = var21 + (var19 - var21) * (0.6666666666666666 - var27) * 6.0;
					}
					else
					{
						var17 = var21;
					}
				}

				int var29 = static_cast<int>(var13 * 256.0);
				int var20 = static_cast<int>(var15 * 256.0);
				int var30 = static_cast<int>(var17 * 256.0);
				int var22 = var30 + (var20 << 8) + (var29 << 16);
				var22 = adjustForBrightness(var22, brightness);
				if (var22 == 0)
				{
					var22 = 1;
				}

				colorPalette[var4++] = var22;
			}
		}

		return colorPalette;
	}

	int JagexColorTest::adjustForBrightness(int rgb, double brightness)
	{
		double var3 = static_cast<double>(rgb >> 16) / 256.0;
		double var5 = static_cast<double>(rgb >> 8 & 255) / 256.0;
		double var7 = static_cast<double>(rgb & 255) / 256.0;
		var3 = std::pow(var3, brightness);
		var5 = std::pow(var5, brightness);
		var7 = std::pow(var7, brightness);
		int var9 = static_cast<int>(var3 * 256.0);
		int var10 = static_cast<int>(var5 * 256.0);
		int var11 = static_cast<int>(var7 * 256.0);
		return var11 + (var10 << 8) + (var9 << 16);
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test public void testHslToRgb()
	void JagexColorTest::testHslToRgb()
	{
		for (auto brightness : BRIGHTNESS_LEVELS)
		{
			std::vector<int> colorPalette = computeColorTable(brightness, 0, 512);
			for (int i = 0; i < 0xFFFF; i++)
			{
				int rgb = JagexColor::HSLtoRGB(static_cast<short>(i), brightness);
				int crgb = colorPalette[i];
				assertEquals(L"idx " + std::to_wstring(i) + L" brightness " + std::to_wstring(brightness), crgb, rgb);
			}
		}
	}
}
