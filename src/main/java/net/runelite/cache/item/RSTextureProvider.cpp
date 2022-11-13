#include "RSTextureProvider.h"

namespace net::runelite::cache::item
{
	using TextureDefinition = net::runelite::cache::definitions::TextureDefinition;
	using SpriteProvider = net::runelite::cache::definitions::providers::SpriteProvider;
	using TextureProvider = net::runelite::cache::definitions::providers::TextureProvider;

	RSTextureProvider::RSTextureProvider(std::shared_ptr<TextureProvider> textureProvider, std::shared_ptr<SpriteProvider> spriteProvider) : spriteProvider(spriteProvider)
	{
		this->size = 0;
		this->brightness = 1.0;
		this->width = 128;
		this->maxSize = 20;
		this->size = this->maxSize;
		this->brightness = 0.8;
		this->width = 128;

		int max = -1;
		for (auto textureDefinition : textureProvider->provide())
		{
			if (textureDefinition->getId() > max)
			{
				max = textureDefinition->getId();
			}
		}

		textures = std::vector<std::shared_ptr<TextureDefinition>>(max + 1);
		for (auto textureDefinition : textureProvider->provide())
		{
			textures[textureDefinition->getId()] = textureDefinition;
		}
	}

	std::vector<int> RSTextureProvider::load(int var1)
	{
		std::shared_ptr<TextureDefinition> var2 = this->textures[var1];
		if (var2 != nullptr)
		{
			{
					std::scoped_lock<std::mutex> lock(var2);
				if (!var2->pixels.empty())
				{
					return var2->pixels;
				}

				var2->method2680(this->brightness, this->width, spriteProvider);
				return var2->pixels;
			}
		}

		return std::vector<int>();
	}

	int RSTextureProvider::getAverageTextureRGB(int var1)
	{
		return this->textures[var1] != nullptr ? this->textures[var1]->field1777 : 0;
	}

	bool RSTextureProvider::vmethod3057(int var1)
	{
		return this->textures[var1]->field1778;
	}

	bool RSTextureProvider::vmethod3066(int var1)
	{
		return this->width == 64;
	}
}
