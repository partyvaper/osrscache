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

using System;
using System.IO;

namespace OSRSCache.fs
{
	using FileData = OSRSCache.index.FileData;


	public class Archive
	{
		private readonly Index index; // member of this index

		private readonly int archiveId;
		private int nameHash;
		private int crc;
		private int revision;
		private int compression;
		private FileData[] fileData;
		private byte[] hash; // used by webservice, sha256 hash of content

		public Archive(Index index, int id)
		{
			this.index = index;
			this.archiveId = id;
		}

		public override int GetHashCode()
		{
			int hash = 7;
			hash = 47 * hash + this.archiveId;
			hash = 47 * hash + this.nameHash;
			hash = 47 * hash + this.revision;
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
//ORIGINAL LINE: final Archive other = (Archive) obj;
			Archive other = (Archive) obj;
			if (this.archiveId != other.archiveId)
			{
				return false;
			}
			if (this.nameHash != other.nameHash)
			{
				return false;
			}
			if (this.revision != other.revision)
			{
				return false;
			}
			return true;
		}

		public virtual Index Index
		{
			get
			{
				return index;
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public byte[] decompress(byte[] data) throws java.io.IOException
		public virtual byte[] decompress(byte[] data)
		{
			return decompress(data, null);
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public byte[] decompress(byte[] data, int[] keys) throws java.io.IOException
		public virtual byte[] decompress(byte[] data, int[] keys)
		{
			if (data == null)
			{
				return null;
			}

			byte[] encryptedData = data;

			Container container = Container.decompress(encryptedData, keys);
			if (container == null)
			{
				Console.WriteLine("Unable to decrypt archive {0}", this);
				return null;
			}

			byte[] decompressedData = container.data;

			if (this.crc != container.crc)
			{
				Console.WriteLine("crc mismatch for archive {0}/{1}", index.Id, this.ArchiveId);
				throw new IOException("CRC mismatch for " + index.Id + "/" + this.ArchiveId);
			}

			if (container.revision != -1 && this.Revision != container.revision)
			{
				// compressed data doesn't always include a revision, but check it if it does
				Console.WriteLine("revision mismatch for archive {0}/{1}, expected {2} was {3}", index.Id, this.ArchiveId, this.Revision, container.revision);
				// I've seen this happen with vanilla caches where the
				// revision in the index data differs from the revision
				// stored for the archive data on disk... I assume this
				// is more correct
				this.Revision = container.revision;
			}

			Compression = container.compression;
			return decompressedData;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public ArchiveFiles getFiles(byte[] data) throws java.io.IOException
		public virtual ArchiveFiles getFiles(byte[] data)
		{
			return getFiles(data, null);
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public ArchiveFiles getFiles(byte[] data, int[] keys) throws java.io.IOException
		public virtual ArchiveFiles getFiles(byte[] data, int[] keys)
		{
			byte[] decompressedData = decompress(data, keys);

			ArchiveFiles files = new ArchiveFiles();
			foreach (FileData fileEntry in fileData)
			{
				FSFile file = new FSFile(fileEntry.Id);
				file.NameHash = fileEntry.NameHash;
				files.addFile(file);
			}
			files.loadContents(decompressedData);
			return files;
		}

		public virtual int ArchiveId
		{
			get
			{
				return archiveId;
			}
		}

		public virtual int NameHash
		{
			get
			{
				return nameHash;
			}
			set
			{
				this.nameHash = value;
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


		public virtual FileData[] FileData
		{
			get
			{
				return fileData;
			}
			set
			{
				this.fileData = value;
			}
		}


		public virtual byte[] Hash
		{
			get
			{
				return hash;
			}
			set
			{
				this.hash = value;
			}
		}

	}

}