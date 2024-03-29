﻿/*
 * Copyright (c) 2020, Hexagon <hexagon@fking.work>
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
	using HitSplatDefinition = OSRSCache.definitions.HitSplatDefinition;
	using InputStream = OSRSCache.io.InputStream;

	public class HitSplatLoader
	{
		public virtual HitSplatDefinition load(byte[] data)
		{
			HitSplatDefinition def = new HitSplatDefinition();
			InputStream stream = new InputStream(data);

			for (; ;)
			{
				int opcode = stream.readUnsignedByte();

				switch (opcode)
				{
					case 0:
						return def;
					case 1:
						def.fontType = stream.readBigSmart2();
						break;
					case 2:
						def.textColor = stream.read24BitInt();
						break;
					case 3:
						def.leftSprite = stream.readBigSmart2();
						break;
					case 4:
						def.leftSprite2 = stream.readBigSmart2();
						break;
					case 5:
						def.backgroundSprite = stream.readBigSmart2();
						break;
					case 6:
						def.rightSpriteId = stream.readBigSmart2();
						break;
					case 7:
						def.scrollToOffsetX = stream.readShort();
						break;
					case 8:
						def.stringFormat = stream.readString2();
						break;
					case 9:
						def.displayCycles = stream.readUnsignedShort();
						break;
					case 10:
						def.scrollToOffsetY = stream.readShort();
						break;
					case 11:
						def.fadeStartCycle = 0;
						break;
					case 12:
						def.useDamage = stream.readUnsignedByte();
						break;
					case 13:
						def.textOffsetY = stream.readShort();
						break;
					case 14:
						def.fadeStartCycle = stream.readUnsignedShort();
						break;
					case 17:
					case 18:
						int varbitId = stream.readUnsignedShort();

						if (varbitId == 0xFFFF)
						{
							varbitId = -1;
						}
						def.varbitID = varbitId;

						int varp = stream.readUnsignedShort();
						if (varp == 0xFFFF)
						{
							varp = -1;
						}
						def.varpID = varp;

						int id = -1;
						if (opcode == 18)
						{
							id = stream.readUnsignedShort();
							if (id == 0xFFFF)
							{
								id = -1;
							}
						}

						int length = stream.readUnsignedByte();
						int[] multihitsplats = new int[length + 2];

						for (int i = 0; i <= length; i++)
						{
							multihitsplats[i] = stream.readUnsignedShort();
							if (multihitsplats[i] == 0xFFFF)
							{
								multihitsplats[i] = -1;
							}
						}

						multihitsplats[length + 1] = id;

						def.multihitsplats = multihitsplats;
						break;
				}
			}
		}
	}

}