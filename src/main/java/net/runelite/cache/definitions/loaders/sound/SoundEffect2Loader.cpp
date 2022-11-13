#include "SoundEffect2Loader.h"

namespace net::runelite::cache::definitions::loaders::sound
{
	using SoundEffect2Definition = net::runelite::cache::definitions::sound::SoundEffect2Definition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::shared_ptr<SoundEffect2Definition> SoundEffect2Loader::load(std::shared_ptr<InputStream> in)
	{
		std::shared_ptr<SoundEffect2Definition> se = std::make_shared<SoundEffect2Definition>();

		load(se, in);

		return se;
	}

	void SoundEffect2Loader::load(std::shared_ptr<SoundEffect2Definition> se, std::shared_ptr<InputStream> var1)
	{
		se->field1087 = var1->readUnsignedByte();
		se->field1088 = var1->readInt();
		se->field1089 = var1->readInt();
		this->method1144(se, var1);
	}

	void SoundEffect2Loader::method1144(std::shared_ptr<SoundEffect2Definition> se, std::shared_ptr<InputStream> var1)
	{
		se->field1092 = var1->readUnsignedByte();
		se->field1086 = std::vector<int>(se->field1092);
		se->field1090 = std::vector<int>(se->field1092);

		for (int var2 = 0; var2 < se->field1092; ++var2)
		{
			se->field1086[var2] = var1->readUnsignedShort();
			se->field1090[var2] = var1->readUnsignedShort();
		}

	}
}
