using System.Collections.Generic;

/*
 * Copyright (c) 2018, Joshua Filby <joshua@filby.me>
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
namespace net.runelite.cache.util
{
	using AllArgsConstructor = lombok.AllArgsConstructor;

//JAVA TO C# CONVERTER TODO TASK: Most Java annotations will not have direct .NET equivalent attributes:
//ORIGINAL LINE: @AllArgsConstructor public enum ScriptVarType
	public sealed class ScriptVarType
	{
		public static readonly ScriptVarType INTEGER = new ScriptVarType("INTEGER", InnerEnum.INTEGER, 'i', "integer");
		public static readonly ScriptVarType BOOLEAN = new ScriptVarType("BOOLEAN", InnerEnum.BOOLEAN, '1', "boolean");
		public static readonly ScriptVarType SEQ = new ScriptVarType("SEQ", InnerEnum.SEQ, 'A', "seq");
		public static readonly ScriptVarType COLOUR = new ScriptVarType("COLOUR", InnerEnum.COLOUR, 'C', "colour");
		/// <summary>
		/// Also known as {@code Widget}.
		/// </summary>
		public static readonly ScriptVarType COMPONENT = new ScriptVarType("COMPONENT", InnerEnum.COMPONENT, 'I', "component");
		public static readonly ScriptVarType IDKIT = new ScriptVarType("IDKIT", InnerEnum.IDKIT, 'K', "idkit");
		public static readonly ScriptVarType MIDI = new ScriptVarType("MIDI", InnerEnum.MIDI, 'M', "midi");
		public static readonly ScriptVarType SYNTH = new ScriptVarType("SYNTH", InnerEnum.SYNTH, 'P', "synth");
		public static readonly ScriptVarType STAT = new ScriptVarType("STAT", InnerEnum.STAT, 'S', "stat");
		public static readonly ScriptVarType COORDGRID = new ScriptVarType("COORDGRID", InnerEnum.COORDGRID, 'c', "coordgrid");
		public static readonly ScriptVarType GRAPHIC = new ScriptVarType("GRAPHIC", InnerEnum.GRAPHIC, 'd', "graphic");
		public static readonly ScriptVarType FONTMETRICS = new ScriptVarType("FONTMETRICS", InnerEnum.FONTMETRICS, 'f', "fontmetrics");
		public static readonly ScriptVarType ENUM = new ScriptVarType("ENUM", InnerEnum.ENUM, 'g', "enum");
		public static readonly ScriptVarType JINGLE = new ScriptVarType("JINGLE", InnerEnum.JINGLE, 'j', "jingle");
		/// <summary>
		/// Also known as {@code Object}.
		/// </summary>
		public static readonly ScriptVarType LOC = new ScriptVarType("LOC", InnerEnum.LOC, 'l', "loc");
		public static readonly ScriptVarType MODEL = new ScriptVarType("MODEL", InnerEnum.MODEL, 'm', "model");
		public static readonly ScriptVarType NPC = new ScriptVarType("NPC", InnerEnum.NPC, 'n', "npc");
		/// <summary>
		/// Also known as {@code Item}.
		/// </summary>
		public static readonly ScriptVarType OBJ = new ScriptVarType("OBJ", InnerEnum.OBJ, 'o', "obj");
		/// <summary>
		/// Another version of {@code OBJ}, but means that on Jagex's side they used the internal name for an item.
		/// </summary>
		public static readonly ScriptVarType NAMEDOBJ = new ScriptVarType("NAMEDOBJ", InnerEnum.NAMEDOBJ, 'O', "namedobj");
		public static readonly ScriptVarType STRING = new ScriptVarType("STRING", InnerEnum.STRING, 's', "string");
		public static readonly ScriptVarType SPOTANIM = new ScriptVarType("SPOTANIM", InnerEnum.SPOTANIM, 't', "spotanim");
		public static readonly ScriptVarType INV = new ScriptVarType("INV", InnerEnum.INV, 'v', "inv");
		public static readonly ScriptVarType TEXTURE = new ScriptVarType("TEXTURE", InnerEnum.TEXTURE, 'x', "texture");
		public static readonly ScriptVarType CHAR = new ScriptVarType("CHAR", InnerEnum.CHAR, 'z', "char");
		public static readonly ScriptVarType MAPSCENEICON = new ScriptVarType("MAPSCENEICON", InnerEnum.MAPSCENEICON, '£', "mapsceneicon");
		public static readonly ScriptVarType MAPELEMENT = new ScriptVarType("MAPELEMENT", InnerEnum.MAPELEMENT, 'µ', "mapelement");
		public static readonly ScriptVarType HITMARK = new ScriptVarType("HITMARK", InnerEnum.HITMARK, '×', "hitmark");
		public static readonly ScriptVarType STRUCT = new ScriptVarType("STRUCT", InnerEnum.STRUCT, 'J', "struct");

		private static readonly List<ScriptVarType> valueList = new List<ScriptVarType>();

		public enum InnerEnum
		{
			INTEGER,
			BOOLEAN,
			SEQ,
			COLOUR,
			COMPONENT,
			IDKIT,
			MIDI,
			SYNTH,
			STAT,
			COORDGRID,
			GRAPHIC,
			FONTMETRICS,
			ENUM,
			JINGLE,
			LOC,
			MODEL,
			NPC,
			OBJ,
			NAMEDOBJ,
			STRING,
			SPOTANIM,
			INV,
			TEXTURE,
			CHAR,
			MAPSCENEICON,
			MAPELEMENT,
			HITMARK,
			STRUCT
		}

		public readonly InnerEnum innerEnumValue;
		private readonly string nameValue;
		private readonly int ordinalValue;
		private static int nextOrdinal = 0;

		private static readonly IDictionary<char, ScriptVarType> keyToTypeMap = new Dictionary<char, ScriptVarType>();

		static ScriptVarType()
		{
			foreach (ScriptVarType type in values())
			{
				keyToTypeMap.put(type.keyChar, type);
			}

			valueList.Add(INTEGER);
			valueList.Add(BOOLEAN);
			valueList.Add(SEQ);
			valueList.Add(COLOUR);
			valueList.Add(COMPONENT);
			valueList.Add(IDKIT);
			valueList.Add(MIDI);
			valueList.Add(SYNTH);
			valueList.Add(STAT);
			valueList.Add(COORDGRID);
			valueList.Add(GRAPHIC);
			valueList.Add(FONTMETRICS);
			valueList.Add(ENUM);
			valueList.Add(JINGLE);
			valueList.Add(LOC);
			valueList.Add(MODEL);
			valueList.Add(NPC);
			valueList.Add(OBJ);
			valueList.Add(NAMEDOBJ);
			valueList.Add(STRING);
			valueList.Add(SPOTANIM);
			valueList.Add(INV);
			valueList.Add(TEXTURE);
			valueList.Add(CHAR);
			valueList.Add(MAPSCENEICON);
			valueList.Add(MAPELEMENT);
			valueList.Add(HITMARK);
			valueList.Add(STRUCT);
		}

		public static ScriptVarType forCharKey(char key)
		{
			return keyToTypeMap.get(key);
		}

		/// <summary>
		/// The character used when encoding or decoding types.
		/// </summary>
		private readonly char keyChar;

		/// <summary>
		/// The full name of the var type.
		/// </summary>
		private readonly string fullName;


		public static ScriptVarType[] values()
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

		public static ScriptVarType valueOf(string name)
		{
			foreach (ScriptVarType enumInstance in ScriptVarType.valueList)
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