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
namespace OSRSCache.definitions.loaders
{
	using MapDefinition = OSRSCache.definitions.MapDefinition;
	using Tile = OSRSCache.definitions.MapDefinition.Tile;
	using InputStream = OSRSCache.io.InputStream;
//JAVA TO C# CONVERTER TODO TASK: This Java 'import static' statement cannot be converted to C#:
//	import static OSRSCache.region.Region.X;
//JAVA TO C# CONVERTER TODO TASK: This Java 'import static' statement cannot be converted to C#:
//	import static OSRSCache.region.Region.Y;
//JAVA TO C# CONVERTER TODO TASK: This Java 'import static' statement cannot be converted to C#:
//	import static OSRSCache.region.Region.Z;

	public class MapLoader
	{
		public virtual MapDefinition load(int regionX, int regionY, byte[] b)
		{
			MapDefinition map = new MapDefinition();
			map.regionX = regionX;
			map.regionY = regionY;
			loadTerrain(map, b);
			return map;
		}

		private void loadTerrain(MapDefinition map, byte[] buf)
		{
			MapDefinition.Tile[][][] tiles = map.tiles;

			InputStream @in = new InputStream(buf);

			for (int z = 0; z < MapDefinition.Z; z++)
			{
				for (int x = 0; x < MapDefinition.X; x++)
				{
					for (int y = 0; y < MapDefinition.Y; y++)
					{
						MapDefinition.Tile tile = tiles[z][x][y] = new MapDefinition.Tile();
						while (true)
						{
							int attribute = @in.readUnsignedByte();
							if (attribute == 0)
							{
								break;
							}
							else if (attribute == 1)
							{
								int height = @in.readUnsignedByte();
								tile.height = height;
								break;
							}
							else if (attribute <= 49)
							{
								tile.attrOpcode = attribute;
								tile.overlayId = @in.readByte();
								tile.overlayPath = (byte)((attribute - 2) / 4);
								tile.overlayRotation = (byte)(attribute - 2 & 3);
							}
							else if (attribute <= 81)
							{
								tile.settings = (byte)(attribute - 49);
							}
							else
							{
								tile.underlayId = (byte)(attribute - 81);
							}
						}
					}
				}
			}
		}
	}

}