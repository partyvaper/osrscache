using System;

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
namespace net.runelite.cache
{
	using Store = net.runelite.cache.fs.Store;
	using CommandLine = org.apache.commons.cli.CommandLine;
	using CommandLineParser = org.apache.commons.cli.CommandLineParser;
	using DefaultParser = org.apache.commons.cli.DefaultParser;
	using Options = org.apache.commons.cli.Options;
	using ParseException = org.apache.commons.cli.ParseException;

	public class Cache
	{
//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public static void main(String[] args) throws java.io.IOException
		public static void Main(string[] args)
		{
			Options options = new Options();

			options.addOption("c", "cache", true, "cache base");

			options.addOption(null, "items", true, "directory to dump items to");
			options.addOption(null, "npcs", true, "directory to dump npcs to");
			options.addOption(null, "objects", true, "directory to dump objects to");
			options.addOption(null, "sprites", true, "directory to dump sprites to");

			CommandLineParser parser = new DefaultParser();
			CommandLine cmd;
			try
			{
				cmd = parser.parse(options, args);
			}
			catch (ParseException ex)
			{
				Console.Error.WriteLine("Error parsing command line options: " + ex.Message);
				Environment.Exit(-1);
				return;
			}

			string cache = cmd.getOptionValue("cache");

			Store store = loadStore(cache);

			if (cmd.hasOption("items"))
			{
				string itemdir = cmd.getOptionValue("items");

				if (string.ReferenceEquals(itemdir, null))
				{
					Console.Error.WriteLine("Item directory must be specified");
					return;
				}

				Console.WriteLine("Dumping items to " + itemdir);
				dumpItems(store, new File(itemdir));
			}
			else if (cmd.hasOption("npcs"))
			{
				string npcdir = cmd.getOptionValue("npcs");

				if (string.ReferenceEquals(npcdir, null))
				{
					Console.Error.WriteLine("NPC directory must be specified");
					return;
				}

				Console.WriteLine("Dumping npcs to " + npcdir);
				dumpNpcs(store, new File(npcdir));
			}
			else if (cmd.hasOption("objects"))
			{
				string objectdir = cmd.getOptionValue("objects");

				if (string.ReferenceEquals(objectdir, null))
				{
					Console.Error.WriteLine("Object directory must be specified");
					return;
				}

				Console.WriteLine("Dumping objects to " + objectdir);
				dumpObjects(store, new File(objectdir));
			}
			else if (cmd.hasOption("sprites"))
			{
				string spritedir = cmd.getOptionValue("sprites");

				if (string.ReferenceEquals(spritedir, null))
				{
					Console.Error.WriteLine("Sprite directory must be specified");
					return;
				}

				Console.WriteLine("Dumping sprites to " + spritedir);
				dumpSprites(store, new File(spritedir));
			}
			else
			{
				Console.Error.WriteLine("Nothing to do");
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: private static net.runelite.cache.fs.Store loadStore(String cache) throws java.io.IOException
		private static Store loadStore(string cache)
		{
			Store store = new Store(new File(cache));
			store.load();
			return store;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: private static void dumpItems(net.runelite.cache.fs.Store store, java.io.File itemdir) throws java.io.IOException
		private static void dumpItems(Store store, File itemdir)
		{
			ItemManager dumper = new ItemManager(store);
			dumper.load();
			dumper.export(itemdir);
			dumper.java(itemdir);
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: private static void dumpNpcs(net.runelite.cache.fs.Store store, java.io.File npcdir) throws java.io.IOException
		private static void dumpNpcs(Store store, File npcdir)
		{
			NpcManager dumper = new NpcManager(store);
			dumper.load();
			dumper.dump(npcdir);
			dumper.java(npcdir);
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: private static void dumpObjects(net.runelite.cache.fs.Store store, java.io.File objectdir) throws java.io.IOException
		private static void dumpObjects(Store store, File objectdir)
		{
			ObjectManager dumper = new ObjectManager(store);
			dumper.load();
			dumper.dump(objectdir);
			dumper.java(objectdir);
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: private static void dumpSprites(net.runelite.cache.fs.Store store, java.io.File spritedir) throws java.io.IOException
		private static void dumpSprites(Store store, File spritedir)
		{
			SpriteManager dumper = new SpriteManager(store);
			dumper.load();
			dumper.export(spritedir);
		}
	}

}