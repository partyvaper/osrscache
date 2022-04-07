using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

/*
 * Copyright (c) 2018 Abex
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
namespace OSRSCache.fs.flat
{
	using Archive = OSRSCache.fs.Archive;
	using Index = OSRSCache.fs.Index;
	using Storage = OSRSCache.fs.Storage;
	using Store = OSRSCache.fs.Store;
	using FileData = OSRSCache.index.FileData;

	/// <summary>
	/// A Storage that stores the cache as a series of flat files, designed
	/// to be git revisioned.
	/// </summary>
	public class FlatStorage : Storage
	{
		protected internal const string EXTENSION = ".flatcache";

		private readonly string directory;
		private readonly IDictionary<long, byte[]> data = new Dictionary<long, byte[]>();

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public FlatStorage(java.io.File directory) throws java.io.IOException
		public FlatStorage(string directory)
		{
			this.directory = directory;
		}

		protected internal FlatStorage()
		{
			this.directory = null;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: protected java.io.InputStream openReader(String filename) throws java.io.IOException
		protected internal virtual Stream openReader(string filename)
		{
			return new FileStream(directory, filename, FileMode.Open, FileAccess.Read);
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: protected java.io.OutputStream openWriter(String filename) throws java.io.IOException
		protected internal virtual Stream openWriter(string filename)
		{
			return new FileStream(directory, filename, FileMode.Create, FileAccess.Write);
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: protected String[] listFlatcacheFiles() throws java.io.IOException
		protected internal virtual string[] listFlatcacheFiles()
		{
			return directory.list((dir, name) => name.EndsWith(EXTENSION));
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public void init(OSRSCache.fs.Store store) throws java.io.IOException
		public virtual void init(Store store)
		{
			string[] idxs = listFlatcacheFiles();
			foreach (string idx in idxs)
			{
				int id = int.Parse(idx.Substring(0, idx.Length - EXTENSION.Length));
				store.addIndex(id);
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public void close() throws java.io.IOException
		public virtual void close()
		{
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public void load(OSRSCache.fs.Store store) throws java.io.IOException
		public virtual void load(Store store)
		{
			foreach (Index idx in store.Indexes)
			{
				string file = idx.Id + EXTENSION;
				using (StreamReader br = new StreamReader(openReader(file), Encoding.UTF8))
				{
					int lineNo = 0;
					Archive archive = null;
					IList<FileData> fileData = null;
					for (string line = br.ReadLine(); !string.ReferenceEquals(line, null); line = br.ReadLine())
					{
						lineNo++;

						try
						{
							int lidx = line.IndexOf('=');
							string key = line.Substring(0, lidx);
							string value = line.Substring(lidx + 1);

							if ("file".Equals(key))
							{
								if (fileData == null)
								{
									fileData = new List<FileData>();
								}

								int vidx = value.IndexOf('=');
								FileData fd = new FileData();
								fd.Id = int.Parse(value.Substring(0, vidx));
								fd.NameHash = int.Parse(value.Substring(vidx + 1));
								fileData.Add(fd);
								continue;
							}
							else if (fileData != null)
							{
								archive.FileData = ((List<FileData>)fileData).ToArray();
								fileData = null;
							}

							if ("id".Equals(key))
							{
								archive = idx.addArchive(int.Parse(value));
								continue;
							}

							if (archive == null)
							{
								switch (key)
								{
									case "protocol":
										idx.Protocol = int.Parse(value);
										continue;
									case "revision":
										idx.Revision = int.Parse(value);
										continue;
									case "compression":
										idx.Compression = int.Parse(value);
										continue;
									case "crc":
										idx.Crc = int.Parse(value);
										continue;
									case "named":
										idx.Named = bool.Parse(value);
										continue;
								}
							}
							else
							{
								switch (key)
								{
									case "namehash":
										archive.NameHash = int.Parse(value);
										continue;
									case "revision":
										archive.Revision = int.Parse(value);
										continue;
									case "crc":
										archive.Crc = int.Parse(value);
										continue;
									case "hash":
										archive.Hash = Base64.getDecoder().decode(value);
										continue;
									case "compression":
										archive.Compression = int.Parse(value);
										continue;
									case "contents":
										data[(long) idx.Id << 32 | archive.ArchiveId] = Base64.getDecoder().decode(value);
										continue;
								}
							}
							throw new IOException("unknown key: \"" + key + "\"");
						}
						catch (Exception e)
						{
							throw new IOException("error reading flatcache at " + file + ":" + lineNo, e);
						}
					}

					if (fileData != null)
					{
						archive.FileData = ((List<FileData>)fileData).ToArray();
						fileData = null;
					}
				}
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public void save(OSRSCache.fs.Store store) throws java.io.IOException
		public virtual void save(Store store)
		{
//JAVA TO C# CONVERTER TODO TASK: Method reference arbitrary object instance method syntax is not converted by Java to C# Converter:
			store.Indexes.Sort(Comparator.comparing(Index::getId));
			foreach (Index idx in store.Indexes)
			{
				string file = idx.Id + EXTENSION;
				using (PrintStream br = new PrintStream(openWriter(file), false, StandardCharsets.UTF_8.name()))
				{
					br.printf("protocol=%d\n", idx.Protocol);
					br.printf("revision=%d\n", idx.Revision);
					br.printf("compression=%d\n", idx.Compression);
					br.printf("crc=%d\n", idx.Crc);
					br.printf("named=%b\n", idx.Named);

//JAVA TO C# CONVERTER TODO TASK: Method reference arbitrary object instance method syntax is not converted by Java to C# Converter:
					idx.Archives.Sort(Comparator.comparing(Archive::getArchiveId));
					foreach (Archive archive in idx.Archives)
					{
						br.printf("id=%d\n", archive.ArchiveId);
						br.printf("namehash=%d\n", archive.NameHash);
						br.printf("revision=%d\n", archive.Revision);
						br.printf("crc=%d\n", archive.Crc);

						if (archive.Hash != null)
						{
							br.append("hash=");
							br.write(Base64.getEncoder().encode(archive.Hash));
							br.append("\n");
						}

						byte[] contents = store.Storage.loadArchive(archive);
						if (contents != null)
						{
							br.append("contents=");
							br.write(Base64.getEncoder().encode(contents));
							br.append("\n");
						}

						br.printf("compression=%d\n", archive.Compression);
						foreach (FileData fd in archive.FileData)
						{
							br.printf("file=%d=%d\n", fd.Id, fd.NameHash);
						}
					}
				}
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public byte[] loadArchive(OSRSCache.fs.Archive archive) throws java.io.IOException
		public virtual byte[] loadArchive(Archive archive)
		{
			return data[(long) archive.Index.Id << 32 | archive.ArchiveId];
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: @Override public void saveArchive(OSRSCache.fs.Archive archive, byte[] bytes) throws java.io.IOException
		public virtual void saveArchive(Archive archive, byte[] bytes)
		{
			data[(long) archive.Index.Id << 32 | archive.ArchiveId] = bytes;
		}
	}

}