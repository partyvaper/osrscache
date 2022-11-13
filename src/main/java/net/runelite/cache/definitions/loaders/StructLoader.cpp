#include "StructLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using HashMap = java::util::HashMap;
	using StructDefinition = net::runelite::cache::definitions::StructDefinition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::shared_ptr<StructDefinition> StructLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<StructDefinition> def = std::make_shared<StructDefinition>(id);
		std::shared_ptr<InputStream> is = std::make_shared<InputStream>(b);

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

	void StructLoader::decodeValues(int opcode, std::shared_ptr<StructDefinition> def, std::shared_ptr<InputStream> stream)
	{
		if (opcode == 249)
		{
			int length = stream->readUnsignedByte();

			def->params = std::unordered_map<int, std::any>(length);

			for (int i = 0; i < length; i++)
			{
				bool isString = stream->readUnsignedByte() == 1;
				int key = stream->read24BitInt();
				std::any value;

				if (isString)
				{
					value = stream->readString();
				}
				else
				{
					value = stream->readInt();
				}

				def->params.emplace(key, value);
			}
		}
	}
}
