using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace OSRSCache.fs
{
	using IndexType = OSRSCache.IndexType;
	using DiskStorage = OSRSCache.fs.jagex.DiskStorage;


	public sealed class Store : System.IDisposable
	{
		private readonly Storage storage;
		private readonly IList<Index> indexes = new List<Index>();

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public Store(java.io.File folder) throws java.io.IOException
		public Store(string folder)
		{
			storage = new DiskStorage(folder);
			storage.init(this);
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public Store(Storage storage) throws java.io.IOException
		public Store(Storage storage)
		{
			this.storage = storage;

			storage.init(this);
		}

		public Storage Storage
		{
			get
			{
				return storage;
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public void close() throws java.io.IOException
		public void Dispose()
		{
			storage.close();
		}

		public override int GetHashCode()
		{
			int hash = 5;
			hash = 79 * hash + this.indexes.GetHashCode();
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
//ORIGINAL LINE: final Store other = (Store) obj;
			Store other = (Store) obj;
			if (!Object.Equals(this.indexes, other.indexes))
			{
				return false;
			}
			return true;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public final Index addIndex(int id) throws java.io.FileNotFoundException
		public Index addIndex(int id)
		{
			foreach (Index i in indexes)
			{
				if (i.Id == id)
				{
					throw new System.ArgumentException("index " + id + " already exists");
				}
			}

			Index index = new Index(id);
			this.indexes.Add(index);

			return index;
		}

		public void removeIndex(Index index)
		{
			Debug.Assert(indexes.Contains(index));
			indexes.Remove(index);
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void load() throws java.io.IOException
		public void load()
		{
			storage.load(this);
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void save() throws java.io.IOException
		public void save()
		{
			storage.save(this);
		}

		public IList<Index> Indexes
		{
			get
			{
				return indexes;
			}
		}

		public Index getIndex(IndexType type)
		{
			return findIndex(type.Number);
		}

		public Index findIndex(int id)
		{
			foreach (Index i in indexes)
			{
				if (i.Id == id)
				{
					return i;
				}
			}
			return null;
		}
	}

}