using System.Collections.Generic;

namespace OSRSCache.definitions
{
	using Location = OSRSCache.region.Location;

	public class LocationsDefinition
	{
		public int regionX; // was private, is now public
		public int regionY; // was private, is now public
		public IList<Location> locations = new List<Location>(); // was private, is now public
	}

}