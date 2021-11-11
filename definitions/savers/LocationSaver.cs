using System.Collections.Generic;

namespace OSRSCache.definitions.savers
{
	// using LinkedListMultimap = com.google.common.collect.LinkedListMultimap;
	// using Multimap = com.google.common.collect.Multimap;
	using LocationsDefinition = OSRSCache.definitions.LocationsDefinition;
	using OutputStream = OSRSCache.io.OutputStream;
	using Location = OSRSCache.region.Location;

	public class LocationSaver
	{
		public virtual byte[] save(LocationsDefinition locs)
		{
			Multimap<int, Location> locById = LinkedListMultimap.create();
			IList<Location> sortedLocs = new List<Location>(locs.getLocations());
			sortedLocs.Sort((l1, l2) => Integer.compare(l1.getId(), l2.getId()));
			foreach (Location loc in sortedLocs)
			{
				locById.put(loc.id, loc);
			}
			OutputStream @out = new OutputStream();
			int prevId = -1;
			foreach (int? id in locById.keySet())
			{
				int diffId = id.Value - prevId;
				prevId = id.Value;

				@out.writeShortSmart(diffId);

				ICollection<Location> locations = locById.get(id);
				int position = 0;
				foreach (Location loc in locations)
				{
					int packedPosition = (loc.position.Z << 12) | (loc.position.X << 6) | (loc.position.Y);

					int diffPos = packedPosition - position;
					position = packedPosition;

					@out.writeShortSmart(diffPos + 1);

					int packedAttributes = (loc.type << 2) | loc.orientation;
					@out.writeByte(packedAttributes);
				}

				@out.writeShortSmart(0);
			}
			@out.writeShortSmart(0);
			return @out.flip();
		}
	}

}