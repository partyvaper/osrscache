using System;
using System.Collections.Generic;

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
namespace OSRSCache
{
	using ItemDefinition = OSRSCache.definitions.ItemDefinition;
	using ItemExporter = OSRSCache.definitions.exporters.ItemExporter;
	using ItemLoader = OSRSCache.definitions.loaders.ItemLoader;
	using ItemProvider = OSRSCache.definitions.providers.ItemProvider;
	using Archive = OSRSCache.fs.Archive;
	using ArchiveFiles = OSRSCache.fs.ArchiveFiles;
	using FSFile = OSRSCache.fs.FSFile;
	using Index = OSRSCache.fs.Index;
	using Storage = OSRSCache.fs.Storage;
	using Store = OSRSCache.fs.Store;
	// using IDClass = OSRSCache.util.IDClass;

	public class ItemManager : ItemProvider
	{
		private readonly Store store;
		private readonly IDictionary<int, ItemDefinition> items = new Dictionary<int, ItemDefinition>();

		public ItemManager(Store store)
		{
			this.store = store;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void load() throws java.io.IOException
		public virtual void load()
		{
			ItemLoader loader = new ItemLoader();

			Storage storage = store.Storage;
			Index index = store.getIndex(IndexType.CONFIGS);
			Archive archive = index.getArchive(ConfigType.ITEM.Id);

			sbyte[] archiveData = storage.loadArchive(archive);
			ArchiveFiles files = archive.getFiles(archiveData);

			foreach (FSFile f in files.Files)
			{
				ItemDefinition def = loader.load(f.FileId, f.Contents);
				items[f.FileId] = def;
			}
		}

		public virtual ICollection<ItemDefinition> Items
		{
			get
			{
				// return Collections.unmodifiableCollection(items.Values);
				return new List<ItemDefinition>(items.Values);
			}
		}

		public virtual ItemDefinition getItem(int itemId)
		{
			return items[itemId];
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void export(java.io.File out) throws java.io.IOException
		public virtual void export(string @out)
		{
			// @out.mkdirs(); // TODO: ????

			foreach (ItemDefinition def in items.Values)
			{
				ItemExporter exporter = new ItemExporter(def);

				string targ = $"{@out}/{def.id}.json";
				exporter.exportTo(targ);
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void java(java.io.File java) throws java.io.IOException
		public virtual void java(string java)
		{
			Console.WriteLine($"ItemManager.java not implemented! {java}");
			// java.mkdirs();
			// using (IDClass ids = IDClass.create(java, "ItemID"), IDClass nulls = IDClass.create(java, "NullItemID"))
			// {
			// 	foreach (ItemDefinition def in items.Values)
			// 	{
			// 		if (def.name.Equals("NULL", StringComparison.OrdinalIgnoreCase))
			// 		{
			// 			nulls.add(def.name, def.id);
			// 		}
			// 		else
			// 		{
			// 			ids.add(def.name, def.id);
			// 		}
			// 	}
			// }
		}

		public virtual ItemDefinition provide(int itemId)
		{
			return getItem(itemId);
		}
	}

}