#include "SpriteDefinition.h"

namespace net::runelite::cache::definitions
{
	using Data = lombok::Data;

	void SpriteDefinition::normalize()
	{
		if (this->width != this->maxWidth || this->height != this->maxHeight)
		{
			std::vector<signed char> var1(this->maxWidth * this->maxHeight);
			int var2 = 0;

			for (int var3 = 0; var3 < this->height; ++var3)
			{
				for (int var4 = 0; var4 < this->width; ++var4)
				{
					var1[var4 + (var3 + this->offsetY) * this->maxWidth + this->offsetX] = this->pixelIdx[var2++];
				}
			}

			this->pixelIdx = var1;
			this->width = this->maxWidth;
			this->height = this->maxHeight;
			this->offsetX = 0;
			this->offsetY = 0;
		}
	}
}
