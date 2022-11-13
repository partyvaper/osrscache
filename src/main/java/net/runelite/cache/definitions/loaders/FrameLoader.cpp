#include "FrameLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using FrameDefinition = net::runelite::cache::definitions::FrameDefinition;
	using FramemapDefinition = net::runelite::cache::definitions::FramemapDefinition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::shared_ptr<FrameDefinition> FrameLoader::load(std::shared_ptr<FramemapDefinition> framemap, int id, std::vector<signed char> &b)
	{
		std::shared_ptr<FrameDefinition> def = std::make_shared<FrameDefinition>();
		std::shared_ptr<InputStream> in = std::make_shared<InputStream>(b);
		std::shared_ptr<InputStream> data = std::make_shared<InputStream>(b);

		def->id = id;
		def->framemap = framemap;

		int framemapArchiveIndex = in->readUnsignedShort();
		int length = in->readUnsignedByte();

		data->skip(3 + length); // framemapArchiveIndex + length + data

		std::vector<int> indexFrameIds(500);
		std::vector<int> scratchTranslatorX(500);
		std::vector<int> scratchTranslatorY(500);
		std::vector<int> scratchTranslatorZ(500);

		int lastI = -1;
		int index = 0;
		for (int i = 0; i < length; ++i)
		{
			int var9 = in->readUnsignedByte();

			if (var9 <= 0)
			{
				continue;
			}

			if (def->framemap->types[i] != 0)
			{
				for (int var10 = i - 1; var10 > lastI; --var10)
				{
					if (def->framemap->types[var10] == 0)
					{
						indexFrameIds[index] = var10;
						scratchTranslatorX[index] = 0;
						scratchTranslatorY[index] = 0;
						scratchTranslatorZ[index] = 0;
						++index;
						break;
					}
				}
			}

			indexFrameIds[index] = i;
			short var11 = 0;
			if (def->framemap->types[i] == 3)
			{
				var11 = 128;
			}

			if ((var9 & 1) != 0)
			{
				scratchTranslatorX[index] = data->readShortSmart();
			}
			else
			{
				scratchTranslatorX[index] = var11;
			}

			if ((var9 & 2) != 0)
			{
				scratchTranslatorY[index] = data->readShortSmart();
			}
			else
			{
				scratchTranslatorY[index] = var11;
			}

			if ((var9 & 4) != 0)
			{
				scratchTranslatorZ[index] = data->readShortSmart();
			}
			else
			{
				scratchTranslatorZ[index] = var11;
			}

			lastI = i;
			++index;
			if (def->framemap->types[i] == 5)
			{
				def->showing = true;
			}
		}

		if (data->getOffset() != b.size())
		{
//JAVA TO C++ CONVERTER TODO TASK: This exception's constructor requires an argument:
//ORIGINAL LINE: throw new RuntimeException();
			throw std::runtime_error();
		}

		def->translatorCount = index;
		def->indexFrameIds = std::vector<int>(index);
		def->translator_x = std::vector<int>(index);
		def->translator_y = std::vector<int>(index);
		def->translator_z = std::vector<int>(index);

		for (int i = 0; i < index; ++i)
		{
			def->indexFrameIds[i] = indexFrameIds[i];
			def->translator_x[i] = scratchTranslatorX[i];
			def->translator_y[i] = scratchTranslatorY[i];
			def->translator_z[i] = scratchTranslatorZ[i];
		}

		return def;
	}
}
