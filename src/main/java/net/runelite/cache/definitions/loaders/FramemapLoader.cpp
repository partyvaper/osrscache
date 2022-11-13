#include "FramemapLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using FramemapDefinition = net::runelite::cache::definitions::FramemapDefinition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::shared_ptr<FramemapDefinition> FramemapLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<FramemapDefinition> def = std::make_shared<FramemapDefinition>();
		std::shared_ptr<InputStream> in = std::make_shared<InputStream>(b);

		def->id = id;

		def->length = in->readUnsignedByte();
		def->types = std::vector<int>(def->length);
		def->frameMaps = std::vector<std::vector<int>>(def->length);

		for (int i = 0; i < def->length; ++i)
		{
			def->types[i] = in->readUnsignedByte();
		}

		for (int i = 0; i < def->length; ++i)
		{
			def->frameMaps[i] = std::vector<int>(in->readUnsignedByte());
		}

		for (int i = 0; i < def->length; ++i)
		{
			for (int j = 0; j < def->frameMaps[i].length; ++j)
			{
				def->frameMaps[i][j] = in->readUnsignedByte();
			}
		}

		return def;
	}
}
