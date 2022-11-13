#include "Rasterizer2D.h"

namespace net::runelite::cache::item
{

	void Rasterizer2D::setRasterBuffer(std::vector<int> &var0, int var1, int var2)
	{
		graphicsPixels = var0;
		graphicsPixelsWidth = var1;
		graphicsPixelsHeight = var2;
		setDrawRegion(0, 0, var1, var2);
	}

	void Rasterizer2D::setDrawRegion(int var0, int var1, int var2, int var3)
	{
		if (var0 < 0)
		{
			var0 = 0;
		}

		if (var1 < 0)
		{
			var1 = 0;
		}

		if (var2 > graphicsPixelsWidth)
		{
			var2 = graphicsPixelsWidth;
		}

		if (var3 > graphicsPixelsHeight)
		{
			var3 = graphicsPixelsHeight;
		}

		draw_region_x = var0;
		drawingAreaTop = var1;
		drawingAreaRight = var2;
		drawingAreaBottom = var3;
	}

	void Rasterizer2D::reset()
	{
		int var0 = 0;

		int var1;
		for (var1 = graphicsPixelsWidth * graphicsPixelsHeight - 7; var0 < var1; graphicsPixels[var0++] = 0)
		{
			graphicsPixels[var0++] = 0;
			graphicsPixels[var0++] = 0;
			graphicsPixels[var0++] = 0;
			graphicsPixels[var0++] = 0;
			graphicsPixels[var0++] = 0;
			graphicsPixels[var0++] = 0;
			graphicsPixels[var0++] = 0;
		}

		for (std::shared_ptr<var1> += 7; var0 < var1; graphicsPixels[var0++] = 0)
		{
			;
		}

	}
}
