#include "SoundEffect1Loader.h"

namespace net::runelite::cache::definitions::loaders::sound
{
	using SoundEffect1Definition = net::runelite::cache::definitions::sound::SoundEffect1Definition;
	using SoundEffect2Definition = net::runelite::cache::definitions::sound::SoundEffect2Definition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::shared_ptr<SoundEffect1Definition> SoundEffect1Loader::load(std::shared_ptr<InputStream> in)
	{
		std::shared_ptr<SoundEffect1Definition> se = std::make_shared<SoundEffect1Definition>();

		load(se, in);

		return se;
	}

	void SoundEffect1Loader::load(std::shared_ptr<SoundEffect1Definition> se, std::shared_ptr<InputStream> var1)
	{
		se->field1181 = se2Loader->load(var1);
		se->field1173 = se2Loader->load(var1);
		int var2 = var1->readUnsignedByte();
		if (var2 != 0)
		{
			var1->setOffset(var1->getOffset() - 1);
			se->field1174 = se2Loader->load(var1);
			se->field1193 = se2Loader->load(var1);
		}

		var2 = var1->readUnsignedByte();
		if (var2 != 0)
		{
			var1->setOffset(var1->getOffset() - 1);
			se->field1183 = se2Loader->load(var1);
			se->field1192 = se2Loader->load(var1);
		}

		var2 = var1->readUnsignedByte();
		if (var2 != 0)
		{
			var1->setOffset(var1->getOffset() - 1);
			se->field1178 = se2Loader->load(var1);
			se->field1175 = se2Loader->load(var1);
		}

		for (int var3 = 0; var3 < 10; ++var3)
		{
			int var4 = var1->readUnsignedShortSmart();
			if (var4 == 0)
			{
				break;
			}

			se->field1180[var3] = var4;
			se->field1179[var3] = var1->readShortSmart();
			se->field1177[var3] = var1->readUnsignedShortSmart();
		}

		se->field1187 = var1->readUnsignedShortSmart();
		se->field1184 = var1->readUnsignedShortSmart();
		se->field1176 = var1->readUnsignedShort();
		se->field1188 = var1->readUnsignedShort();
		se->field1186 = std::make_shared<SoundEffect2Definition>();
		se->field1182 = se3Loader->load(var1, se->field1186);
	}
}
