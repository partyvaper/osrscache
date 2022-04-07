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
namespace OSRSCache.definitions.savers
{
	using MapDefinition = OSRSCache.definitions.MapDefinition;
	using Tile = OSRSCache.definitions.MapDefinition.Tile;
	using OutputStream = OSRSCache.io.OutputStream;
//JAVA TO C# CONVERTER TODO TASK: This Java 'import static' statement cannot be converted to C#:
//	import static OSRSCache.region.Region.X;
//JAVA TO C# CONVERTER TODO TASK: This Java 'import static' statement cannot be converted to C#:
//	import static OSRSCache.region.Region.Y;
//JAVA TO C# CONVERTER TODO TASK: This Java 'import static' statement cannot be converted to C#:
//	import static OSRSCache.region.Region.Z;

	public class MapSaver
	{
		public virtual byte[] save(MapDefinition map)
		{
			MapDefinition.Tile[][][] tiles = map.tiles;
			OutputStream @out = new OutputStream();
			for (int z = 0; z < MapDefinition.Z; z++)
			{
				for (int x = 0; x < MapDefinition.X; x++)
				{
					for (int y = 0; y < MapDefinition.Y; y++)
					{
						MapDefinition.Tile tile = tiles[z][x][y];
						if (tile.attrOpcode != 0)
						{
							@out.writeByte(tile.attrOpcode);
							@out.writeByte(tile.overlayId);
						}
						if (tile.settings != 0)
						{
							@out.writeByte(tile.settings + 49);
						}
						if (tile.underlayId != 0)
						{
							@out.writeByte(tile.underlayId + 81);
						}
						if (tile.height == null)
						{
							@out.writeByte(0);
						}
						else
						{
							@out.writeByte(1);
							@out.writeByte(tile.height.Value);
						}
					}
				}
			}
			return @out.flip();
		}
	}

}