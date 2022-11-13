#include "LocationsLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using LocationsDefinition = net::runelite::cache::definitions::LocationsDefinition;
	using InputStream = net::runelite::cache::io::InputStream;
	using Location = net::runelite::cache::region::Location;
	using Position = net::runelite::cache::region::Position;

	std::shared_ptr<LocationsDefinition> LocationsLoader::load(int regionX, int regionY, std::vector<signed char> &b)
	{
		std::shared_ptr<LocationsDefinition> loc = std::make_shared<LocationsDefinition>();
		loc->setRegionX(regionX);
		loc->setRegionY(regionY);
		loadLocations(loc, b);
		return loc;
	}

	void LocationsLoader::loadLocations(std::shared_ptr<LocationsDefinition> loc, std::vector<signed char> &b)
	{
		std::shared_ptr<InputStream> buf = std::make_shared<InputStream>(b);

		int id = -1;
		int idOffset;

		while ((idOffset = buf->readUnsignedIntSmartShortCompat()) != 0)
		{
			id += idOffset;

			int position = 0;
			int positionOffset;

			while ((positionOffset = buf->readUnsignedShortSmart()) != 0)
			{
				position += positionOffset - 1;

				int localY = position & 0x3F;
				int localX = position >> 6 & 0x3F;
				int height = position >> 12 & 0x3;

				int attributes = buf->readUnsignedByte();
				int type = attributes >> 2;
				int orientation = attributes & 0x3;

				loc->getLocations()->add(std::make_shared<Location>(id, type, orientation, std::make_shared<Position>(localX, localY, height)));
			}
		}
	}
}
