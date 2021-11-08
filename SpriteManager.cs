﻿using System.Collections.Generic;

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
namespace net.runelite.cache
{
	using LinkedListMultimap = com.google.common.collect.LinkedListMultimap;
	using Multimap = com.google.common.collect.Multimap;
	using SpriteDefinition = net.runelite.cache.definitions.SpriteDefinition;
	using SpriteExporter = net.runelite.cache.definitions.exporters.SpriteExporter;
	using SpriteLoader = net.runelite.cache.definitions.loaders.SpriteLoader;
	using SpriteProvider = net.runelite.cache.definitions.providers.SpriteProvider;
	using Archive = net.runelite.cache.fs.Archive;
	using Index = net.runelite.cache.fs.Index;
	using Storage = net.runelite.cache.fs.Storage;
	using Store = net.runelite.cache.fs.Store;

	public class SpriteManager : SpriteProvider
	{
		private readonly Store store;
		private readonly Multimap<int, SpriteDefinition> sprites = LinkedListMultimap.create();

		public SpriteManager(Store store)
		{
			this.store = store;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void load() throws java.io.IOException
		public virtual void load()
		{
			Storage storage = store.Storage;
			Index index = store.getIndex(IndexType.SPRITES);

			foreach (Archive a in index.Archives)
			{
				sbyte[] contents = a.decompress(storage.loadArchive(a));

				SpriteLoader loader = new SpriteLoader();
				SpriteDefinition[] defs = loader.load(a.ArchiveId, contents);

				foreach (SpriteDefinition sprite in defs)
				{
					sprites.put(sprite.getId(), sprite);
				}
			}
		}

		public virtual ICollection<SpriteDefinition> Sprites
		{
			get
			{
				return Collections.unmodifiableCollection(sprites.values());
			}
		}

		public virtual SpriteDefinition findSprite(int spriteId, int frameId)
		{
			foreach (SpriteDefinition sprite in sprites.get(spriteId))
			{
				if (sprite.getFrame() == frameId)
				{
					return sprite;
				}
			}
			return null;
		}

		public virtual BufferedImage getSpriteImage(SpriteDefinition sprite)
		{
			BufferedImage image = new BufferedImage(sprite.getWidth(), sprite.getHeight(), BufferedImage.TYPE_INT_ARGB);
			image.setRGB(0, 0, sprite.getWidth(), sprite.getHeight(), sprite.getPixels(), 0, sprite.getWidth());
			return image;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void export(java.io.File outDir) throws java.io.IOException
		public virtual void export(File outDir)
		{
			foreach (SpriteDefinition sprite in sprites.values())
			{
				// I don't know why this happens
				if (sprite.getHeight() <= 0 || sprite.getWidth() <= 0)
				{
					continue;
				}

				SpriteExporter exporter = new SpriteExporter(sprite);
				File png = new File(outDir, sprite.getId() + "-" + sprite.getFrame() + ".png");

				exporter.exportTo(png);
			}
		}

		public virtual SpriteDefinition provide(int spriteId, int frameId)
		{
			return findSprite(spriteId, frameId);
		}
	}

}