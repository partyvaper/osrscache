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

namespace net.runelite.cache
{
	public sealed class IndexType
	{
		public static readonly IndexType FRAMES = new IndexType("FRAMES", InnerEnum.FRAMES, 0);
		public static readonly IndexType FRAMEMAPS = new IndexType("FRAMEMAPS", InnerEnum.FRAMEMAPS, 1);
		public static readonly IndexType CONFIGS = new IndexType("CONFIGS", InnerEnum.CONFIGS, 2);
		public static readonly IndexType INTERFACES = new IndexType("INTERFACES", InnerEnum.INTERFACES, 3);
		public static readonly IndexType SOUNDEFFECTS = new IndexType("SOUNDEFFECTS", InnerEnum.SOUNDEFFECTS, 4);
		public static readonly IndexType MAPS = new IndexType("MAPS", InnerEnum.MAPS, 5);
		public static readonly IndexType TRACK1 = new IndexType("TRACK1", InnerEnum.TRACK1, 6);
		public static readonly IndexType MODELS = new IndexType("MODELS", InnerEnum.MODELS, 7);
		public static readonly IndexType SPRITES = new IndexType("SPRITES", InnerEnum.SPRITES, 8);
		public static readonly IndexType TEXTURES = new IndexType("TEXTURES", InnerEnum.TEXTURES, 9);
		public static readonly IndexType BINARY = new IndexType("BINARY", InnerEnum.BINARY, 10);
		public static readonly IndexType TRACK2 = new IndexType("TRACK2", InnerEnum.TRACK2, 11);
		public static readonly IndexType CLIENTSCRIPT = new IndexType("CLIENTSCRIPT", InnerEnum.CLIENTSCRIPT, 12);
		public static readonly IndexType FONTS = new IndexType("FONTS", InnerEnum.FONTS, 13);
		public static readonly IndexType VORBIS = new IndexType("VORBIS", InnerEnum.VORBIS, 14);
		public static readonly IndexType INSTRUMENTS = new IndexType("INSTRUMENTS", InnerEnum.INSTRUMENTS, 15);
		public static readonly IndexType WORLDMAP = new IndexType("WORLDMAP", InnerEnum.WORLDMAP, 16);

		private static readonly List<IndexType> valueList = new List<IndexType>();

		static IndexType()
		{
			valueList.Add(FRAMES);
			valueList.Add(FRAMEMAPS);
			valueList.Add(CONFIGS);
			valueList.Add(INTERFACES);
			valueList.Add(SOUNDEFFECTS);
			valueList.Add(MAPS);
			valueList.Add(TRACK1);
			valueList.Add(MODELS);
			valueList.Add(SPRITES);
			valueList.Add(TEXTURES);
			valueList.Add(BINARY);
			valueList.Add(TRACK2);
			valueList.Add(CLIENTSCRIPT);
			valueList.Add(FONTS);
			valueList.Add(VORBIS);
			valueList.Add(INSTRUMENTS);
			valueList.Add(WORLDMAP);
		}

		public enum InnerEnum
		{
			FRAMES,
			FRAMEMAPS,
			CONFIGS,
			INTERFACES,
			SOUNDEFFECTS,
			MAPS,
			TRACK1,
			MODELS,
			SPRITES,
			TEXTURES,
			BINARY,
			TRACK2,
			CLIENTSCRIPT,
			FONTS,
			VORBIS,
			INSTRUMENTS,
			WORLDMAP
		}

		public readonly InnerEnum innerEnumValue;
		private readonly string nameValue;
		private readonly int ordinalValue;
		private static int nextOrdinal = 0;

		private int id;

		internal IndexType(string name, InnerEnum innerEnum, int id)
		{
			this.id = id;

			nameValue = name;
			ordinalValue = nextOrdinal++;
			innerEnumValue = innerEnum;
		}

		public int Number
		{
			get
			{
				return id;
			}
		}

		public static IndexType[] values()
		{
			return valueList.ToArray();
		}

		public int ordinal()
		{
			return ordinalValue;
		}

		public override string ToString()
		{
			return nameValue;
		}

		public static IndexType valueOf(string name)
		{
			foreach (IndexType enumInstance in IndexType.valueList)
			{
				if (enumInstance.nameValue == name)
				{
					return enumInstance;
				}
			}
			throw new System.ArgumentException(name);
		}
	}
}