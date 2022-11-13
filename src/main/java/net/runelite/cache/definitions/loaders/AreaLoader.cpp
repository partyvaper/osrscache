#include "AreaLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using AreaDefinition = net::runelite::cache::definitions::AreaDefinition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::shared_ptr<AreaDefinition> AreaLoader::load(std::vector<signed char> &b, int id)
	{
		std::shared_ptr<InputStream> in = std::make_shared<InputStream>(b);
		std::shared_ptr<AreaDefinition> def = std::make_shared<AreaDefinition>();
		def->id = id;

		for (;;)
		{
			int opcode = in->readUnsignedByte();
			if (opcode == 0)
			{
				break;
			}

			processOpcode(def, in, opcode);
		}

		return def;
	}

	void AreaLoader::processOpcode(std::shared_ptr<AreaDefinition> def, std::shared_ptr<InputStream> in, int opcode)
	{
		if (opcode == 1)
		{
			def->spriteId = in->readBigSmart2();
		}
		else if (opcode == 2)
		{
			def->field3294 = in->readBigSmart2();
		}
		else if (opcode == 3)
		{
			def->name = in->readString();
		}
		else if (opcode == 4)
		{
			def->field3296 = in->read24BitInt();
		}
		else if (opcode == 5)
		{
			in->read24BitInt();
		}
		else if (opcode == 6)
		{
			def->field3310 = in->readUnsignedByte();
		}
		else if (opcode == 7)
		{
			int var3 = in->readUnsignedByte();
			if ((var3 & 1) == 0)
			{
				;
			}

			if ((var3 & 2) == 2)
			{
				;
			}
		}
		else if (opcode == 8)
		{
			in->readUnsignedByte();
		}
		else if (opcode >= 10 && opcode <= 14)
		{
			def->field3298[opcode - 10] = in->readString();
		}
		else if (opcode == 15)
		{
			int var3 = in->readUnsignedByte();
			def->field3300 = std::vector<int>(var3 * 2);

			int var4;
			for (var4 = 0; var4 < var3 * 2; ++var4)
			{
				def->field3300[var4] = in->readShort();
			}

			in->readInt();
			var4 = in->readUnsignedByte();
			def->field3292 = std::vector<int>(var4);

			int var5;
			for (var5 = 0; var5 < def->field3292.size(); ++var5)
			{
				def->field3292[var5] = in->readInt();
			}

			def->field3309 = std::vector<signed char>(var3);

			for (var5 = 0; var5 < var3; ++var5)
			{
				def->field3309[var5] = in->readByte();
			}
		}
		else if (opcode == 16)
		{

		}
		else if (opcode == 17)
		{
			def->field3308 = in->readString();
		}
		else if (opcode == 18)
		{
			in->readBigSmart2();
		}
		else if (opcode == 19)
		{
			def->field3297 = in->readUnsignedShort();
		}
		else if (opcode == 21)
		{
			in->readInt();
		}
		else if (opcode == 22)
		{
			in->readInt();
		}
		else if (opcode == 23)
		{
			in->readUnsignedByte();
			in->readUnsignedByte();
			in->readUnsignedByte();
		}
		else if (opcode == 24)
		{
			in->readShort();
			in->readShort();
		}
		else if (opcode == 25)
		{
			in->readBigSmart2();
		}
		else if (opcode == 28)
		{
			in->readUnsignedByte();
		}
		else if (opcode == 29)
		{
			in->skip(1);
		//			class257[] var6 = new class257[]
		//			{
		//				class257.field3538, class257.field3539, class257.field3540
		//			};
		//			this.field3299 = (class257) Item.method1751(var6, var1.readUnsignedByte());
		}
		else if (opcode == 30)
		{
			in->skip(1);
		//			class239[] var7 = new class239[]
		//			{
		//				class239.field3273, class239.field3275, class239.field3271
		//			};
		//			this.field3306 = (class239) Item.method1751(var7, var1.readUnsignedByte());
		}

	}
}