#include "SpriteLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using SpriteDefinition = net::runelite::cache::definitions::SpriteDefinition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::vector<std::shared_ptr<SpriteDefinition>> SpriteLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<InputStream> is = std::make_shared<InputStream>(b);

		is->setOffset(is->getLength() - 2);
		int spriteCount = is->readUnsignedShort();

		std::vector<std::shared_ptr<SpriteDefinition>> sprites(spriteCount);

		// 2 for size
		// 5 for width, height, palette length
		// + 8 bytes per sprite for offset x/y, width, and height
		is->setOffset(is->getLength() - 7 - spriteCount * 8);

		// max width and height
		int width = is->readUnsignedShort();
		int height = is->readUnsignedShort();
		int paletteLength = is->readUnsignedByte() + 1;

		for (int i = 0; i < spriteCount; ++i)
		{
			sprites[i] = std::make_shared<SpriteDefinition>();
			sprites[i]->setId(id);
			sprites[i]->setFrame(i);
			sprites[i]->setMaxWidth(width);
			sprites[i]->setMaxHeight(height);
		}

		for (int i = 0; i < spriteCount; ++i)
		{
			sprites[i]->setOffsetX(is->readUnsignedShort());
		}

		for (int i = 0; i < spriteCount; ++i)
		{
			sprites[i]->setOffsetY(is->readUnsignedShort());
		}

		for (int i = 0; i < spriteCount; ++i)
		{
			sprites[i]->setWidth(is->readUnsignedShort());
		}

		for (int i = 0; i < spriteCount; ++i)
		{
			sprites[i]->setHeight(is->readUnsignedShort());
		}

		// same as above + 3 bytes for each palette entry, except for the first one (which is transparent)
		is->setOffset(is->getLength() - 7 - spriteCount * 8 - (paletteLength - 1) * 3);
		std::vector<int> palette(paletteLength);

		for (int i = 1; i < paletteLength; ++i)
		{
			palette[i] = is->read24BitInt();

			if (palette[i] == 0)
			{
				palette[i] = 1;
			}
		}

		is->setOffset(0);

		for (int i = 0; i < spriteCount; ++i)
		{
			std::shared_ptr<SpriteDefinition> def = sprites[i];
			int spriteWidth = def->getWidth();
			int spriteHeight = def->getHeight();
			int dimension = spriteWidth * spriteHeight;
			std::vector<signed char> pixelPaletteIndicies(dimension);
			std::vector<signed char> pixelAlphas(dimension);
			def->pixelIdx = pixelPaletteIndicies;
			def->palette = palette;

			int flags = is->readUnsignedByte();

			if ((flags & FLAG_VERTICAL) == 0)
			{
				// read horizontally
				for (int j = 0; j < dimension; ++j)
				{
					pixelPaletteIndicies[j] = is->readByte();
				}
			}
			else
			{
				// read vertically
				for (int j = 0; j < spriteWidth; ++j)
				{
					for (int k = 0; k < spriteHeight; ++k)
					{
						pixelPaletteIndicies[spriteWidth * k + j] = is->readByte();
					}
				}
			}

			// read alphas
			if ((flags & FLAG_ALPHA) != 0)
			{
				if ((flags & FLAG_VERTICAL) == 0)
				{
					// read horizontally
					for (int j = 0; j < dimension; ++j)
					{
						pixelAlphas[j] = is->readByte();
					}
				}
				else
				{
					// read vertically
					for (int j = 0; j < spriteWidth; ++j)
					{
						for (int k = 0; k < spriteHeight; ++k)
						{
							pixelAlphas[spriteWidth * k + j] = is->readByte();
						}
					}
				}
			}
			else
			{
				// everything non-zero is opaque
				for (int j = 0; j < dimension; ++j)
				{
					int index = pixelPaletteIndicies[j];

					if (index != 0)
					{
						pixelAlphas[j] = static_cast<signed char>(0xFF);
					}
				}
			}

			std::vector<int> pixels(dimension);

			// build argb pixels from palette/alphas
			for (int j = 0; j < dimension; ++j)
			{
				int index = pixelPaletteIndicies[j] & 0xFF;

				pixels[j] = palette[index] | (pixelAlphas[j] << 24);
			}

			def->setPixels(pixels);
		}

		return sprites;
	}
}
