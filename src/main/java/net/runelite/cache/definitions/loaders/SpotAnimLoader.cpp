#include "SpotAnimLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using SpotAnimDefinition = net::runelite::cache::definitions::SpotAnimDefinition;
	using InputStream = net::runelite::cache::io::InputStream;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> SpotAnimLoader::logger = org::slf4j::LoggerFactory::getLogger(SpotAnimLoader::class);

	std::shared_ptr<SpotAnimDefinition> SpotAnimLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<SpotAnimDefinition> def = std::make_shared<SpotAnimDefinition>();
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

	void SpotAnimLoader::decodeValues(int opcode, std::shared_ptr<SpotAnimDefinition> def, std::shared_ptr<InputStream> stream)
	{
		if (opcode == 1)
		{
			def->modelId = stream->readUnsignedShort();
		}
		else if (opcode == 2)
		{
			def->animationId = stream->readUnsignedShort();
		}
		else if (opcode == 4)
		{
			def->resizeX = stream->readUnsignedShort();
		}
		else if (opcode == 5)
		{
			def->resizeY = stream->readUnsignedShort();
		}
		else if (opcode == 6)
		{
			def->rotaton = stream->readUnsignedShort();
		}
		else if (opcode == 7)
		{
			def->ambient = stream->readUnsignedByte();
		}
		else if (opcode == 8)
		{
			def->contrast = stream->readUnsignedByte();
		}
		else if (opcode == 40)
		{
			int var3 = stream->readUnsignedByte();
			def->recolorToFind = std::vector<short>(var3);
			def->recolorToReplace = std::vector<short>(var3);

			for (int var4 = 0; var4 < var3; ++var4)
			{
				def->recolorToFind[var4] = static_cast<short>(stream->readUnsignedShort());
				def->recolorToReplace[var4] = static_cast<short>(stream->readUnsignedShort());
			}
		}
		else if (opcode == 41)
		{
			int var3 = stream->readUnsignedByte();
			def->textureToFind = std::vector<short>(var3);
			def->textureToReplace = std::vector<short>(var3);

			for (int var4 = 0; var4 < var3; ++var4)
			{
				def->textureToFind[var4] = static_cast<short>(stream->readUnsignedShort());
				def->textureToReplace[var4] = static_cast<short>(stream->readUnsignedShort());
			}
		}
	}
}
