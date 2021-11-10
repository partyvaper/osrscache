namespace OSRSCache.fs.jagex
{

	public class IndexEntry
	{
		private readonly IndexFile indexFile;
		private readonly int id, sector, length;

		public IndexEntry(IndexFile indexFile, int id, int sector, int length)
		{
			this.indexFile = indexFile;
			this.id = id;
			this.sector = sector;
			this.length = length;
		}

		public virtual IndexFile IndexFile
		{
			get
			{
				return indexFile;
			}
		}

		public virtual int Id
		{
			get
			{
				return id;
			}
		}

		public virtual int Sector
		{
			get
			{
				return sector;
			}
		}

		public virtual int Length
		{
			get
			{
				return length;
			}
		}

		public override int GetHashCode()
		{
			int hash = 7;
			hash = 19 * hash + Objects.hashCode(this.indexFile);
			hash = 19 * hash + this.id;
			hash = 19 * hash + this.sector;
			hash = 19 * hash + this.length;
			return hash;
		}

		public override bool Equals(object obj)
		{
			if (obj == null)
			{
				return false;
			}
			if (this.GetType() != obj.GetType())
			{
				return false;
			}
//JAVA TO C# CONVERTER WARNING: The original Java variable was marked 'final':
//ORIGINAL LINE: final IndexEntry other = (IndexEntry) obj;
			IndexEntry other = (IndexEntry) obj;
			if (!Objects.equals(this.indexFile, other.indexFile))
			{
				return false;
			}
			if (this.id != other.id)
			{
				return false;
			}
			if (this.sector != other.sector)
			{
				return false;
			}
			if (this.length != other.length)
			{
				return false;
			}
			return true;
		}
	}

}