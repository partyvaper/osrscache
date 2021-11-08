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
namespace net.runelite.cache
{
	using NpcDefinition = net.runelite.cache.definitions.NpcDefinition;
	using NpcExporter = net.runelite.cache.definitions.exporters.NpcExporter;
	using NpcLoader = net.runelite.cache.definitions.loaders.NpcLoader;
	using Archive = net.runelite.cache.fs.Archive;
	using ArchiveFiles = net.runelite.cache.fs.ArchiveFiles;
	using FSFile = net.runelite.cache.fs.FSFile;
	using Index = net.runelite.cache.fs.Index;
	using Storage = net.runelite.cache.fs.Storage;
	using Store = net.runelite.cache.fs.Store;
	using IDClass = net.runelite.cache.util.IDClass;

	public class NpcManager
	{
		private readonly Store store;
		private readonly IDictionary<int, NpcDefinition> npcs = new Dictionary<int, NpcDefinition>();

		public NpcManager(Store store)
		{
			this.store = store;
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void load() throws java.io.IOException
		public virtual void load()
		{
			NpcLoader loader = new NpcLoader();

			Storage storage = store.Storage;
			Index index = store.getIndex(IndexType.CONFIGS);
			Archive archive = index.getArchive(ConfigType.NPC.getId());

			sbyte[] archiveData = storage.loadArchive(archive);
			ArchiveFiles files = archive.getFiles(archiveData);

			foreach (FSFile f in files.Files)
			{
				NpcDefinition npc = loader.load(f.FileId, f.Contents);
				npcs[f.FileId] = npc;
			}
		}

		public virtual ICollection<NpcDefinition> Npcs
		{
			get
			{
				return Collections.unmodifiableCollection(npcs.Values);
			}
		}

		public virtual NpcDefinition get(int npcId)
		{
			return npcs[npcId];
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void dump(java.io.File out) throws java.io.IOException
		public virtual void dump(File @out)
		{
			@out.mkdirs();

			foreach (NpcDefinition def in npcs.Values)
			{
				NpcExporter exporter = new NpcExporter(def);

				File targ = new File(@out, def.id + ".json");
				exporter.exportTo(targ);
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void java(java.io.File java) throws java.io.IOException
		public virtual void java(File java)
		{
			java.mkdirs();
			using (IDClass ids = IDClass.create(java, "NpcID"), IDClass nulls = IDClass.create(java, "NullNpcID"))
			{
				foreach (NpcDefinition def in npcs.Values)
				{
					if (def.name.Equals("NULL", StringComparison.OrdinalIgnoreCase))
					{
						nulls.add(def.name, def.id);
					}
					else
					{
						ids.add(def.name, def.id);
					}
				}
			}
		}
	}

}