#include "SoundEffect3Loader.h"

namespace net::runelite::cache::definitions::loaders::sound
{
	using SoundEffect2Definition = net::runelite::cache::definitions::sound::SoundEffect2Definition;
	using SoundEffect3Definition = net::runelite::cache::definitions::sound::SoundEffect3Definition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::shared_ptr<SoundEffect3Definition> SoundEffect3Loader::load(std::shared_ptr<InputStream> in, std::shared_ptr<SoundEffect2Definition> var2)
	{
		std::shared_ptr<SoundEffect3Definition> se = std::make_shared<SoundEffect3Definition>();

		load(se, in, var2);

		return se;
	}

	void SoundEffect3Loader::load(std::shared_ptr<SoundEffect3Definition> se, std::shared_ptr<InputStream> var1, std::shared_ptr<SoundEffect2Definition> var2)
	{
		int var3 = var1->readUnsignedByte();
		se->field1155[0] = var3 >> 4;
		se->field1155[1] = var3 & 15;
		if (var3 != 0)
		{
			se->field1156[0] = var1->readUnsignedShort();
			se->field1156[1] = var1->readUnsignedShort();
			int var4 = var1->readUnsignedByte();

			int var5;
			int var6;
			for (var5 = 0; var5 < 2; ++var5)
			{
				for (var6 = 0; var6 < se->field1155[var5]; ++var6)
				{
					se->field1154[var5][0][var6] = var1->readUnsignedShort();
					se->field1159[var5][0][var6] = var1->readUnsignedShort();
				}
			}

			for (var5 = 0; var5 < 2; ++var5)
			{
				for (var6 = 0; var6 < se->field1155[var5]; ++var6)
				{
					if ((var4 & 1 << var5 * 4 << var6) != 0)
					{
						se->field1154[var5][1][var6] = var1->readUnsignedShort();
						se->field1159[var5][1][var6] = var1->readUnsignedShort();
					}
					else
					{
						se->field1154[var5][1][var6] = se->field1154[var5][0][var6];
						se->field1159[var5][1][var6] = se->field1159[var5][0][var6];
					}
				}
			}

			if (var4 != 0 || se->field1156[1] != se->field1156[0])
			{
				se2Loader->method1144(var2, var1);
			}
		}
		else
		{
			std::vector<int> var7 = se->field1156;
			se->field1156[1] = 0;
			var7[0] = 0;
		}
	}
}
