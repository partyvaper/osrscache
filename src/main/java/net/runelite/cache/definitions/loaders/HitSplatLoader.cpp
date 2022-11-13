#include "HitSplatLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using HitSplatDefinition = net::runelite::cache::definitions::HitSplatDefinition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::shared_ptr<HitSplatDefinition> HitSplatLoader::load(std::vector<signed char> &data)
	{
		std::shared_ptr<HitSplatDefinition> def = std::make_shared<HitSplatDefinition>();
		std::shared_ptr<InputStream> stream = std::make_shared<InputStream>(data);

		for (; ;)
		{
			int opcode = stream->readUnsignedByte();

			switch (opcode)
			{
				case 0:
					return def;
				case 1:
					def->setFontType(stream->readBigSmart2());
					break;
				case 2:
					def->setTextColor(stream->read24BitInt());
					break;
				case 3:
					def->setLeftSprite(stream->readBigSmart2());
					break;
				case 4:
					def->setLeftSprite2(stream->readBigSmart2());
					break;
				case 5:
					def->setBackgroundSprite(stream->readBigSmart2());
					break;
				case 6:
					def->setRightSpriteId(stream->readBigSmart2());
					break;
				case 7:
					def->setScrollToOffsetX(stream->readShort());
					break;
				case 8:
					def->setStringFormat(stream->readString2());
					break;
				case 9:
					def->setDisplayCycles(stream->readUnsignedShort());
					break;
				case 10:
					def->setScrollToOffsetY(stream->readShort());
					break;
				case 11:
					def->setFadeStartCycle(0);
					break;
				case 12:
					def->setUseDamage(stream->readUnsignedByte());
					break;
				case 13:
					def->setTextOffsetY(stream->readShort());
					break;
				case 14:
					def->setFadeStartCycle(stream->readUnsignedShort());
					break;
				case 17:
				case 18:
				{
					int varbitId = stream->readUnsignedShort();

					if (varbitId == 0xFFFF)
					{
						varbitId = -1;
					}
					def->setVarbitID(varbitId);

					int varp = stream->readUnsignedShort();
					if (varp == 0xFFFF)
					{
						varp = -1;
					}
					def->setVarpID(varp);

					int id = -1;
					if (opcode == 18)
					{
						id = stream->readUnsignedShort();
						if (id == 0xFFFF)
						{
							id = -1;
						}
					}

					int length = stream->readUnsignedByte();
					std::vector<int> multihitsplats(length + 2);

					for (int i = 0; i <= length; i++)
					{
						multihitsplats[i] = stream->readUnsignedShort();
						if (multihitsplats[i] == 0xFFFF)
						{
							multihitsplats[i] = -1;
						}
					}

					multihitsplats[length + 1] = id;

					def->setMultihitsplats(multihitsplats);
					break;
				}
			}
		}
	}
}
