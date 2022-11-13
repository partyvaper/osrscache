#include "LocationSaver.h"

namespace net::runelite::cache::definitions::savers
{
	using LinkedListMultimap = com::google::common::collect::LinkedListMultimap;
	using Multimap = com::google::common::collect::Multimap;
	using ArrayList = java::util::ArrayList;
	using Collection = java::util::Collection;
	using List = java::util::List;
	using LocationsDefinition = net::runelite::cache::definitions::LocationsDefinition;
	using OutputStream = net::runelite::cache::io::OutputStream;
	using Location = net::runelite::cache::region::Location;

	std::vector<signed char> LocationSaver::save(std::shared_ptr<LocationsDefinition> locs)
	{
		std::shared_ptr<Multimap<int, std::shared_ptr<Location>>> locById = LinkedListMultimap::create();
		std::vector<std::shared_ptr<Location>> sortedLocs(locs->getLocations());
		sortedLocs.sort([&] (l1, l2)
		{
		Integer::compare(l1::getId(), l2::getId());
		});
		for (auto loc : sortedLocs)
		{
			locById->put(loc->getId(), loc);
		}
		std::shared_ptr<OutputStream> out = std::make_shared<OutputStream>();
		int prevId = -1;
		for (auto id : locById)
		{
			int diffId = id.first - prevId;
			prevId = id.first;

			out->writeShortSmart(diffId);

			std::shared_ptr<Collection<std::shared_ptr<Location>>> locations = locById->get(id.first);
			int position = 0;
			for (auto loc : locations)
			{
				int packedPosition = (loc->getPosition().getZ() << 12) | (loc->getPosition().getX() << 6) | (loc->getPosition().getY());

				int diffPos = packedPosition - position;
				position = packedPosition;

				out->writeShortSmart(diffPos + 1);

				int packedAttributes = (loc->getType() << 2) | loc->getOrientation();
				out->writeByte(packedAttributes);
			}

			out->writeShortSmart(0);
		}
		out->writeShortSmart(0);
		return out->flip();
	}
}
