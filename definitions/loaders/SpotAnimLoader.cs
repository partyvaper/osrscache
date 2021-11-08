﻿/*
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
namespace net.runelite.cache.definitions.loaders
{
	using SpotAnimDefinition = net.runelite.cache.definitions.SpotAnimDefinition;
	using InputStream = net.runelite.cache.io.InputStream;
	using Logger = org.slf4j.Logger;
	using LoggerFactory = org.slf4j.LoggerFactory;

	public class SpotAnimLoader
	{
		private static readonly Logger logger = LoggerFactory.getLogger(typeof(SpotAnimLoader));

		public virtual SpotAnimDefinition load(int id, sbyte[] b)
		{
			SpotAnimDefinition def = new SpotAnimDefinition();
			InputStream @is = new InputStream(b);
			def.id = id;

			while (true)
			{
				int opcode = @is.readUnsignedByte();
				if (opcode == 0)
				{
					break;
				}

				this.decodeValues(opcode, def, @is);
			}

			return def;
		}

		private void decodeValues(int opcode, SpotAnimDefinition def, InputStream stream)
		{
			if (opcode == 1)
			{
				def.modelId = stream.readUnsignedShort();
			}
			else if (opcode == 2)
			{
				def.animationId = stream.readUnsignedShort();
			}
			else if (opcode == 4)
			{
				def.resizeX = stream.readUnsignedShort();
			}
			else if (opcode == 5)
			{
				def.resizeY = stream.readUnsignedShort();
			}
			else if (opcode == 6)
			{
				def.rotaton = stream.readUnsignedShort();
			}
			else if (opcode == 7)
			{
				def.ambient = stream.readUnsignedByte();
			}
			else if (opcode == 8)
			{
				def.contrast = stream.readUnsignedByte();
			}
			else if (opcode == 40)
			{
				int var3 = stream.readUnsignedByte();
				def.recolorToFind = new short[var3];
				def.recolorToReplace = new short[var3];

				for (int var4 = 0; var4 < var3; ++var4)
				{
					def.recolorToFind[var4] = (short) stream.readUnsignedShort();
					def.recolorToReplace[var4] = (short) stream.readUnsignedShort();
				}
			}
			else if (opcode == 41)
			{
				int var3 = stream.readUnsignedByte();
				def.textureToFind = new short[var3];
				def.textureToReplace = new short[var3];

				for (int var4 = 0; var4 < var3; ++var4)
				{
					def.textureToFind[var4] = (short) stream.readUnsignedShort();
					def.textureToReplace[var4] = (short) stream.readUnsignedShort();
				}
			}
		}
	}

}