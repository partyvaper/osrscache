﻿/*
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
namespace OSRSCache.definitions.loaders
{
	using OverlayDefinition = OSRSCache.definitions.OverlayDefinition;
	using InputStream = OSRSCache.io.InputStream;


	public class OverlayLoader
	{
		public virtual OverlayDefinition load(int id, byte[] b)
		{
			OverlayDefinition def = new OverlayDefinition();
			InputStream @is = new InputStream(b);

			def.id = id;

			for (;;)
			{
				int opcode = @is.readUnsignedByte();
				if (opcode == 0)
				{
					break;
				}

				if (opcode == 1)
				{
					int color = @is.read24BitInt();
					def.rgbColor = color;
				}
				else if (opcode == 2)
				{
					int texture = @is.readUnsignedByte();
					def.texture = texture;
				}
				else if (opcode == 5)
				{
					def.hideUnderlay = false;
				}
				else if (opcode == 7)
				{
					int secondaryColor = @is.read24BitInt();
					def.secondaryRgbColor = secondaryColor;
				}
			}

			def.calculateHsl();

			return def;
		}
	}

}