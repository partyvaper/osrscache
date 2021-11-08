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
namespace net.runelite.cache.region
{
	using LocationsDefinition = net.runelite.cache.definitions.LocationsDefinition;
	using MapDefinition = net.runelite.cache.definitions.MapDefinition;
	using Tile = net.runelite.cache.definitions.MapDefinition.Tile;

	public class Region
	{

		public const int X = 64;
		public const int Y = 64;
		public const int Z = 4;

		private readonly int regionID;
		private readonly int baseX;
		private readonly int baseY;

//JAVA TO C# CONVERTER NOTE: The following call to the 'RectangularArrays' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: private readonly int[][][] tileHeights = new int[Z][X][Y];
		private readonly int[][][] tileHeights = RectangularArrays.RectangularIntArray(Z, X, Y);
//JAVA TO C# CONVERTER NOTE: The following call to the 'RectangularArrays' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: private readonly sbyte[][][] tileSettings = new sbyte[Z][X][Y];
		private readonly sbyte[][][] tileSettings = RectangularArrays.RectangularSbyteArray(Z, X, Y);
//JAVA TO C# CONVERTER NOTE: The following call to the 'RectangularArrays' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: private readonly sbyte[][][] overlayIds = new sbyte[Z][X][Y];
		private readonly sbyte[][][] overlayIds = RectangularArrays.RectangularSbyteArray(Z, X, Y);
//JAVA TO C# CONVERTER NOTE: The following call to the 'RectangularArrays' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: private readonly sbyte[][][] overlayPaths = new sbyte[Z][X][Y];
		private readonly sbyte[][][] overlayPaths = RectangularArrays.RectangularSbyteArray(Z, X, Y);
//JAVA TO C# CONVERTER NOTE: The following call to the 'RectangularArrays' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: private readonly sbyte[][][] overlayRotations = new sbyte[Z][X][Y];
		private readonly sbyte[][][] overlayRotations = RectangularArrays.RectangularSbyteArray(Z, X, Y);
//JAVA TO C# CONVERTER NOTE: The following call to the 'RectangularArrays' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: private readonly sbyte[][][] underlayIds = new sbyte[Z][X][Y];
		private readonly sbyte[][][] underlayIds = RectangularArrays.RectangularSbyteArray(Z, X, Y);

		private readonly IList<Location> locations = new List<Location>();

		public Region(int id)
		{
			this.regionID = id;
			this.baseX = ((id >> 8) & 0xFF) << 6; // local coords are in bottom 6 bits (64*64)
			this.baseY = (id & 0xFF) << 6;
		}

		public Region(int x, int y)
		{
			this.regionID = x << 8 | y;
			this.baseX = x << 6;
			this.baseY = y << 6;
		}

		public virtual void loadTerrain(MapDefinition map)
		{
			MapDefinition.Tile[][][] tiles = map.getTiles();
			for (int z = 0; z < Z; z++)
			{
				for (int x = 0; x < X; x++)
				{
					for (int y = 0; y < Y; y++)
					{
						MapDefinition.Tile tile = tiles[z][x][y];

						if (tile.height == null)
						{
							if (z == 0)
							{
								tileHeights[0][x][y] = -HeightCalc.calculate(baseX + x + 0xe3b7b, baseY + y + 0x87cce) * 8;
							}
							else
							{
								tileHeights[z][x][y] = tileHeights[z - 1][x][y] - 240;
							}
						}
						else
						{
							int height = tile.getHeight();
							if (height == 1)
							{
								height = 0;
							}

							if (z == 0)
							{
								tileHeights[0][x][y] = -height * 8;
							}
							else
							{
								tileHeights[z][x][y] = tileHeights[z - 1][x][y] - height * 8;
							}
						}

						overlayIds[z][x][y] = tile.getOverlayId();
						overlayPaths[z][x][y] = tile.getOverlayPath();
						overlayRotations[z][x][y] = tile.getOverlayRotation();

						tileSettings[z][x][y] = tile.getSettings();
						underlayIds[z][x][y] = tile.getUnderlayId();
					}
				}
			}
		}

		public virtual void loadLocations(LocationsDefinition locs)
		{
			foreach (Location loc in locs.getLocations())
			{
				Location newLoc = new Location(loc.getId(), loc.getType(), loc.getOrientation(), new Position(BaseX + loc.getPosition().getX(), BaseY + loc.getPosition().getY(), loc.getPosition().getZ()));
				locations.Add(newLoc);
			}
		}

		public virtual int RegionID
		{
			get
			{
				return regionID;
			}
		}

		public virtual int BaseX
		{
			get
			{
				return baseX;
			}
		}

		public virtual int BaseY
		{
			get
			{
				return baseY;
			}
		}

		public virtual int getTileHeight(int z, int x, int y)
		{
			return tileHeights[z][x][y];
		}

		public virtual sbyte getTileSetting(int z, int x, int y)
		{
			return tileSettings[z][x][y];
		}

		public virtual int getOverlayId(int z, int x, int y)
		{
			return overlayIds[z][x][y] & 0xFF;
		}

		public virtual sbyte getOverlayPath(int z, int x, int y)
		{
			return overlayPaths[z][x][y];
		}

		public virtual sbyte getOverlayRotation(int z, int x, int y)
		{
			return overlayRotations[z][x][y];
		}

		public virtual int getUnderlayId(int z, int x, int y)
		{
			return underlayIds[z][x][y] & 0xFF;
		}

		public virtual IList<Location> Locations
		{
			get
			{
				return locations;
			}
		}

		public virtual int RegionX
		{
			get
			{
				return baseX >> 6;
			}
		}

		public virtual int RegionY
		{
			get
			{
				return baseY >> 6;
			}
		}
	}

}