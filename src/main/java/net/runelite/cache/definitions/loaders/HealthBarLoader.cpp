#include "HealthBarLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using HealthBarDefinition = net::runelite::cache::definitions::HealthBarDefinition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::shared_ptr<HealthBarDefinition> HealthBarLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<HealthBarDefinition> def = std::make_shared<HealthBarDefinition>();
		std::shared_ptr<InputStream> is = std::make_shared<InputStream>(b);
		def->id = id;

		while (true)
		{
			int opcode = is->readUnsignedByte();
			if (opcode == 0)
			{
				break;
			}

			this->decodeValues(opcode, def, is);
		}

		return def;
	}

	void HealthBarLoader::decodeValues(int opcode, std::shared_ptr<HealthBarDefinition> def, std::shared_ptr<InputStream> stream)
	{
		if (opcode == 1)
		{
			stream->readUnsignedShort();
		}
		else if (opcode == 2)
		{
			def->field3277 = stream->readUnsignedByte();
		}
		else if (opcode == 3)
		{
			def->field3278 = stream->readUnsignedByte();
		}
		else if (opcode == 4)
		{
			def->field3283 = 0;
		}
		else if (opcode == 5)
		{
			def->field3275 = stream->readUnsignedShort();
		}
		else if (opcode == 6)
		{
			stream->readUnsignedByte();
		}
		else if (opcode == 7)
		{
			def->healthBarFrontSpriteId = stream->readBigSmart2();
		}
		else if (opcode == 8)
		{
			def->healthBarBackSpriteId = stream->readBigSmart2();
		}
		else if (opcode == 11)
		{
			def->field3283 = stream->readUnsignedShort();
		}
		else if (opcode == 14)
		{
			def->healthScale = stream->readUnsignedByte();
		}
		else if (opcode == 15)
		{
			def->healthBarPadding = stream->readUnsignedByte();
		}
	}
}
