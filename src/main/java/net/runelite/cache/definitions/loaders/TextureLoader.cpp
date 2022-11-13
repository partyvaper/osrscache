#include "TextureLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using TextureDefinition = net::runelite::cache::definitions::TextureDefinition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::shared_ptr<TextureDefinition> TextureLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<TextureDefinition> def = std::make_shared<TextureDefinition>();
		std::shared_ptr<InputStream> is = std::make_shared<InputStream>(b);

		def->field1777 = is->readUnsignedShort();
		def->field1778 = is->readByte() != 0;
		def->setId(id);

		int count = is->readUnsignedByte();
		std::vector<int> files(count);

		for (int i = 0; i < count; ++i)
		{
			files[i] = is->readUnsignedShort();
		}

		def->setFileIds(files);

		if (count > 1)
		{
			def->field1780 = std::vector<int>(count - 1);

			for (int var3 = 0; var3 < count - 1; ++var3)
			{
				def->field1780[var3] = is->readUnsignedByte();
			}
		}

		if (count > 1)
		{
			def->field1781 = std::vector<int>(count - 1);

			for (int var3 = 0; var3 < count - 1; ++var3)
			{
				def->field1781[var3] = is->readUnsignedByte();
			}
		}

		def->field1786 = std::vector<int>(count);

		for (int var3 = 0; var3 < count; ++var3)
		{
			def->field1786[var3] = is->readInt();
		}

		def->animationDirection = is->readUnsignedByte();
		def->animationSpeed = is->readUnsignedByte();

		return def;
	}
}
