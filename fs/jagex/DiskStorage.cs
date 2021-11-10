using System;
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
namespace OSRSCache.fs.jagex
{
	using Ints = com.google.common.primitives.Ints;
	using Archive = OSRSCache.fs.Archive;
	using Container = OSRSCache.fs.Container;
	using Index = OSRSCache.fs.Index;
	using Storage = OSRSCache.fs.Storage;
	using Store = OSRSCache.fs.Store;
	using ArchiveData = OSRSCache.index.ArchiveData;
	using IndexData = OSRSCache.index.IndexData;
	using Crc32 = OSRSCache.util.Crc32;


	public class DiskStorage : Storage
	{
		private const string MAIN_FILE_CACHE_DAT = "main_file_cache.dat2";
		private const string MAIN_FILE_CACHE_IDX = "main_file_cache.idx";

		private readonly string folder;

		private readonly DataFile data;
		private readonly IndexFile index255;
		private readonly IList<IndexFile> indexFiles = new List<IndexFile>();

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public DiskStorage(java.io.File folder) throws java.io.IOException
		public DiskStorage(string folder)
		{
			this.folder = folder;

			this.data = new DataFile($"{folder}/{MAIN_FILE_CACHE_DAT}");
			this.index255 = new IndexFile(255, $"{folder}/{MAIN_FILE_CACHE_IDX}255");
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public void init(OSRSCache.fs.Store store) throws java.io.IOException
		public virtual void init(Store store)
		{
			for (int i = 0; i < index255.IndexCount; ++i)
			{
				store.addIndex(i);
				getIndex(i);
			}

			Debug.Assert(store.Indexes.Count == indexFiles.Count);
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public void close() throws java.io.IOException
		public virtual void close()
		{
			data.Dispose();
			index255.Dispose();
			foreach (IndexFile indexFile in indexFiles)
			{
				indexFile.Dispose();
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: private IndexFile getIndex(int i) throws java.io.FileNotFoundException
		private IndexFile getIndex(int i)
		{
			foreach (IndexFile indexFile in indexFiles)
			{
				if (indexFile.IndexFileId == i)
				{
					return indexFile;
				}
			}

			IndexFile _indexFile = new IndexFile(i, $"{folder}/{MAIN_FILE_CACHE_IDX}{i}"); 
			indexFiles.Add(_indexFile);
			return _indexFile;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public void load(OSRSCache.fs.Store store) throws java.io.IOException
		public virtual void load(Store store)
		{
			foreach (Index index in store.Indexes)
			{
				loadIndex(index);
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public byte[] readIndex(int indexId) throws java.io.IOException
		public virtual sbyte[] readIndex(int indexId)
		{
			IndexEntry entry = index255.read(indexId);
			if (entry == null)
			{
				return null;
			}

			sbyte[] indexData = data.read(index255.IndexFileId, entry.Id, entry.Sector, entry.Length);
			return indexData;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: private void loadIndex(OSRSCache.fs.Index index) throws java.io.IOException
		private void loadIndex(Index index)
		{
			Console.WriteLine("Loading index {}", index.Id);

			sbyte[] indexData = readIndex(index.Id);
			if (indexData == null)
			{
				return;
			}

			Container res = Container.decompress(indexData, null);
			sbyte[] data = res.data;

			IndexData id = new IndexData();
			id.load(data);

			index.Protocol = id.Protocol;
			index.Revision = id.Revision;
			index.Named = id.Named;

			foreach (ArchiveData ad in id.Archives)
			{
				Archive archive = index.addArchive(ad.Id);
				archive.NameHash = ad.NameHash;
				archive.Crc = ad.Crc;
				archive.Revision = ad.Revision;
				archive.FileData = ad.Files;

				Debug.Assert(ad.Files.Length > 0);
			}

			index.Crc = res.crc;
			index.Compression = res.compression;
			Debug.Assert(res.revision == -1);
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public byte[] loadArchive(OSRSCache.fs.Archive archive) throws java.io.IOException
		public virtual sbyte[] loadArchive(Archive archive)
		{
			Index index = archive.Index;
			IndexFile indexFile = getIndex(index.Id);

			Debug.Assert(indexFile.IndexFileId == index.Id);

			IndexEntry entry = indexFile.read(archive.ArchiveId);
			if (entry == null)
			{
				Console.WriteLine("can't read archive " + archive.ArchiveId + " from index " + index.Id);
				return null;
			}

			Debug.Assert(entry.Id == archive.ArchiveId);

			Console.WriteLine("Loading archive {} for index {} from sector {} length {}", archive.ArchiveId, index.Id, entry.Sector, entry.Length);

			sbyte[] archiveData = data.read(index.Id, entry.Id, entry.Sector, entry.Length);
			return archiveData;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public void save(OSRSCache.fs.Store store) throws java.io.IOException
		public virtual void save(Store store)
		{
			Console.WriteLine("Saving store");

			foreach (Index i in store.Indexes)
			{
				saveIndex(i);
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: private void saveIndex(OSRSCache.fs.Index index) throws java.io.IOException
		private void saveIndex(Index index)
		{
			IndexData indexData = index.toIndexData();
			sbyte[] data = indexData.writeIndexData();

			Container container = new Container(index.Compression, -1); // index data revision is always -1
			container.compress(data, null);
			sbyte[] compressedData = container.data;
			DataFileWriteResult res = this.data.write(index255.IndexFileId, index.Id, compressedData);

			index255.write(new IndexEntry(index255, index.Id, res.sector, res.compressedLength));

			Crc32 crc = new Crc32();
			crc.update(compressedData, 0, compressedData.Length);
			index.Crc = crc.Hash;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public void saveArchive(OSRSCache.fs.Archive a, byte[] archiveData) throws java.io.IOException
		public virtual void saveArchive(Archive a, sbyte[] archiveData)
		{
			Index index = a.Index;
			IndexFile indexFile = getIndex(index.Id);
			Debug.Assert(indexFile.IndexFileId == index.Id);

			DataFileWriteResult res = data.write(index.Id, a.ArchiveId, archiveData);
			indexFile.write(new IndexEntry(indexFile, a.ArchiveId, res.sector, res.compressedLength));

			sbyte compression = archiveData[0];
			int compressedSize = Ints.fromBytes(archiveData[1], archiveData[2], archiveData[3], archiveData[4]);

			// don't crc the appended revision, if it is there
			int length = 1 + 4 + compressedSize + (compression != CompressionType.NONE ? 4 : 0);

			Crc32 crc = new Crc32();
			crc.update(archiveData, 0, length);
			a.Crc = crc.Hash;

			Console.WriteLine("Saved archive {}/{} at sector {}, compressed length {}", index.Id, a.ArchiveId, res.sector, res.compressedLength);
		}
	}

}