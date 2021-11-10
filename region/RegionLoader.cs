using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;

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
namespace OSRSCache.region
{
	using IndexType = OSRSCache.IndexType;
	using LocationsDefinition = OSRSCache.definitions.LocationsDefinition;
	using MapDefinition = OSRSCache.definitions.MapDefinition;
	using LocationsLoader = OSRSCache.definitions.loaders.LocationsLoader;
	using MapLoader = OSRSCache.definitions.loaders.MapLoader;
	using Archive = OSRSCache.fs.Archive;
	using Index = OSRSCache.fs.Index;
	using Storage = OSRSCache.fs.Storage;
	using Store = OSRSCache.fs.Store;
	using XteaKeyManager = OSRSCache.util.XteaKeyManager;


	public class RegionLoader
	{
		private const int MAX_REGION = 32768;

		private readonly Store store;
		private readonly Index index;
		private readonly XteaKeyManager keyManager;

		private readonly IDictionary<int, Region> regions = new Dictionary<int, Region>();
		private Region lowestX = null, lowestY = null;
		private Region highestX = null, highestY = null;

		public RegionLoader(Store store)
		{
			this.store = store;
			index = store.getIndex(IndexType.MAPS);
			keyManager = new XteaKeyManager();
			keyManager.loadKeys();
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public void loadRegions() throws java.io.IOException
		public virtual void loadRegions()
		{
			for (int i = 0; i < MAX_REGION; ++i)
			{
				Region region = this.loadRegionFromArchive(i);
				if (region != null)
				{
					regions[i] = region;
				}
			}
		}

//JAVA TO C# CONVERTER WARNING: Method 'throws' clauses are not available in C#:
//ORIGINAL LINE: public Region loadRegionFromArchive(int i) throws java.io.IOException
		public virtual Region loadRegionFromArchive(int i)
		{
			int x = i >> 8;
			int y = i & 0xFF;

			Storage storage = store.Storage;
			Archive map = index.findArchiveByName("m" + x + "_" + y);
			Archive land = index.findArchiveByName("l" + x + "_" + y);

			Debug.Assert((map == null) == (land == null));

			if (map == null || land == null)
			{
				return null;
			}

			sbyte[] data = map.decompress(storage.loadArchive(map));

			MapDefinition mapDef = (new MapLoader()).load(x, y, data);

			Region region = new Region(i);
			region.loadTerrain(mapDef);

			int[] keys = keyManager.getKeys(i);
			if (keys != null)
			{
				try
				{
					data = land.decompress(storage.loadArchive(land), keys);
					LocationsDefinition locDef = (new LocationsLoader()).load(x, y, data);
					region.loadLocations(locDef);
				}
				catch (IOException ex)
				{
					Console.WriteLine("Can't decrypt region " + i, ex);
				}
			}

			return region;
		}

		public virtual void calculateBounds()
		{
			foreach (Region region in regions.Values)
			{
				if (lowestX == null || region.BaseX < lowestX.BaseX)
				{
					lowestX = region;
				}

				if (highestX == null || region.BaseX > highestX.BaseX)
				{
					highestX = region;
				}

				if (lowestY == null || region.BaseY < lowestY.BaseY)
				{
					lowestY = region;
				}

				if (highestY == null || region.BaseY > highestY.BaseY)
				{
					highestY = region;
				}
			}
		}

		public virtual ICollection<Region> Regions
		{
			get
			{
				return regions.Values;
			}
		}

		public virtual Region findRegionForWorldCoordinates(int x, int y)
		{
			x = (int)((uint)x >> 6);
			y = (int)((uint)y >> 6);
			return regions[(x << 8) | y];
		}

		public virtual Region LowestX
		{
			get
			{
				return lowestX;
			}
		}

		public virtual Region LowestY
		{
			get
			{
				return lowestY;
			}
		}

		public virtual Region HighestX
		{
			get
			{
				return highestX;
			}
		}

		public virtual Region HighestY
		{
			get
			{
				return highestY;
			}
		}
	}

}