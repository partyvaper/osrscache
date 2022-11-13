#include "DBRowLoader.h"
#include "DBTableLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using Slf4j = lombok::extern_Keyword::slf4j::Slf4j;
	using DBRowDefinition = net::runelite::cache::definitions::DBRowDefinition;
	using InputStream = net::runelite::cache::io::InputStream;
	using ScriptVarType = net::runelite::cache::util::ScriptVarType;

	std::shared_ptr<DBRowDefinition> DBRowLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<DBRowDefinition> def = std::make_shared<DBRowDefinition>(id);
		std::shared_ptr<InputStream> is = std::make_shared<InputStream>(b);

		while (true)
		{
			int opcode = is->readUnsignedByte();
			if (opcode == 0)
			{
				break;
			}

			this->decode(opcode, def, is);
		}

		return def;
	}

	void DBRowLoader::decode(int opcode, std::shared_ptr<DBRowDefinition> def, std::shared_ptr<InputStream> stream)
	{
		switch (opcode)
		{
			case 3:
			{
				int numColumns = stream->readUnsignedByte();
				std::vector<std::vector<ScriptVarType>> types(numColumns);
				std::vector<std::vector<std::any>> columnValues(numColumns);

				for (int columnId = stream->readUnsignedByte(); columnId != 255; columnId = stream->readUnsignedByte())
				{
					std::vector<ScriptVarType> columnTypes(stream->readUnsignedByte());
					for (int i = 0; i < columnTypes.length; i++)
					{
						columnTypes[i] = ScriptVarType::forId(stream->readUnsignedShortSmart());
					}
					types[columnId] = columnTypes;
					columnValues[columnId] = DBTableLoader::decodeColumnFields(stream, columnTypes);
				}

				def->setColumnTypes(types);
				def->setColumnValues(columnValues);
				break;
			}
			case 4:
				def->setTableId(stream->readVarInt2());
				break;
			default:
				log::warn(L"Unrecognized dbrow opcode {}", opcode);
				break;
		}
	}
}
