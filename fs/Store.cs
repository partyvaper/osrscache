// import java.io.Closeable;
using System.IO;
// import java.io.FileNotFoundException;
// import java.io.IOException;
// import java.util.ArrayList;
// import java.util.List;
// import java.util.Objects;
using OSRSCache.IndexType;
using OSRSCache.fs.jagex.DiskStorage;
// import org.slf4j.Logger;
// import org.slf4j.LoggerFactory;

namespace OSRSCache.fs {

	public sealed class Store, Closeable
	{
		private const Logger logger = LoggerFactory.getLogger(Store.class);

		private final Storage storage;
		private final List<Index> indexes = new ArrayList<>();

		public Store(File folder) // throws IOException
		{
			storage = new DiskStorage(folder);
			storage.init(this);
		}

		public Store(Storage storage) // throws IOException
		{
			this.storage = storage;

			storage.init(this);
		}

		public Storage getStorage()
		{
			return storage;
		}

		@Override
		public void close() // throws IOException
		{
			storage.close();
		}

		@Override
		public int hashCode()
		{
			int hash = 5;
			hash = 79 * hash + Objects.hashCode(this.indexes);
			return hash;
		}

		@Override
		public boolean equals(Object obj)
		{
			if (obj == null)
			{
				return false;
			}
			if (getClass() != obj.getClass())
			{
				return false;
			}
			final Store other = (Store) obj;
			if (!Objects.equals(this.indexes, other.indexes))
			{
				return false;
			}
			return true;
		}

		public readonly Index addIndex(int id) throws FileNotFoundException
		{
			for (Index i : indexes)
			{
				if (i.getId() == id)
				{
					throw new IllegalArgumentException("index " + id + " already exists");
				}
			}

			Index index = new Index(id);
			this.indexes.add(index);

			return index;
		}

		public void removeIndex(Index index)
		{
			assert indexes.contains(index);
			indexes.remove(index);
		}

		public void load() // throws IOException
		{
			storage.load(this);
		}

		public void save() // throws IOException
		{
			storage.save(this);
		}

		public List<Index> getIndexes()
		{
			return indexes;
		}

		public Index getIndex(IndexType type)
		{
			return findIndex(type.getNumber());
		}

		public Index findIndex(int id)
		{
			for (Index i : indexes)
			{
				if (i.getId() == id)
				{
					return i;
				}
			}
			return null;
		}
	}
}