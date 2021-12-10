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

using System;

namespace OSRSCache.definitions.loaders
{
	using EnumDefinition = OSRSCache.definitions.EnumDefinition;
	using InputStream = OSRSCache.io.InputStream;
	using ScriptVarType = OSRSCache.util.ScriptVarType;


	public class EnumLoader
	{
		public virtual EnumDefinition load(int id, byte[] b)
		{
			if (b.Length == 1 && b[0] == 0)
			{
				return null;
			}

			EnumDefinition def = new EnumDefinition();
			InputStream @is = new InputStream(b);

			def.id = id;

			for (;;)
			{
				int opcode = @is.readUnsignedByte();
				if (opcode == 0)
				{
					break;
				}

				processOp(opcode, def, @is);
			}

			return def;
		}

		private void processOp(int opcode, EnumDefinition def, InputStream @is)
		{
			switch (opcode)
			{
				case 1:
					def.keyType = ScriptVarType.forCharKey((char) @is.readUnsignedByte());
					break;
				case 2:
					def.valType = ScriptVarType.forCharKey((char) @is.readUnsignedByte());
					break;
				case 3:
					def.defaultString = @is.readString();
					break;
				case 4:
					def.defaultInt = @is.readInt();
					break;
				case 5:
				{
					int size = @is.readUnsignedShort();
					int[] keys = new int[size];
					string[] stringVals = new string[size];
					for (int index = 0; index < size; ++index)
					{
						keys[index] = @is.readInt();
						stringVals[index] = @is.readString();
					}

					def.size = size;
					def.keys = keys;
					def.stringVals = stringVals;
					break;
				}
				case 6:
				{
					int size = @is.readUnsignedShort();
					int[] keys = new int[size];
					int[] intVals = new int[size];
					for (int index = 0; index < size; ++index)
					{
						keys[index] = @is.readInt();
						intVals[index] = @is.readInt();
					}
					def.size = size;
					def.keys = keys;
					def.intVals = intVals;
					break;
				}
				default:
					Console.WriteLine("EnumLoader: unrecognized opcode {0}", opcode);
					break;
			}
		}
	}

}