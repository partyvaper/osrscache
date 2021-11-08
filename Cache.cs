using System;
using OSRSCache.fs;
using System.IO;
using CommandLine;

// import java.io.IOException;
// import org.apache.commons.cli.CommandLine;
// import org.apache.commons.cli.CommandLineParser;
// import org.apache.commons.cli.DefaultParser;
// import org.apache.commons.cli.Options;
// import org.apache.commons.cli.ParseException;

namespace OSRSCache {

	public enum IndexType: int
	{
		FRAMES = 0,
		FRAMEMAPS = 1,
		CONFIGS = 2,
		INTERFACES = 3,
		SOUNDEFFECTS = 4,
		MAPS = 5,
		TRACK1 = 6,
		MODELS = 7,
		SPRITES = 8,
		TEXTURES = 9,
		BINARY = 10,
		TRACK2 = 11,
		CLIENTSCRIPT = 12,
		FONTS = 13,
		VORBIS = 14,
		INSTRUMENTS = 15,
		WORLDMAP = 16,
	}

	internal class Cache
	{
		public class Options
		{
			[Option('v', "verbose", Required = false, HelpText = "Set output to verbose messages")]
			public bool Verbose { get; set; }
			[Option('c', "cache", Required = false, HelpText = "Set the cache folder directory")]
			public string Cache { get; set; }
			[Option('i', "items", Required = false, HelpText = "Dump items config to folder")]
			public bool Items { get; set; }
			[Option('n', "npcs", Required = false, HelpText = "Dump npcs config to folder")]
			public bool Npcs { get; set; }
			[Option('o', "objects", Required = false, HelpText = "Dump objects config to folder")]
			public bool Objects { get; set; }
			[Option('s', "sprites", Required = false, HelpText = "Dump sprites images to folder")]
			public bool Sprites { get; set; }
		}
		
		public static void Main(string[] args) // throws IOException
		{
			Parser.Default.ParseArguments<Options>(args).WithParsed<Options>(o => {
				Console.WriteLine($"Verbose set to: {o.Verbose}");

				string cacheDir = o.Cache;
				if (cacheDir == null) {
					cacheDir = "cache";
				}

				string outDir = "dumps";

				// TODO: flatcache
				
				Store store = loadStore(cacheDir);
				
				if (o.Items)
				{
					string dir = outDir + "/items";
					Console.WriteLine("Dumping items to " + dir);
					dumpItems(store, new File(dir));
				}
				else if (o.Npcs)
				{
					string dir = outDir + "/npcs";
					Console.WriteLine("Dumping npcs to " + dir);
					dumpNpcs(store, new File(dir));
				}
				else if (o.Objects)
				{
					string dir = outDir + "/objects";
					Console.WriteLine("Dumping objects to " + dir);
					dumpObjects(store, new File(dir));
				}
				else if (o.Sprites)
				{
					string dir = outDir + "/sprites";
					Console.WriteLine("Dumping sprites to " + dir);
					dumpSprites(store, new File(dir));
				}
				else
				{
					Console.WriteLine("Nothing to do");
				}
				
				System.Environment.Exit(1);
			});
		}

		private static Store loadStore(string cache) // throws IOException
		{
			Store store = new Store(new File(cache));
			store.load();
			return store;
		}

		private static void dumpItems(Store store, File itemdir) // throws IOException
		{
			ItemManager dumper = new ItemManager(store);
			dumper.load();
			dumper.export(itemdir);
			dumper.java(itemdir);
		}

		private static void dumpNpcs(Store store, File npcdir) // throws IOException
		{
			NpcManager dumper = new NpcManager(store);
			dumper.load();
			dumper.dump(npcdir);
			dumper.java(npcdir);
		}

		private static void dumpObjects(Store store, File objectdir) // throws IOException
		{
			ObjectManager dumper = new ObjectManager(store);
			dumper.load();
			dumper.dump(objectdir);
			dumper.java(objectdir);
		}

		private static void dumpSprites(Store store, File spritedir) // throws IOException
		{
			SpriteManager dumper = new SpriteManager(store);
			dumper.load();
			dumper.export(spritedir);
		}
	}
}