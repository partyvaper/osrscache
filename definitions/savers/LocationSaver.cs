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
			IDictionary<int, Location> locById = new Dictionary<int, Location>();
			IList<Location> sortedLocs = new List<Location>(locs.locations);
			// sortedLocs.Sort((l1, l2) => Integer.compare(l1.getId(), l2.getId()));
			foreach (Location loc in sortedLocs)
			{
				locById.Add(loc.id, loc);
			}
			OutputStream @out = new OutputStream();
			int prevId = -1;
			foreach (int id in locById.Keys)
			{
				int diffId = id - prevId;
				prevId = id;

				@out.writeShortSmart(diffId);

				// ICollection<Location> locations = locById[id];
				int position = 0;
				// foreach (Location loc in locations)
				// {
					Location loc = locById[id];
					int packedPosition = (loc.position.Z << 12) | (loc.position.X << 6) | (loc.position.Y);

					int diffPos = packedPosition - position;
					position = packedPosition;

					@out.writeShortSmart(diffPos + 1);

					int packedAttributes = (loc.type << 2) | loc.orientation;
					@out.writeByte(packedAttributes);
				// }

				@out.writeShortSmart(0);
			}
			@out.writeShortSmart(0);
			return @out.flip();
		}
	}

}