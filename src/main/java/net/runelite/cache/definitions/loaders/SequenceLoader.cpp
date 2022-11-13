#include "SequenceLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using HashMap = java::util::HashMap;
	using SequenceDefinition = net::runelite::cache::definitions::SequenceDefinition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::shared_ptr<SequenceDefinition> SequenceLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<SequenceDefinition> def = std::make_shared<SequenceDefinition>(id);
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

	void SequenceLoader::decodeValues(int opcode, std::shared_ptr<SequenceDefinition> def, std::shared_ptr<InputStream> stream)
	{
		int var3;
		int var4;
		if (opcode == 1)
		{
			var3 = stream->readUnsignedShort();
			def->frameLenghts = std::vector<int>(var3);

			for (var4 = 0; var4 < var3; ++var4)
			{
				def->frameLenghts[var4] = stream->readUnsignedShort();
			}

			def->frameIDs = std::vector<int>(var3);

			for (var4 = 0; var4 < var3; ++var4)
			{
				def->frameIDs[var4] = stream->readUnsignedShort();
			}

			for (var4 = 0; var4 < var3; ++var4)
			{
				def->frameIDs[var4] += stream->readUnsignedShort() << 16;
			}
		}
		else if (opcode == 2)
		{
			def->frameStep = stream->readUnsignedShort();
		}
		else if (opcode == 3)
		{
			var3 = stream->readUnsignedByte();
			def->interleaveLeave = std::vector<int>(1 + var3);

			for (var4 = 0; var4 < var3; ++var4)
			{
				def->interleaveLeave[var4] = stream->readUnsignedByte();
			}

			def->interleaveLeave[var3] = 9999999;
		}
		else if (opcode == 4)
		{
			def->stretches = true;
		}
		else if (opcode == 5)
		{
			def->forcedPriority = stream->readUnsignedByte();
		}
		else if (opcode == 6)
		{
			def->leftHandItem = stream->readUnsignedShort();
		}
		else if (opcode == 7)
		{
			def->rightHandItem = stream->readUnsignedShort();
		}
		else if (opcode == 8)
		{
			def->maxLoops = stream->readUnsignedByte();
		}
		else if (opcode == 9)
		{
			def->precedenceAnimating = stream->readUnsignedByte();
		}
		else if (opcode == 10)
		{
			def->priority = stream->readUnsignedByte();
		}
		else if (opcode == 11)
		{
			def->replyMode = stream->readUnsignedByte();
		}
		else if (opcode == 12)
		{
			var3 = stream->readUnsignedByte();
			def->chatFrameIds = std::vector<int>(var3);

			for (var4 = 0; var4 < var3; ++var4)
			{
				def->chatFrameIds[var4] = stream->readUnsignedShort();
			}

			for (var4 = 0; var4 < var3; ++var4)
			{
				def->chatFrameIds[var4] += stream->readUnsignedShort() << 16;
			}
		}
		else if (opcode == 13)
		{
			var3 = stream->readUnsignedByte();
			def->frameSounds = std::vector<int>(var3);

			for (var4 = 0; var4 < var3; ++var4)
			{
				def->frameSounds[var4] = stream->read24BitInt();
			}
		}
		else if (opcode == 14)
		{
			def->animMayaID = stream->readInt();
		}
		else if (opcode == 15)
		{
			var3 = stream->readUnsignedShort();
			def->animMayaFrameSounds = std::unordered_map<int, int>();

			for (var4 = 0; var4 < var3; ++var4)
			{
				int var5 = stream->readUnsignedShort();
				int var6 = stream->read24BitInt();
				def->animMayaFrameSounds.emplace(var5, var6);
			}
		}
		else if (opcode == 16)
		{
			def->animMayaStart = stream->readUnsignedShort();
			def->animMayaEnd = stream->readUnsignedShort();
		}
		else if (opcode == 17)
		{
			def->animMayaMasks = std::vector<bool>(256);

			var3 = stream->readUnsignedByte();

			for (var4 = 0; var4 < var3; ++var4)
			{
				def->animMayaMasks[stream->readUnsignedByte()] = true;
			}
		}
	}
}
