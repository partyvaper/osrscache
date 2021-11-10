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

namespace OSRSCache
{
	public sealed class ConfigType
	{
		// types from https://github.com/im-frizzy/OpenRS/blob/master/source/net/openrs/cache/type/ConfigArchive.java
		public static readonly ConfigType UNDERLAY = new ConfigType("UNDERLAY", InnerEnum.UNDERLAY, 1);
		public static readonly ConfigType IDENTKIT = new ConfigType("IDENTKIT", InnerEnum.IDENTKIT, 3);
		public static readonly ConfigType OVERLAY = new ConfigType("OVERLAY", InnerEnum.OVERLAY, 4);
		public static readonly ConfigType INV = new ConfigType("INV", InnerEnum.INV, 5);
		public static readonly ConfigType OBJECT = new ConfigType("OBJECT", InnerEnum.OBJECT, 6);
		public static readonly ConfigType ENUM = new ConfigType("ENUM", InnerEnum.ENUM, 8);
		public static readonly ConfigType NPC = new ConfigType("NPC", InnerEnum.NPC, 9);
		public static readonly ConfigType ITEM = new ConfigType("ITEM", InnerEnum.ITEM, 10);
		public static readonly ConfigType PARAMS = new ConfigType("PARAMS", InnerEnum.PARAMS, 11);
		public static readonly ConfigType SEQUENCE = new ConfigType("SEQUENCE", InnerEnum.SEQUENCE, 12);
		public static readonly ConfigType SPOTANIM = new ConfigType("SPOTANIM", InnerEnum.SPOTANIM, 13);
		public static readonly ConfigType VARBIT = new ConfigType("VARBIT", InnerEnum.VARBIT, 14);
		public static readonly ConfigType VARCLIENT = new ConfigType("VARCLIENT", InnerEnum.VARCLIENT, 19);
		public static readonly ConfigType VARCLIENTSTRING = new ConfigType("VARCLIENTSTRING", InnerEnum.VARCLIENTSTRING, 15);
		public static readonly ConfigType VARPLAYER = new ConfigType("VARPLAYER", InnerEnum.VARPLAYER, 16);
		public static readonly ConfigType HITSPLAT = new ConfigType("HITSPLAT", InnerEnum.HITSPLAT, 32);
		public static readonly ConfigType HEALTHBAR = new ConfigType("HEALTHBAR", InnerEnum.HEALTHBAR, 33);
		public static readonly ConfigType STRUCT = new ConfigType("STRUCT", InnerEnum.STRUCT, 34);
		public static readonly ConfigType AREA = new ConfigType("AREA", InnerEnum.AREA, 35);

		private static readonly List<ConfigType> valueList = new List<ConfigType>();

		static ConfigType()
		{
			valueList.Add(UNDERLAY);
			valueList.Add(IDENTKIT);
			valueList.Add(OVERLAY);
			valueList.Add(INV);
			valueList.Add(OBJECT);
			valueList.Add(ENUM);
			valueList.Add(NPC);
			valueList.Add(ITEM);
			valueList.Add(PARAMS);
			valueList.Add(SEQUENCE);
			valueList.Add(SPOTANIM);
			valueList.Add(VARBIT);
			valueList.Add(VARCLIENT);
			valueList.Add(VARCLIENTSTRING);
			valueList.Add(VARPLAYER);
			valueList.Add(HITSPLAT);
			valueList.Add(HEALTHBAR);
			valueList.Add(STRUCT);
			valueList.Add(AREA);
		}

		public enum InnerEnum
		{
			UNDERLAY,
			IDENTKIT,
			OVERLAY,
			INV,
			OBJECT,
			ENUM,
			NPC,
			ITEM,
			PARAMS,
			SEQUENCE,
			SPOTANIM,
			VARBIT,
			VARCLIENT,
			VARCLIENTSTRING,
			VARPLAYER,
			HITSPLAT,
			HEALTHBAR,
			STRUCT,
			AREA
		}

		public readonly InnerEnum innerEnumValue;
		private readonly string nameValue;
		private readonly int ordinalValue;
		private static int nextOrdinal = 0;

		private readonly int id;

		internal ConfigType(string name, InnerEnum innerEnum, int id)
		{
			this.id = id;

			nameValue = name;
			ordinalValue = nextOrdinal++;
			innerEnumValue = innerEnum;
		}

		public int Id
		{
			get
			{
				return id;
			}
		}

		public static ConfigType[] values()
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

		public static ConfigType valueOf(string name)
		{
			foreach (ConfigType enumInstance in ConfigType.valueList)
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