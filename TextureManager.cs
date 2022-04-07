using System.Collections.Generic;

/*
 * Copyright (c) 2017, Adam <Adam@sigterm.info>
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
	using TextureDefinition = OSRSCache.definitions.TextureDefinition;
	using TextureLoader = OSRSCache.definitions.loaders.TextureLoader;
	using TextureProvider = OSRSCache.definitions.providers.TextureProvider;
	using Archive = OSRSCache.fs.Archive;
	using ArchiveFiles = OSRSCache.fs.ArchiveFiles;
	using FSFile = OSRSCache.fs.FSFile;
	using Index = OSRSCache.fs.Index;
	using Storage = OSRSCache.fs.Storage;
	using Store = OSRSCache.fs.Store;

	public class TextureManager : TextureProvider
	{
		private readonly Store store;
		private readonly IList<TextureDefinition> textures = new List<TextureDefinition>();

		public TextureManager(Store store)
		{
			this.store = store;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void load() throws java.io.IOException
		public virtual void load()
		{
			Storage storage = store.Storage;
			Index index = store.getIndex(IndexType.TEXTURES);
			Archive archive = index.getArchive(0);

			byte[] archiveData = storage.loadArchive(archive);
			ArchiveFiles files = archive.getFiles(archiveData);

			TextureLoader loader = new TextureLoader();

			foreach (FSFile file in files.Files)
			{
				TextureDefinition texture = loader.load(file.FileId, file.Contents);
				textures.Add(texture);
			}
		}

		public virtual IList<TextureDefinition> Textures
		{
			get
			{
				return textures;
			}
		}

		public virtual TextureDefinition findTexture(int id)
		{
			foreach (TextureDefinition td in textures)
			{
				if (td.id == id)
				{
					return td;
				}
			}
			return null;
		}

		public virtual TextureDefinition[] provide()
		{
			return ((List<TextureDefinition>)textures).ToArray();
		}
	}

}