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

using System.Collections.Generic;
using OSRSCache;
using OSRSCache.fs;

namespace OSRSCache;

// import java.io.IOException;
// import java.util.ArrayList;
// import java.util.List;
using OSRSCache.definitions.TextureDefinition;
using OSRSCache.definitions.loaders.TextureLoader;
using OSRSCache.definitions.providers.TextureProvider;
using OSRSCache.fs.Archive;
using OSRSCache.fs.ArchiveFiles;
using OSRSCache.fs.FSFile;
using OSRSCache.fs.Index;
using OSRSCache.fs.Storage;
using OSRSCache.fs.Store;

public class TextureManager // , TextureProvider
{
	private readonly Store store;
	private readonly List<TextureDefinition> textures = new ArrayList<>();

	public TextureManager(Store store)
	{
		this.store = store;
	}

	public void load() // throws IOException
	{
		Storage storage = store.getStorage();
		Index index = store.getIndex(IndexType.TEXTURES);
		Archive archive = index.getArchive(0);

		byte[] archiveData = storage.loadArchive(archive);
		ArchiveFiles files = archive.getFiles(archiveData);

		TextureLoader loader = new TextureLoader();

		for (FSFile file : files.getFiles())
		{
			TextureDefinition texture = loader.load(file.getFileId(), file.getContents());
			textures.add(texture);
		}
	}

	public List<TextureDefinition> getTextures()
	{
		return textures;
	}

	public TextureDefinition findTexture(int id)
	{
		for (TextureDefinition td : textures)
		{
			if (td.getId() == id)
			{
				return td;
			}
		}
		return null;
	}

	// @Override
	public TextureDefinition[] provide()
	{
		return textures.toArray(new TextureDefinition[textures.size()]);
	}
}
