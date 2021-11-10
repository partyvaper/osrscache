using System;
using System.Collections.Generic;

namespace OSRSCache.definitions.loaders
{
	using NpcDefinition = OSRSCache.definitions.NpcDefinition;
	using InputStream = OSRSCache.io.InputStream;


	public class NpcLoader
	{
		public virtual NpcDefinition load(int id, sbyte[] b)
		{
			NpcDefinition def = new NpcDefinition(id);
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

		private void decodeValues(int opcode, NpcDefinition def, InputStream stream)
		{
			int length;
			int index;
			if (opcode == 1)
			{
				length = stream.readUnsignedByte();
				def.models = new int[length];

				for (index = 0; index < length; ++index)
				{
					def.models[index] = stream.readUnsignedShort();
				}
			}
			else if (opcode == 2)
			{
				def.name = stream.readString();
			}
			else if (opcode == 12)
			{
				def.size = stream.readUnsignedByte();
			}
			else if (opcode == 13)
			{
				def.standingAnimation = stream.readUnsignedShort();
			}
			else if (opcode == 14)
			{
				def.walkingAnimation = stream.readUnsignedShort();
			}
			else if (opcode == 15)
			{
				def.rotateLeftAnimation = stream.readUnsignedShort();
			}
			else if (opcode == 16)
			{
				def.rotateRightAnimation = stream.readUnsignedShort();
			}
			else if (opcode == 17)
			{
				def.walkingAnimation = stream.readUnsignedShort();
				def.rotate180Animation = stream.readUnsignedShort();
				def.rotate90RightAnimation = stream.readUnsignedShort();
				def.rotate90LeftAnimation = stream.readUnsignedShort();
			}
			else if (opcode == 18)
			{
				def.category = stream.readUnsignedShort();
			}
			else if (opcode >= 30 && opcode < 35)
			{
				def.actions[opcode - 30] = stream.readString();
				if (def.actions[opcode - 30].Equals("Hidden", StringComparison.OrdinalIgnoreCase))
				{
					def.actions[opcode - 30] = null;
				}
			}
			else if (opcode == 40)
			{
				length = stream.readUnsignedByte();
				def.recolorToFind = new short[length];
				def.recolorToReplace = new short[length];

				for (index = 0; index < length; ++index)
				{
					def.recolorToFind[index] = (short) stream.readUnsignedShort();
					def.recolorToReplace[index] = (short) stream.readUnsignedShort();
				}

			}
			else if (opcode == 41)
			{
				length = stream.readUnsignedByte();
				def.retextureToFind = new short[length];
				def.retextureToReplace = new short[length];

				for (index = 0; index < length; ++index)
				{
					def.retextureToFind[index] = (short) stream.readUnsignedShort();
					def.retextureToReplace[index] = (short) stream.readUnsignedShort();
				}

			}
			else if (opcode == 60)
			{
				length = stream.readUnsignedByte();
				def.chatheadModels = new int[length];

				for (index = 0; index < length; ++index)
				{
					def.chatheadModels[index] = stream.readUnsignedShort();
				}

			}
			else if (opcode == 93)
			{
				def.isMinimapVisible = false;
			}
			else if (opcode == 95)
			{
				def.combatLevel = stream.readUnsignedShort();
			}
			else if (opcode == 97)
			{
				def.widthScale = stream.readUnsignedShort();
			}
			else if (opcode == 98)
			{
				def.heightScale = stream.readUnsignedShort();
			}
			else if (opcode == 99)
			{
				def.hasRenderPriority = true;
			}
			else if (opcode == 100)
			{
				def.ambient = stream.readByte();
			}
			else if (opcode == 101)
			{
				def.contrast = stream.readByte();
			}
			else if (opcode == 102)
			{
				def.headIcon = stream.readUnsignedShort();
			}
			else if (opcode == 103)
			{
				def.rotationSpeed = stream.readUnsignedShort();
			}
			else if (opcode == 106)
			{
				def.varbitId = stream.readUnsignedShort();
				if (def.varbitId == 65535)
				{
					def.varbitId = -1;
				}

				def.varpIndex = stream.readUnsignedShort();
				if (def.varpIndex == 65535)
				{
					def.varpIndex = -1;
				}

				length = stream.readUnsignedByte();
				def.configs = new int[length + 2];

				for (index = 0; index <= length; ++index)
				{
					def.configs[index] = stream.readUnsignedShort();
					if (def.configs[index] == '\uffff')
					{
						def.configs[index] = -1;
					}
				}

				def.configs[length + 1] = -1;

			}
			else if (opcode == 107)
			{
				def.isInteractable = false;
			}
			else if (opcode == 109)
			{
				def.rotationFlag = false;
			}
			else if (opcode == 111)
			{
				def.isPet = true;
			}
			else if (opcode == 118)
			{
				def.varbitId = stream.readUnsignedShort();
				if (def.varbitId == 65535)
				{
					def.varbitId = -1;
				}

				def.varpIndex = stream.readUnsignedShort();
				if (def.varpIndex == 65535)
				{
					def.varpIndex = -1;
				}

				int var = stream.readUnsignedShort();
				if (var == 0xFFFF)
				{
					var = -1;
				}

				length = stream.readUnsignedByte();
				def.configs = new int[length + 2];

				for (index = 0; index <= length; ++index)
				{
					def.configs[index] = stream.readUnsignedShort();
					if (def.configs[index] == '\uffff')
					{
						def.configs[index] = -1;
					}
				}

				def.configs[length + 1] = var;
			}
			else if (opcode == 249)
			{
				length = stream.readUnsignedByte();

				def.@params = new Dictionary<int, object>(length);

				for (int i = 0; i < length; i++)
				{
					bool isString = stream.readUnsignedByte() == 1;
					int key = stream.read24BitInt();
					object value;

					if (isString)
					{
						value = stream.readString();
					}

					else
					{
						value = stream.readInt();
					}

					def.@params[key] = value;
				}
			}
			else
			{
				Console.WriteLine("NpcLoader: unrecognized opcode {}", opcode);
			}
		}
	}

}