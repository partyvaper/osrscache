using System;
using System.Collections.Generic;

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
	using ArchiveData = OSRSCache.index.ArchiveData;
	using FileData = OSRSCache.index.FileData;
	using IndexData = OSRSCache.index.IndexData;
	using Djb2 = OSRSCache.util.Djb2;


	public class Index
	{
		private readonly int id;

		private int protocol = 6;
		private bool named = true;
		private int revision;
		private int crc;
		private int compression; // compression method of this index's data in 255

		private readonly IList<Archive> archives = new List<Archive>();

		public Index(int id)
		{
			this.id = id;
		}

		public override int GetHashCode()
		{
			int hash = 3;
			hash = 97 * hash + this.id;
			hash = 97 * hash + this.revision;
			hash = 97 * hash + this.archives.GetHashCode();
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
//ORIGINAL LINE: final Index other = (Index) obj;
			Index other = (Index) obj;
			if (this.id != other.id)
			{
				return false;
			}
			if (this.revision != other.revision)
			{
				return false;
			}
			if (!Object.Equals(this.archives, other.archives))
			{
				return false;
			}
			return true;
		}

		public virtual int Id
		{
			get
			{
				return id;
			}
		}

		public virtual int Protocol
		{
			get
			{
				return protocol;
			}
			set
			{
				this.protocol = value;
			}
		}


		public virtual bool Named
		{
			get
			{
				return named;
			}
			set
			{
				this.named = value;
			}
		}


		public virtual int Revision
		{
			get
			{
				return revision;
			}
			set
			{
				this.revision = value;
			}
		}


		public virtual int Crc
		{
			get
			{
				return crc;
			}
			set
			{
				this.crc = value;
			}
		}


		public virtual int Compression
		{
			get
			{
				return compression;
			}
			set
			{
				this.compression = value;
			}
		}


		public virtual IList<Archive> Archives
		{
			get
			{
				return archives;
			}
		}

		public virtual Archive addArchive(int id)
		{
			Archive archive = new Archive(this, id);
			this.archives.Add(archive);
			return archive;
		}

		public virtual Archive getArchive(int id)
		{
			foreach (Archive a in archives)
			{
				if (a.ArchiveId == id)
				{
					return a;
				}
			}
			return null;
		}

		public virtual Archive findArchiveByName(string name)
		{
			int hash = Djb2.hash(name);
			foreach (Archive a in archives)
			{
				if (a.NameHash == hash)
				{
					return a;
				}
			}
			return null;
		}

		public virtual IndexData toIndexData()
		{
			IndexData data = new IndexData();
			data.Protocol = protocol;
			data.Revision = revision;
			data.Named = named;

			ArchiveData[] archiveDatas = new ArchiveData[archives.Count];
			data.Archives = archiveDatas;

			int idx = 0;
			foreach (Archive archive in archives)
			{
				ArchiveData ad = archiveDatas[idx++] = new ArchiveData();
				ad.Id = archive.ArchiveId;
				ad.NameHash = archive.NameHash;
				ad.Crc = archive.Crc;
				ad.Revision = archive.Revision;

				FileData[] files = archive.FileData;
				ad.Files = files;
			}
			return data;
		}
	}

}