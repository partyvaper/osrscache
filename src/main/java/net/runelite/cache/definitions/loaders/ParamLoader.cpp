#include "ParamLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using ParamDefinition = net::runelite::cache::definitions::ParamDefinition;
	using InputStream = net::runelite::cache::io::InputStream;
	using ScriptVarType = net::runelite::cache::util::ScriptVarType;

	std::shared_ptr<ParamDefinition> ParamLoader::load(std::vector<signed char> &data)
	{
		std::shared_ptr<ParamDefinition> def = std::make_shared<ParamDefinition>();
		std::shared_ptr<InputStream> b = std::make_shared<InputStream>(data);

		for (; ;)
		{
			int opcode = b->readUnsignedByte();

			switch (opcode)
			{
				case 0:
					return def;
				case 1:
				{
					int idx = b->readUnsignedByte();
					def->setType(ScriptVarType::forCharKey(static_cast<wchar_t>(idx)));
					break;
				}
				case 2:
					def->setDefaultInt(b->readInt());
					break;
				case 4:
					def->setMembers(false);
					break;
				case 5:
					def->setDefaultString(b->readString());
					break;
			}
		}
	}
}
