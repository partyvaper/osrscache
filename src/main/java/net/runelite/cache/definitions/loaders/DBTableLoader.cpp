#include "DBTableLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using Slf4j = lombok::extern_Keyword::slf4j::Slf4j;
	using DBTableDefinition = net::runelite::cache::definitions::DBTableDefinition;
	using InputStream = net::runelite::cache::io::InputStream;
	using ScriptVarType = net::runelite::cache::util::ScriptVarType;

	std::shared_ptr<DBTableDefinition> DBTableLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<DBTableDefinition> def = std::make_shared<DBTableDefinition>(id);
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

	void DBTableLoader::decode(int opcode, std::shared_ptr<DBTableDefinition> def, std::shared_ptr<InputStream> stream)
	{
		if (opcode == 1)
		{
			int numColumns = stream->readUnsignedByte();
			std::vector<std::vector<ScriptVarType>> types(numColumns);
			std::vector<std::vector<std::any>> defaultValues;

			for (int setting = stream->readUnsignedByte(); setting != 255; setting = stream->readUnsignedByte())
			{
				int columnId = setting & 0x7F;
				bool hasDefault = (setting & 0x80) != 0;
				std::vector<ScriptVarType> columnTypes(stream->readUnsignedByte());
				for (int i = 0; i < columnTypes.length; i++)
				{
					columnTypes[i] = ScriptVarType::forId(stream->readUnsignedShortSmart());
				}
				types[columnId] = columnTypes;

				if (hasDefault)
				{
					if (defaultValues.empty())
					{
						defaultValues = std::vector<std::vector<std::any>>(types.length);
					}

					defaultValues[columnId] = decodeColumnFields(stream, columnTypes);
				}
			}

			def->setTypes(types);
			def->setDefaultColumnValues(defaultValues);
		}
		else
		{
			log::warn(L"Unrecognized dbtable opcode {}", opcode);
		}
	}

	std::vector<std::any> DBTableLoader::decodeColumnFields(std::shared_ptr<InputStream> stream, std::vector<ScriptVarType> &types)
	{
		int fieldCount = stream->readUnsignedShortSmart();
		std::vector<std::any> values(fieldCount * types.length);

		for (int fieldIndex = 0; fieldIndex < fieldCount; fieldIndex++)
		{
			for (int typeIndex = 0; typeIndex < types.length; typeIndex++)
			{
				ScriptVarType type = types[typeIndex];
				int valuesIndex = fieldIndex * types.length + typeIndex;

				if (type == ScriptVarType::STRING)
				{
					values[valuesIndex] = stream->readString();
				}
				else
				{
					values[valuesIndex] = stream->readInt();
				}
			}
		}

		return values;
	}
}
