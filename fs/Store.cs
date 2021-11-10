using System.Collections.Generic;
using System.Diagnostics;

/*
 * Copyright (c) 2016-2017, Adam <Adam@sigterm.info>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
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
			hash = 79 * hash + Objects.hashCode(this.indexes);
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
			if (!Objects.equals(this.indexes, other.indexes))
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