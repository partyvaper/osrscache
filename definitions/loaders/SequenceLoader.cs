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
	using SequenceDefinition = OSRSCache.definitions.SequenceDefinition;
	using InputStream = OSRSCache.io.InputStream;

	public class SequenceLoader
	{
		public virtual SequenceDefinition load(int id, byte[] b)
		{
			SequenceDefinition def = new SequenceDefinition(id);
			InputStream @is = new InputStream(b);

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

		private void decodeValues(int opcode, SequenceDefinition def, InputStream stream)
		{
			int var3;
			int var4;
			if (opcode == 1)
			{
				var3 = stream.readUnsignedShort();
				def.frameLenghts = new int[var3];

				for (var4 = 0; var4 < var3; ++var4)
				{
					def.frameLenghts[var4] = stream.readUnsignedShort();
				}

				def.frameIDs = new int[var3];

				for (var4 = 0; var4 < var3; ++var4)
				{
					def.frameIDs[var4] = stream.readUnsignedShort();
				}

				for (var4 = 0; var4 < var3; ++var4)
				{
					def.frameIDs[var4] += stream.readUnsignedShort() << 16;
				}
			}
			else if (opcode == 2)
			{
				def.frameStep = stream.readUnsignedShort();
			}
			else if (opcode == 3)
			{
				var3 = stream.readUnsignedByte();
				def.interleaveLeave = new int[1 + var3];

				for (var4 = 0; var4 < var3; ++var4)
				{
					def.interleaveLeave[var4] = stream.readUnsignedByte();
				}

				def.interleaveLeave[var3] = 9999999;
			}
			else if (opcode == 4)
			{
				def.stretches = true;
			}
			else if (opcode == 5)
			{
				def.forcedPriority = stream.readUnsignedByte();
			}
			else if (opcode == 6)
			{
				def.leftHandItem = stream.readUnsignedShort();
			}
			else if (opcode == 7)
			{
				def.rightHandItem = stream.readUnsignedShort();
			}
			else if (opcode == 8)
			{
				def.maxLoops = stream.readUnsignedByte();
			}
			else if (opcode == 9)
			{
				def.precedenceAnimating = stream.readUnsignedByte();
			}
			else if (opcode == 10)
			{
				def.priority = stream.readUnsignedByte();
			}
			else if (opcode == 11)
			{
				def.replyMode = stream.readUnsignedByte();
			}
			else if (opcode == 12)
			{
				var3 = stream.readUnsignedByte();
				def.chatFrameIds = new int[var3];

				for (var4 = 0; var4 < var3; ++var4)
				{
					def.chatFrameIds[var4] = stream.readUnsignedShort();
				}

				for (var4 = 0; var4 < var3; ++var4)
				{
					def.chatFrameIds[var4] += stream.readUnsignedShort() << 16;
				}
			}
			else if (opcode == 13)
			{
				var3 = stream.readUnsignedByte();
				def.frameSounds = new int[var3];

				for (var4 = 0; var4 < var3; ++var4)
				{
					def.frameSounds[var4] = stream.read24BitInt();
				}
			}

		}
	}

}