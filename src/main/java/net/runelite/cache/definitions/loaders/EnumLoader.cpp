#include "EnumLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using EnumDefinition = net::runelite::cache::definitions::EnumDefinition;
	using InputStream = net::runelite::cache::io::InputStream;
	using ScriptVarType = net::runelite::cache::util::ScriptVarType;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> EnumLoader::logger = org::slf4j::LoggerFactory::getLogger(EnumLoader::class);

	std::shared_ptr<EnumDefinition> EnumLoader::load(int id, std::vector<signed char> &b)
	{
		if (b.size() == 1 && b[0] == 0)
		{
			return nullptr;
		}

		std::shared_ptr<EnumDefinition> def = std::make_shared<EnumDefinition>();
		std::shared_ptr<InputStream> is = std::make_shared<InputStream>(b);

		def->setId(id);

		for (;;)
		{
			int opcode = is->readUnsignedByte();
			if (opcode == 0)
			{
				break;
			}

			processOp(opcode, def, is);
		}

		return def;
	}

	void EnumLoader::processOp(int opcode, std::shared_ptr<EnumDefinition> def, std::shared_ptr<InputStream> is)
	{
		switch (opcode)
		{
			case 1:
				def->setKeyType(ScriptVarType::forCharKey(static_cast<wchar_t>(is->readUnsignedByte())));
				break;
			case 2:
				def->setValType(ScriptVarType::forCharKey(static_cast<wchar_t>(is->readUnsignedByte())));
				break;
			case 3:
				def->setDefaultString(is->readString());
				break;
			case 4:
				def->setDefaultInt(is->readInt());
				break;
			case 5:
			{
				int size = is->readUnsignedShort();
				std::vector<int> keys(size);
				std::vector<std::wstring> stringVals(size);
				for (int index = 0; index < size; ++index)
				{
					keys[index] = is->readInt();
					stringVals[index] = is->readString();
				}
				def->setSize(size);
				def->setKeys(keys);
				def->setStringVals(stringVals);
				break;
			}
			case 6:
			{
				int size = is->readUnsignedShort();
				std::vector<int> keys(size);
				std::vector<int> intVals(size);
				for (int index = 0; index < size; ++index)
				{
					keys[index] = is->readInt();
					intVals[index] = is->readInt();
				}
				def->setSize(size);
				def->setKeys(keys);
				def->setIntVals(intVals);
				break;
			}
			default:
				logger->warn(L"Unrecognized opcode {}", opcode);
				break;
		}
	}
}
