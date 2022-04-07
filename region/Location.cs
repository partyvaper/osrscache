namespace OSRSCache.region
{
	public class Location
	{
		public readonly int id;
		public readonly int type;
		public readonly int orientation;
		public readonly Position position;

		public Location(int id, int type, int orientation, Position position)
		{
			this.id = id;
			this.type = type;
			this.orientation = orientation;
			this.position = position;
		}
	}

}