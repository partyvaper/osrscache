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
namespace OSRSCache.definitions.loaders
{
	using ObjectDefinition = OSRSCache.definitions.ObjectDefinition;
	using InputStream = OSRSCache.io.InputStream;


	public class ObjectLoader
	{
		public virtual ObjectDefinition load(int id, byte[] b)
		{
			ObjectDefinition def = new ObjectDefinition();
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

			post(def);

			return def;
		}

		private void processOp(int opcode, ObjectDefinition def, InputStream @is)
		{
			if (opcode == 1)
			{
				int length = @is.readUnsignedByte();
				if (length > 0)
				{
					int[] objectTypes = new int[length];
					int[] objectModels = new int[length];

					for (int index = 0; index < length; ++index)
					{
						objectModels[index] = @is.readUnsignedShort();
						objectTypes[index] = @is.readUnsignedByte();
					}

					def.objectTypes = objectTypes;
					def.objectModels = objectModels;
				}
			}
			else if (opcode == 2)
			{
				def.name = @is.readString();
			}
			else if (opcode == 5)
			{
				int length = @is.readUnsignedByte();
				if (length > 0)
				{
					def.objectTypes = null;
					int[] objectModels = new int[length];

					for (int index = 0; index < length; ++index)
					{
						objectModels[index] = @is.readUnsignedShort();
					}

					def.objectModels = objectModels;
				}
			}
			else if (opcode == 14)
			{
				def.sizeX = @is.readUnsignedByte();
			}
			else if (opcode == 15)
			{
				def.sizeY = @is.readUnsignedByte();
			}
			else if (opcode == 17)
			{
				def.interactType = 0;
				def.blocksProjectile = false;
			}
			else if (opcode == 18)
			{
				def.blocksProjectile = false;
			}
			else if (opcode == 19)
			{
				def.wallOrDoor = @is.readUnsignedByte();
			}
			else if (opcode == 21)
			{
				def.contouredGround = 0;
			}
			else if (opcode == 22)
			{
				def.mergeNormals = true;
			}
			else if (opcode == 23)
			{
				def.aBool2111 = true;
			}
			else if (opcode == 24)
			{
				def.animationID = @is.readUnsignedShort();
				if (def.animationID == 0xFFFF)
				{
					def.animationID = -1;
				}
			}
			else if (opcode == 27)
			{
				def.interactType = 1;
			}
			else if (opcode == 28)
			{
				def.decorDisplacement = @is.readUnsignedByte();
			}
			else if (opcode == 29)
			{
				def.ambient = @is.readByte();
			}
			else if (opcode == 39)
			{
				def.contrast = @is.readByte() * 25;
			}
			else if (opcode >= 30 && opcode < 35)
			{
				string[] actions = def.actions;
				actions[opcode - 30] = @is.readString();
				if (actions[opcode - 30].Equals("Hidden", StringComparison.OrdinalIgnoreCase))
				{
					actions[opcode - 30] = null;
				}
			}
			else if (opcode == 40)
			{
				int length = @is.readUnsignedByte();
				short[] recolorToFind = new short[length];
				short[] recolorToReplace = new short[length];

				for (int index = 0; index < length; ++index)
				{
					recolorToFind[index] = @is.readShort();
					recolorToReplace[index] = @is.readShort();
				}

				def.recolorToFind = recolorToFind;
				def.recolorToReplace = recolorToReplace;
			}
			else if (opcode == 41)
			{
				int length = @is.readUnsignedByte();
				short[] retextureToFind = new short[length];
				short[] textureToReplace = new short[length];

				for (int index = 0; index < length; ++index)
				{
					retextureToFind[index] = @is.readShort();
					textureToReplace[index] = @is.readShort();
				}

				def.retextureToFind = retextureToFind;
				def.textureToReplace = textureToReplace;
			}
			else if (opcode == 61)
			{
				def.category = @is.readUnsignedShort();
			}
			else if (opcode == 62)
			{
				def.isRotated = true;
			}
			else if (opcode == 64)
			{
				def.shadow = false;
			}
			else if (opcode == 65)
			{
				def.modelSizeX = @is.readUnsignedShort();
			}
			else if (opcode == 66)
			{
				def.modelSizeHeight = @is.readUnsignedShort();
			}
			else if (opcode == 67)
			{
				def.modelSizeY = @is.readUnsignedShort();
			}
			else if (opcode == 68)
			{
				def.mapSceneID = @is.readUnsignedShort();
			}
			else if (opcode == 69)
			{
				def.blockingMask = @is.readByte();
			}
			else if (opcode == 70)
			{
				def.offsetX = @is.readUnsignedShort();
			}
			else if (opcode == 71)
			{
				def.offsetHeight = @is.readUnsignedShort();
			}
			else if (opcode == 72)
			{
				def.offsetY = @is.readUnsignedShort();
			}
			else if (opcode == 73)
			{
				def.obstructsGround = true;
			}
			else if (opcode == 74)
			{
				def.isHollow = true;
			}
			else if (opcode == 75)
			{
				def.supportsItems = @is.readUnsignedByte();
			}
			else if (opcode == 77)
			{
				int varpID = @is.readUnsignedShort();
				if (varpID == 0xFFFF)
				{
					varpID = -1;
				}
				def.varbitID = varpID;
				int configId = @is.readUnsignedShort();
				if (configId == 0xFFFF)
				{
					configId = -1;
				}
				def.varpID = configId;
				int length = @is.readUnsignedByte();
				int[] configChangeDest = new int[length + 2];

				for (int index = 0; index <= length; ++index)
				{
					configChangeDest[index] = @is.readUnsignedShort();
					if (0xFFFF == configChangeDest[index])
					{
						configChangeDest[index] = -1;
					}
				}

				configChangeDest[length + 1] = -1;

				def.configChangeDest = configChangeDest;
			}
			else if (opcode == 78)
			{
				def.ambientSoundId = @is.readUnsignedShort();
				def.anInt2083 = @is.readUnsignedByte();
			}
			else if (opcode == 79)
			{
				def.anInt2112 = @is.readUnsignedShort();
				def.anInt2113 = @is.readUnsignedShort();
				def.anInt2083 = @is.readUnsignedByte();
				int length = @is.readUnsignedByte();
				int[] anIntArray2084 = new int[length];

				for (int index = 0; index < length; ++index)
				{
					anIntArray2084[index] = @is.readUnsignedShort();
				}

				def.ambientSoundIds = anIntArray2084;
			}
			else if (opcode == 81)
			{
				def.contouredGround = @is.readUnsignedByte() * 256;
			}
			else if (opcode == 82)
			{
				def.mapAreaId = @is.readUnsignedShort();
			}
			else if (opcode == 89)
			{
				def.randomizeAnimStart = true;
			}
			else if (opcode == 92)
			{
				int varpID = @is.readUnsignedShort();
				if (varpID == 0xFFFF)
				{
					varpID = -1;
				}
				def.varbitID = varpID;
				int configId = @is.readUnsignedShort();
				if (configId == 0xFFFF)
				{
					configId = -1;
				}
				def.varpID = configId;
				int var = @is.readUnsignedShort();
				if (var == 0xFFFF)
				{
					var = -1;
				}

				int length = @is.readUnsignedByte();
				int[] configChangeDest = new int[length + 2];

				for (int index = 0; index <= length; ++index)
				{
					configChangeDest[index] = @is.readUnsignedShort();
					if (0xFFFF == configChangeDest[index])
					{
						configChangeDest[index] = -1;
					}
				}

				configChangeDest[length + 1] = var;

				def.configChangeDest = configChangeDest;
			}
			else if (opcode == 249)
			{
				int length = @is.readUnsignedByte();

				IDictionary<int, object> @params = new Dictionary<int, object>(length);
				for (int i = 0; i < length; i++)
				{
					bool isString = @is.readUnsignedByte() == 1;
					int key = @is.read24BitInt();
					object value;

					if (isString)
					{
						value = @is.readString();
					}

					else
					{
						value = @is.readInt();
					}

					@params[key] = value;
				}

				def.@params = @params;
			}
			else
			{
				Console.WriteLine("ObjectLoader: unrecognized opcode {}", opcode);
			}
		}


		private void post(ObjectDefinition def)
		{
			if (def.wallOrDoor == -1)
			{
				def.wallOrDoor = 0;
				if (def.objectModels != null && (def.objectTypes == null || def.objectTypes[0] == 10))
				{
					def.wallOrDoor = 1;
				}

				for (int var1 = 0; var1 < 5; ++var1)
				{
					if (def.actions[var1] != null)
					{
						def.wallOrDoor = 1;
					}
				}
			}

			if (def.supportsItems == -1)
			{
				def.supportsItems = def.interactType != 0 ? 1 : 0;
			}
		}
	}

}