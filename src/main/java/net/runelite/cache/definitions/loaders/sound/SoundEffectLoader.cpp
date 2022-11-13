#include "SoundEffectLoader.h"
#include "SoundEffect1Loader.h"

namespace net::runelite::cache::definitions::loaders::sound
{
	using SoundEffectDefinition = net::runelite::cache::definitions::sound::SoundEffectDefinition;
	using SoundEffect1Definition = net::runelite::cache::definitions::sound::SoundEffect1Definition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::shared_ptr<SoundEffectDefinition> SoundEffectLoader::load(std::vector<signed char> &b)
	{
		std::shared_ptr<SoundEffectDefinition> se = std::make_shared<SoundEffectDefinition>();
		std::shared_ptr<InputStream> in = std::make_shared<InputStream>(b);

		load(se, in);

		return se;
	}

	void SoundEffectLoader::load(std::shared_ptr<SoundEffectDefinition> se, std::shared_ptr<InputStream> var1)
	{
		for (int var2 = 0; var2 < 10; ++var2)
		{
			int var3 = var1->readUnsignedByte();
			if (var3 != 0)
			{
				var1->setOffset(var1->getOffset() - 1);

				std::shared_ptr<SoundEffect1Loader> se1Loader = std::make_shared<SoundEffect1Loader>();
				std::shared_ptr<SoundEffect1Definition> se1 = se1Loader->load(var1);

				se->field1008[var2] = se1;
			}
		}

		se->field1006 = var1->readUnsignedShort();
		se->field1009 = var1->readUnsignedShort();
	}
}
