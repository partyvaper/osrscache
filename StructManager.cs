using System.Collections.Generic;

/*
 * Copyright (c) 2018, Joshua Filby <joshua@filby.me>
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
namespace OSRSCache
{
	using StructDefinition = OSRSCache.definitions.StructDefinition;
	using StructLoader = OSRSCache.definitions.loaders.StructLoader;
	using StructProvider = OSRSCache.definitions.providers.StructProvider;
	using Archive = OSRSCache.fs.Archive;
	using ArchiveFiles = OSRSCache.fs.ArchiveFiles;
	using FSFile = OSRSCache.fs.FSFile;
	using Index = OSRSCache.fs.Index;
	using Storage = OSRSCache.fs.Storage;
	using Store = OSRSCache.fs.Store;

	public class StructManager : StructProvider
	{
		private readonly Store store;
		private readonly IDictionary<int, StructDefinition> structs = new Dictionary<int, StructDefinition>();

		public StructManager(Store store)
		{
			this.store = store;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void load() throws java.io.IOException
		public virtual void load()
		{
			StructLoader loader = new StructLoader();

			Storage storage = store.Storage;
			Index index = store.getIndex(IndexType.CONFIGS);
			Archive archive = index.getArchive(ConfigType.STRUCT.Id);

			byte[] archiveData = storage.loadArchive(archive);
			ArchiveFiles files = archive.getFiles(archiveData);

			foreach (FSFile f in files.Files)
			{
				StructDefinition def = loader.load(f.FileId, f.Contents);
				structs[f.FileId] = def;
			}
		}

		public virtual IDictionary<int, StructDefinition> Structs
		{
			get
			{
				return new Dictionary<int, StructDefinition>(structs);
			}
		}

		public virtual StructDefinition getStruct(int structId)
		{
			return structs[structId];
		}

		public virtual StructDefinition provide(int structId)
		{
			return getStruct(structId);
		}
	}

}