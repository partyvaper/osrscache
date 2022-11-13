#include "JagexColor.h"

namespace net::runelite::cache::models
{

const double JagexColor::HUE_OFFSET = (.5 / 64.D);
const double JagexColor::SATURATION_OFFSET = (.5 / 8.D);

	JagexColor::JagexColor()
	{
	}

	short JagexColor::packHSL(int hue, int saturation, int luminance)
	{
		return static_cast<short>(static_cast<short>(hue & 63) << 10 | static_cast<short>(saturation & 7) << 7 | static_cast<short>(luminance & 127));
	}

	int JagexColor::unpackHue(short hsl)
	{
		return hsl >> 10 & 63;
	}

	int JagexColor::unpackSaturation(short hsl)
	{
		return hsl >> 7 & 7;
	}

	int JagexColor::unpackLuminance(short hsl)
	{
		return hsl & 127;
	}

	std::wstring JagexColor::formatHSL(short hsl)
	{
		return String::format(L"%02Xh%Xs%02Xl", unpackHue(hsl), unpackSaturation(hsl), unpackLuminance(hsl));
	}

	int JagexColor::HSLtoRGB(short hsl, double brightness)
	{
		double hue = static_cast<double>(unpackHue(hsl)) / 64.D + HUE_OFFSET;
		double saturation = static_cast<double>(unpackSaturation(hsl)) / 8.D + SATURATION_OFFSET;
		double luminance = static_cast<double>(unpackLuminance(hsl)) / 128.D;

		// This is just a standard hsl to rgb transform
		// the only difference is the offsets above and the brightness transform below
		double chroma = (1.D - std::abs((2.D * luminance) - 1.D)) * saturation;
		double x = chroma * (1 - std::abs(((hue * 6.D) % 2.D) - 1.D));
		double lightness = luminance - (chroma / 2);

		double r = lightness, g = lightness, b = lightness;
		switch (static_cast<int>(hue * 6.D))
		{
			case 0:
				r += chroma;
				g += x;
				break;
			case 1:
				g += chroma;
				r += x;
				break;
			case 2:
				g += chroma;
				b += x;
				break;
			case 3:
				b += chroma;
				g += x;
				break;
			case 4:
				b += chroma;
				r += x;
				break;
			default:
				r += chroma;
				b += x;
				break;
		}

		int rgb = (static_cast<int>(r * 256.0) << 16) | (static_cast<int>(g * 256.0) << 8) | static_cast<int>(b * 256.0);

		rgb = adjustForBrightness(rgb, brightness);

		if (rgb == 0)
		{
			rgb = 1;
		}
		return rgb;
	}

	int JagexColor::adjustForBrightness(int rgb, double brightness)
	{
		double r = static_cast<double>(rgb >> 16) / 256.0;
		double g = static_cast<double>(rgb >> 8 & 255) / 256.0;
		double b = static_cast<double>(rgb & 255) / 256.0;

		r = std::pow(r, brightness);
		g = std::pow(g, brightness);
		b = std::pow(b, brightness);

		return (static_cast<int>(r * 256.0) << 16) | (static_cast<int>(g * 256.0) << 8) | static_cast<int>(b * 256.0);
	}

	std::vector<int> JagexColor::createPalette(double brightness)
	{
		std::vector<int> colorPalette(65536);
		for (int i = 0; i < colorPalette.size(); i++)
		{
			colorPalette[i] = HSLtoRGB(static_cast<short>(i), brightness);
		}
		return colorPalette;
	}
}
