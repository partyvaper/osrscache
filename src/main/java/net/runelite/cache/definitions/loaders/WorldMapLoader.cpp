#include "WorldMapLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using LinkedList = java::util::LinkedList;
	using WorldMapDefinition = net::runelite::cache::definitions::WorldMapDefinition;
	using WorldMapType0 = net::runelite::cache::definitions::WorldMapType0;
	using WorldMapType1 = net::runelite::cache::definitions::WorldMapType1;
	using WorldMapType2 = net::runelite::cache::definitions::WorldMapType2;
	using WorldMapType3 = net::runelite::cache::definitions::WorldMapType3;
	using WorldMapTypeBase = net::runelite::cache::definitions::WorldMapTypeBase;
	using InputStream = net::runelite::cache::io::InputStream;
	using Position = net::runelite::cache::region::Position;

	std::shared_ptr<WorldMapDefinition> WorldMapLoader::load(std::vector<signed char> &b, int fileId)
	{
		std::shared_ptr<WorldMapDefinition> def = std::make_shared<WorldMapDefinition>();
		std::shared_ptr<InputStream> in = std::make_shared<InputStream>(b);

		def->fileId = fileId;
		def->safeName = in->readString();
		def->name = in->readString();

		int packedPos = in->readInt();
		if (packedPos == -1)
		{
			def->position = std::make_shared<Position>(-1, -1, -1);
		}
		else
		{
			int y = packedPos >> 28 & 3;
			int x = packedPos >> 14 & 16383;
			int z = packedPos & 16383;
			def->position = std::make_shared<Position>(x, y, z);
		}

		def->field450 = in->readInt();
		in->readUnsignedByte();
		def->isSurface = in->readUnsignedByte() == 1;
		def->defaultZoom = in->readUnsignedByte();
		int var3 = in->readUnsignedByte();
		def->regionList = std::list();

		for (int var4 = 0; var4 < var3; ++var4)
		{
			def->regionList.push_back(this->loadType(in));
		}

		return def;
	}

	std::shared_ptr<WorldMapTypeBase> WorldMapLoader::loadType(std::shared_ptr<InputStream> var1)
	{
		int var2 = var1->readUnsignedByte();
		//      field397 = new class27(1, (byte)0);
		//      field390 = new class27(2, (byte)1);
		//      field399 = new class27(3, (byte)2);
		//      field393 = new class27(0, (byte)3);
		std::shared_ptr<WorldMapTypeBase> __super;
		switch (var2)
		{
			case 0:
				// type 1
				__super = load1(var1);
				break;
			case 1:
				// type 2
				__super = load2(var1);
				break;
			case 2:
				// type 3
				__super = load3(var1);
				break;
			case 3:
				// type 0
				__super = load0(var1);
				break;
			default:
				throw IllegalStateException();
		}
		return __super;
	}

	std::shared_ptr<WorldMapTypeBase> WorldMapLoader::load0(std::shared_ptr<InputStream> in)
	{
		std::shared_ptr<WorldMapType0> wm = std::make_shared<WorldMapType0>();

		wm->plane = in->readUnsignedByte();
		wm->numberOfPlanes = in->readUnsignedByte();
		wm->xLow = in->readUnsignedShort();
		wm->chunk_xLow = in->readUnsignedByte();
		wm->yLow = in->readUnsignedShort();
		wm->chunk_yLow = in->readUnsignedByte();
		wm->xHigh = in->readUnsignedShort();
		wm->chunk_xHigh = in->readUnsignedByte();
		wm->yHigh = in->readUnsignedShort();
		wm->chunk_yHigh = in->readUnsignedByte();

		return wm;
	}

	std::shared_ptr<WorldMapTypeBase> WorldMapLoader::load1(std::shared_ptr<InputStream> in)
	{
		std::shared_ptr<WorldMapType1> wm = std::make_shared<WorldMapType1>();

		wm->plane = in->readUnsignedByte();
		wm->numberOfPlanes = in->readUnsignedByte();
		wm->xLowerLeft = in->readUnsignedShort();
		wm->yLowerLeft = in->readUnsignedShort();
		wm->xLowerRight = in->readUnsignedShort();
		wm->yUpperLeft = in->readUnsignedShort();
		wm->xUpperLeft = in->readUnsignedShort();
		wm->yLowerRight = in->readUnsignedShort();
		wm->xUpperRight = in->readUnsignedShort();
		wm->yUpperRight = in->readUnsignedShort();

		return wm;
	}

	std::shared_ptr<WorldMapTypeBase> WorldMapLoader::load2(std::shared_ptr<InputStream> in)
	{
		std::shared_ptr<WorldMapType2> wm = std::make_shared<WorldMapType2>();

		wm->plane = in->readUnsignedByte();
		wm->numberOfPlanes = in->readUnsignedByte();
		wm->xLow = in->readUnsignedShort();
		wm->yLow = in->readUnsignedShort();
		wm->xHigh = in->readUnsignedShort();
		wm->yHigh = in->readUnsignedShort();

		return wm;
	}

	std::shared_ptr<WorldMapTypeBase> WorldMapLoader::load3(std::shared_ptr<InputStream> in)
	{
		std::shared_ptr<WorldMapType3> wm = std::make_shared<WorldMapType3>();

		wm->oldPlane = in->readUnsignedByte();
		wm->numberOfPlanes = in->readUnsignedByte();
		wm->oldX = in->readUnsignedShort();
		wm->chunk_oldXLow = in->readUnsignedByte();
		wm->chunk_oldXHigh = in->readUnsignedByte();
		wm->oldY = in->readUnsignedShort();
		wm->chunk_oldYLow = in->readUnsignedByte();
		wm->chunk_oldYHigh = in->readUnsignedByte();
		wm->newX = in->readUnsignedShort();
		wm->chunk_newXLow = in->readUnsignedByte();
		wm->chunk_newXHigh = in->readUnsignedByte();
		wm->newY = in->readUnsignedShort();
		wm->chunk_newYLow = in->readUnsignedByte();
		wm->chunk_newYHigh = in->readUnsignedByte();

		return wm;
	}
}
