#pragma once

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
namespace net::runelite::cache::util
{


//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @AllArgsConstructor @Getter public enum ScriptVarType
	enum class ScriptVarType
	{
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		INTEGER(0, L'i', L"integer"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		BOOLEAN(1, L'1', L"boolean"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		SEQ(6, L'A', L"seq"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		COLOUR(7, L'C', L"colour"),
		/**
		 * Also known as {@code Widget}.
		 */
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		COMPONENT(9, L'I', L"component"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		IDKIT(10, L'K', L"idkit"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		MIDI(11, L'M', L"midi"),
		/**
		 * Another version of {@code OBJ}, but means that on Jagex's side they used the internal name for an item.
		 */
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		NAMEDOBJ(13, L'O', L"namedobj"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		SYNTH(14, L'P', L"synth"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		STAT(17, L'S', L"stat"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		COORDGRID(22, L'c', L"coordgrid"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		GRAPHIC(23, L'd', L"graphic"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		FONTMETRICS(25, L'f', L"fontmetrics"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		ENUM(26, L'g', L"enum"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		JINGLE(28, L'j', L"jingle"),
		/**
		 * Also known as {@code Object}.
		 */
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		LOC(30, L'l', L"loc"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		MODEL(31, L'm', L"model"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		NPC(32, L'n', L"npc"),
		/**
		 * Also known as {@code Item}.
		 */
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		OBJ(33, L'o', L"obj"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		STRING(36, L's', L"string"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		SPOTANIM(37, L't', L"spotanim"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		INV(39, L'v', L"inv"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		TEXTURE(40, L'x', L"texture"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		CHAR(42, L'z', L"char"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		MAPSCENEICON(55, L'£', L"mapsceneicon"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		MAPELEMENT(59, L'µ', L"mapelement"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		HITMARK(62, L'×', L"hitmark"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		STRUCT(73, L'J', L"struct"),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		DBROW(74, L'Ð', L"dbrow")

//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//		private static final java.util.Map<int, ScriptVarType> idToTypeMap = new java.util.HashMap<>();
//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//		private static final java.util.Map<char, ScriptVarType> keyToTypeMap = new java.util.HashMap<>();

//JAVA TO C++ CONVERTER TODO TASK: Java to C++ Converter does not convert types within enums:
//			private class StaticConstructor
	//		{
	//			public StaticConstructor()
	//			{
	//			for (ScriptVarType type : values())
	//			{
	//				if (type.id != -1)
	//				{
	//					idToTypeMap.put(type.id, type);
	//				}
	//				keyToTypeMap.put(type.keyChar, type);
	//			}
	//			}
	//		}

//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//			private static StaticConstructor staticConstructor;


//JAVA TO C++ CONVERTER TODO TASK: Enum methods are not converted by Java to C++ Converter:
//		public static ScriptVarType forId(int id)
	//	{
	//		return idToTypeMap.get(id);
	//	}

//JAVA TO C++ CONVERTER TODO TASK: Enum methods are not converted by Java to C++ Converter:
//		public static ScriptVarType forCharKey(char key)
	//	{
	//		return keyToTypeMap.get(key);
	//	}

		/**
		 * The type id when encoding or decoding types from some data structures.
		 */
//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//		private final int id;

		/**
		 * The character used when encoding or decoding types.
		 */
//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//		private final char keyChar;

		/**
		 * The full name of the var type.
		 */
//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//		private final String fullName;

	};

}
