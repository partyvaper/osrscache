using System;
using CommandLine;

namespace OSRSCache
{
	using Store = OSRSCache.fs.Store;

	public class Cache
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
		
		public static void Main(string[] args)
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
					dumpItems(store, dir);
				}
				else if (o.Npcs)
				{
					string dir = outDir + "/npcs";
					Console.WriteLine("Dumping npcs to " + dir);
					dumpNpcs(store, dir);
				}
				else if (o.Objects)
				{
					string dir = outDir + "/objects";
					Console.WriteLine("Dumping objects to " + dir);
					dumpObjects(store, dir);
				}
				else if (o.Sprites)
				{
					string dir = outDir + "/sprites";
					Console.WriteLine("Dumping sprites to " + dir);
					dumpSprites(store, dir);
				}
				else
				{
					Console.WriteLine("Nothing to do");
				}
				
				Environment.Exit(1);
			});
		}

		private static Store loadStore(string cache)
		{
			Store store = new Store(cache);
			store.load();
			return store;
		}

		private static void dumpItems(Store store, string itemdir)
		{
			ItemManager dumper = new ItemManager(store);
			dumper.load();
			dumper.export(itemdir);
			dumper.java(itemdir);
		}

		private static void dumpNpcs(Store store, string npcdir)
		{
			NpcManager dumper = new NpcManager(store);
			dumper.load();
			dumper.dump(npcdir);
			dumper.java(npcdir);
		}

		private static void dumpObjects(Store store, string objectdir)
		{
			ObjectManager dumper = new ObjectManager(store);
			dumper.load();
			dumper.dump(objectdir);
			dumper.java(objectdir);
		}

		private static void dumpSprites(Store store, string spritedir)
		{
			SpriteManager dumper = new SpriteManager(store);
			dumper.load();
			dumper.export(spritedir);
		}
	}

}