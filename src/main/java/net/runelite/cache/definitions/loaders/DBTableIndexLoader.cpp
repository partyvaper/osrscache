#include "DBTableIndexLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using ArrayList = java::util::ArrayList;
	using HashMap = java::util::HashMap;
	using List = java::util::List;
	using Map = java::util::Map;
	using DBTableIndex = net::runelite::cache::definitions::DBTableIndex;
	using InputStream = net::runelite::cache::io::InputStream;
	using BaseVarType = net::runelite::cache::util::BaseVarType;

	std::shared_ptr<DBTableIndex> DBTableIndexLoader::load(int tableId, int columnId, std::vector<signed char> &b)
	{
		std::shared_ptr<DBTableIndex> index = std::make_shared<DBTableIndex>(tableId, columnId);
		std::shared_ptr<InputStream> is = std::make_shared<InputStream>(b);
		decode(index, is);
		return index;
	}

	void DBTableIndexLoader::decode(std::shared_ptr<DBTableIndex> index, std::shared_ptr<InputStream> stream)
	{
		int tupleSize = stream->readVarInt2();
		std::vector<BaseVarType> tupleTypes(tupleSize);
		std::vector<std::unordered_map<std::any, std::vector<int>>> tupleIndexes(tupleSize);

		for (int i = 0; i < tupleSize; i++)
		{
			tupleTypes[i] = BaseVarType::forId(stream->readUnsignedByte());

			int valueCount = stream->readVarInt2();
			std::unordered_map<std::any, std::vector<int>> valueToRows(valueCount);

			while (valueCount-- > 0)
			{
				std::any value = decodeValue(tupleTypes[i], stream);

				int rowCount = stream->readVarInt2();
				std::vector<int> rowIds(rowCount);

				while (rowCount-- > 0)
				{
					rowIds.push_back(stream->readVarInt2());
				}

				valueToRows.emplace(value, rowIds);
			}

			tupleIndexes.push_back(i, valueToRows);
		}

		index->setTupleTypes(tupleTypes);
		index->setTupleIndexes(tupleIndexes);
	}

	std::any DBTableIndexLoader::decodeValue(BaseVarType baseType, std::shared_ptr<InputStream> stream)
	{
		switch (baseType)
		{
			case BaseVarType::INTEGER:
				return stream->readInt();
			case BaseVarType::LONG:
				return stream->readLong();
			case BaseVarType::STRING:
				return stream->readString();
		}
		return std::any();
	}
}
