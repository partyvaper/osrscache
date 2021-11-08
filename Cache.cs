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

	internal class Cache
	{
		public class Options
		{
			[Option('v', "verbose", Required = false, HelpText = "Set output to verbose messages.")]
			public bool Verbose { get; set; }
		}
		
		public static void Main(string[] args) // throws IOException
		{
			Parser.Default.ParseArguments<Options>(args)
				.WithParsed<Options>(o => {
					if (o.Verbose)
					{
						Console.WriteLine($"Verbose output enabled. Current Arguments: -v {o.Verbose}");
						Console.WriteLine("Quick Start Example! App is in Verbose mode!");
					}
					else
					{
						Console.WriteLine($"Current Arguments: -v {o.Verbose}");
						Console.WriteLine("Quick Start Example!");
					}
				});
			
			// Options options = new Options();
			//
			// options.addOption("c", "cache", true, "cache base");
			//
			// options.addOption(null, "items", true, "directory to dump items to");
			// options.addOption(null, "npcs", true, "directory to dump npcs to");
			// options.addOption(null, "objects", true, "directory to dump objects to");
			// options.addOption(null, "sprites", true, "directory to dump sprites to");
			//
			// CommandLineParser parser = new DefaultParser();
			// CommandLine cmd;
			// try
			// {
			// 	cmd = parser.parse(options, args);
			// }
			// catch (ParseException ex)
			// {
			// 	Console.WriteLine("Error parsing command line options: " + ex.getMessage());
			// 	System.exit(-1);
			// 	return;
			// }
			//
			// string cache = cmd.getOptionValue("cache");
			//
			// Store store = loadStore(cache);
			//
			// if (cmd.hasOption("items"))
			// {
			// 	string itemdir = cmd.getOptionValue("items");
			//
			// 	if (itemdir == null)
			// 	{
			// 		Console.WriteLine("Item directory must be specified");
			// 		return;
			// 	}
			//
			// 	Console.WriteLine("Dumping items to " + itemdir);
			// 	dumpItems(store, new File(itemdir));
			// }
			// else if (cmd.hasOption("npcs"))
			// {
			// 	string npcdir = cmd.getOptionValue("npcs");
			//
			// 	if (npcdir == null)
			// 	{
			// 		Console.WriteLine("NPC directory must be specified");
			// 		return;
			// 	}
			//
			// 	Console.WriteLine("Dumping npcs to " + npcdir);
			// 	dumpNpcs(store, new File(npcdir));
			// }
			// else if (cmd.hasOption("objects"))
			// {
			// 	string objectdir = cmd.getOptionValue("objects");
			//
			// 	if (objectdir == null)
			// 	{
			// 		Console.WriteLine("Object directory must be specified");
			// 		return;
			// 	}
			//
			// 	Console.WriteLine("Dumping objects to " + objectdir);
			// 	dumpObjects(store, new File(objectdir));
			// }
			// else if (cmd.hasOption("sprites"))
			// {
			// 	string spritedir = cmd.getOptionValue("sprites");
			//
			// 	if (spritedir == null)
			// 	{
			// 		Console.WriteLine("Sprite directory must be specified");
			// 		return;
			// 	}
			//
			// 	Console.WriteLine("Dumping sprites to " + spritedir);
			// 	dumpSprites(store, new File(spritedir));
			// }
			// else
			// {
			// 	Console.WriteLine("Nothing to do");
			// }
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