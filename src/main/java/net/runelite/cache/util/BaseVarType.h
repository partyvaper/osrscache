#pragma once

/*
 * Copyright (c) 2022, Joshua Filby <joshua@filby.me>
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
//ORIGINAL LINE: @AllArgsConstructor public enum BaseVarType
	enum class BaseVarType
	{
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		INTEGER(0, Integer.class),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		LONG(1, Long.class),
//JAVA TO C++ CONVERTER TODO TASK: Non-ordinal enum value constructions are not converted by Java to C++ Converter:
		STRING(2, String.class)

//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//		private static final BaseVarType[] VALUES = values();

//JAVA TO C++ CONVERTER TODO TASK: Enum methods are not converted by Java to C++ Converter:
//		public static BaseVarType forId(int id)
	//	{
	//		for (BaseVarType type : VALUES)
	//		{
	//			if (type.id == id)
	//			{
	//				return type;
	//			}
	//		}
	//		return nullptr;
	//	}

		/**
		 * The id of the type when being encoded or decoded.
		 */
//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//		private final int id;

		/**
		 * The class the base type represents.
		 */
//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//		private final Class clazz;
	};

}
