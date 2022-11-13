#include "SpritePixels.h"

namespace net::runelite::cache::item
{
	using BufferedImage = java::awt::image::BufferedImage;

	SpritePixels::SpritePixels(std::vector<int> &var1, int var2, int var3)
	{
		this->pixels = var1;
		this->width = var2;
		this->height = var3;
		this->offsetY = 0;
		this->offsetX = 0;
	}

	SpritePixels::SpritePixels(int var1, int var2) : SpritePixels(std::vector<int>(var2 * var1), var1, var2)
	{
	}

	void SpritePixels::drawBorder(int color)
	{
		std::vector<int> newPixels(this->width * this->height);
		int pixelIndex = 0;

		for (int y = 0; y < this->height; ++y)
		{
			for (int x = 0; x < this->width; ++x)
			{
				int pixel = this->pixels[pixelIndex];
				if (pixel == 0)
				{
					// W
					if (x > 0 && this->pixels[pixelIndex - 1] != 0)
					{
						pixel = color;
					}
					// N
					else if (y > 0 && this->pixels[pixelIndex - this->width] != 0)
					{
						pixel = color;
					}
					// E
					else if (x < this->width - 1 && this->pixels[pixelIndex + 1] != 0)
					{
						pixel = color;
					}
					// S
					else if (y < this->height - 1 && this->pixels[pixelIndex + this->width] != 0)
					{
						pixel = color;
					}
				}

				newPixels[pixelIndex++] = pixel;
			}
		}

		this->pixels = newPixels;
	}

	void SpritePixels::drawShadow(int color)
	{
		for (int y = this->height - 1; y > 0; --y)
		{
			int rowOffset = y * this->width;

			for (int x = this->width - 1; x > 0; --x)
			{
				// if *this* pixel is black/unset AND the pixel to the NW isn't black/unset
				if (this->pixels[x + rowOffset] == 0 && this->pixels[x + rowOffset - 1 - this->width] != 0)
				{
					this->pixels[x + rowOffset] = color;
				}
			}
		}

	}

	void SpritePixels::drawAtOn(std::shared_ptr<Rasterizer2D> graphics, int x, int y)
	{
		x += this->offsetX;
		y += this->offsetY;
		int pixelIndex = x + y * graphics->graphicsPixelsWidth;
		int deltaIndex = 0;
		int height = this->height;
		int width = this->width;
		int var7 = graphics->graphicsPixelsWidth - width;
		int var8 = 0;
		if (y < graphics->drawingAreaTop)
		{
			int deltaY = graphics->drawingAreaTop - y;
			height -= deltaY;
			y = graphics->drawingAreaTop;
			deltaIndex += deltaY * width;
			pixelIndex += deltaY * graphics->graphicsPixelsWidth;
		}

		if (height + y > graphics->drawingAreaBottom)
		{
			height -= height + y - graphics->drawingAreaBottom;
		}

		if (x < graphics->draw_region_x)
		{
			int deltaX = graphics->draw_region_x - x;
			width -= deltaX;
			x = graphics->draw_region_x;
			deltaIndex += deltaX;
			pixelIndex += deltaX;
			var8 += deltaX;
			var7 += deltaX;
		}

		if (width + x > graphics->drawingAreaRight)
		{
			int deltaX = width + x - graphics->drawingAreaRight;
			width -= deltaX;
			var8 += deltaX;
			var7 += deltaX;
		}

		if (width > 0 && height > 0)
		{
			method5843(graphics->graphicsPixels, this->pixels, 0, deltaIndex, pixelIndex, width, height, var7, var8);
		}
	}

	void SpritePixels::method5843(std::vector<int> &rasterizerPixels, std::vector<int> &spritePixels, int var2, int var3, int pixelIndex, int width, int height, int var7, int var8)
	{
		int var9 = -(width >> 2);
		width = -(width & 3);

		for (int var10 = -height; var10 < 0; ++var10)
		{
			for (int i = var9 * 4; i < 0; ++i)
			{
				var2 = spritePixels[var3++];
				if (var2 != 0)
				{
					rasterizerPixels[pixelIndex++] = var2;
				}
				else
				{
					++pixelIndex;
				}
			}

			for (int i = width; i < 0; ++i)
			{
				var2 = spritePixels[var3++];
				if (var2 != 0)
				{
					rasterizerPixels[pixelIndex++] = var2;
				}
				else
				{
					++pixelIndex;
				}
			}

			pixelIndex += var7;
			var3 += var8;
		}

	}

	std::shared_ptr<BufferedImage> SpritePixels::toBufferedImage()
	{
		std::vector<int> transPixels(pixels.size());
		std::shared_ptr<BufferedImage> img = std::make_shared<BufferedImage>(width, height, BufferedImage::TYPE_INT_ARGB);

		for (int i = 0; i < pixels.size(); i++)
		{
			if (pixels[i] != 0)
			{
				transPixels[i] = pixels[i] | 0xff000000;
			}
		}

		img->setRGB(0, 0, width, height, transPixels, 0, width);
		return img;
	}
}
