using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using OSRSCache;
using OSRSCache.fs;

namespace OSRSCache;

// import com.google.common.collect.LinkedListMultimap;
// import com.google.common.collect.Multimap;
// import java.awt.image.BufferedImage;
// import java.io.File;
// import java.io.IOException;
// import java.util.Collection;
// import java.util.Collections;
using OSRSCache.definitions.SpriteDefinition;
using OSRSCache.definitions.exporters.SpriteExporter;
using OSRSCache.definitions.loaders.SpriteLoader;
using OSRSCache.definitions.providers.SpriteProvider;
using OSRSCache.fs.Archive;
using OSRSCache.fs.Index;
using OSRSCache.fs.Storage;
using OSRSCache.fs.Store;

public class SpriteManager // , SpriteProvider
{
	private readonly Store store;
	private readonly Multimap<Integer, SpriteDefinition> sprites = LinkedListMultimap.create();

	public SpriteManager(Store store)
	{
		this.store = store;
	}

	public void load() // throws IOException
	{
		Storage storage = store.getStorage();
		Index index = store.getIndex(IndexType.SPRITES);

		for (Archive a : index.getArchives())
		{
			byte[] contents = a.decompress(storage.loadArchive(a));

			SpriteLoader loader = new SpriteLoader();
			SpriteDefinition[] defs = loader.load(a.getArchiveId(), contents);

			for (SpriteDefinition sprite : defs)
			{
				sprites.put(sprite.getId(), sprite);
			}
		}
	}

	public Collection<SpriteDefinition> getSprites()
	{
		return Collections.unmodifiableCollection(sprites.values());
	}

	public SpriteDefinition findSprite(int spriteId, int frameId)
	{
		for (SpriteDefinition sprite : sprites.get(spriteId))
		{
			if (sprite.getFrame() == frameId)
			{
				return sprite;
			}
		}
		return null;
	}

	public BufferedImage getSpriteImage(SpriteDefinition sprite)
	{
		BufferedImage image = new BufferedImage(sprite.getWidth(), sprite.getHeight(), BufferedImage.TYPE_INT_ARGB);
		image.setRGB(0, 0, sprite.getWidth(), sprite.getHeight(), sprite.getPixels(), 0, sprite.getWidth());
		return image;
	}

	public void export(File outDir) // throws IOException
	{
		for (SpriteDefinition sprite : sprites.values())
		{
			// I don't know why this happens
			if (sprite.getHeight() <= 0 || sprite.getWidth() <= 0)
			{
				continue;
			}

			SpriteExporter exporter = new SpriteExporter(sprite);
			string png = $"{outDir}/{sprite.id}-{sprite.frame}.png";
				
			Console.WriteLine("SpriteManager: export not implemented! {00}", png);

			// exporter.exportTo(png);
		}
	}

	// @Override
	public SpriteDefinition provide(int spriteId, int frameId)
	{
		return findSprite(spriteId, frameId);
	}
}
