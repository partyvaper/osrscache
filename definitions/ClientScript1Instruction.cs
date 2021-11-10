using System.Collections.Generic;

/*
 * Copyright (c) 2018 Abex
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
namespace OSRSCache.definitions
{

//JAVA TO C# CONVERTER TODO TASK: Most Java annotations will not have direct .NET equivalent attributes:
//ORIGINAL LINE: @Data public class ClientScript1Instruction
	public class ClientScript1Instruction
	{
//JAVA TO C# CONVERTER TODO TASK: Most Java annotations will not have direct .NET equivalent attributes:
//ORIGINAL LINE: @RequiredArgsConstructor public enum Opcode
		public sealed class Opcode
		{
			public static readonly Opcode RETURN = new Opcode("RETURN", InnerEnum.RETURN, 0);
			public static readonly Opcode BOOSTED_SKILL_LEVELS = new Opcode("BOOSTED_SKILL_LEVELS", InnerEnum.BOOSTED_SKILL_LEVELS, 1);
			public static readonly Opcode REAL_SKILL_LEVELS = new Opcode("REAL_SKILL_LEVELS", InnerEnum.REAL_SKILL_LEVELS, 1);
			public static readonly Opcode SKILL_EXPERIENCE = new Opcode("SKILL_EXPERIENCE", InnerEnum.SKILL_EXPERIENCE, 1);
			public static readonly Opcode WIDGET_CONTAINS_ITEM_GET_QUANTITY = new Opcode("WIDGET_CONTAINS_ITEM_GET_QUANTITY", InnerEnum.WIDGET_CONTAINS_ITEM_GET_QUANTITY, 3);
			public static readonly Opcode VARP = new Opcode("VARP", InnerEnum.VARP, 1);
			public static readonly Opcode EXPERIENCE_AT_LEVEL_FOR_SKILL = new Opcode("EXPERIENCE_AT_LEVEL_FOR_SKILL", InnerEnum.EXPERIENCE_AT_LEVEL_FOR_SKILL, 1);
			public static readonly Opcode VARP_TIMES_469 = new Opcode("VARP_TIMES_469", InnerEnum.VARP_TIMES_469, 1);
			public static readonly Opcode COMBAT_LEVEL = new Opcode("COMBAT_LEVEL", InnerEnum.COMBAT_LEVEL, 1);
			public static readonly Opcode TOTAL_LEVEL = new Opcode("TOTAL_LEVEL", InnerEnum.TOTAL_LEVEL, 0);
			public static readonly Opcode WIDGET_CONTAINS_ITEM_STAR = new Opcode("WIDGET_CONTAINS_ITEM_STAR", InnerEnum.WIDGET_CONTAINS_ITEM_STAR, 3);
			public static readonly Opcode RUN_ENERGY = new Opcode("RUN_ENERGY", InnerEnum.RUN_ENERGY, 0);
			public static readonly Opcode WEIGHT = new Opcode("WEIGHT", InnerEnum.WEIGHT, 0);
			public static readonly Opcode VARP_TESTBIT = new Opcode("VARP_TESTBIT", InnerEnum.VARP_TESTBIT, 2);
			public static readonly Opcode VARBIT = new Opcode("VARBIT", InnerEnum.VARBIT, 1);
			public static readonly Opcode MINUS = new Opcode("MINUS", InnerEnum.MINUS, 0);
			public static readonly Opcode DIV = new Opcode("DIV", InnerEnum.DIV, 0);
			public static readonly Opcode MUL = new Opcode("MUL", InnerEnum.MUL, 0);
			public static readonly Opcode WORLD_X = new Opcode("WORLD_X", InnerEnum.WORLD_X, 0);
			public static readonly Opcode WORLD_Y = new Opcode("WORLD_Y", InnerEnum.WORLD_Y, 1);
			public static readonly Opcode CONSTANT = new Opcode("CONSTANT", InnerEnum.CONSTANT, 1);

			private static readonly List<Opcode> valueList = new List<Opcode>();

			static Opcode()
			{
				valueList.Add(RETURN);
				valueList.Add(BOOSTED_SKILL_LEVELS);
				valueList.Add(REAL_SKILL_LEVELS);
				valueList.Add(SKILL_EXPERIENCE);
				valueList.Add(WIDGET_CONTAINS_ITEM_GET_QUANTITY);
				valueList.Add(VARP);
				valueList.Add(EXPERIENCE_AT_LEVEL_FOR_SKILL);
				valueList.Add(VARP_TIMES_469);
				valueList.Add(COMBAT_LEVEL);
				valueList.Add(TOTAL_LEVEL);
				valueList.Add(WIDGET_CONTAINS_ITEM_STAR);
				valueList.Add(RUN_ENERGY);
				valueList.Add(WEIGHT);
				valueList.Add(VARP_TESTBIT);
				valueList.Add(VARBIT);
				valueList.Add(MINUS);
				valueList.Add(DIV);
				valueList.Add(MUL);
				valueList.Add(WORLD_X);
				valueList.Add(WORLD_Y);
				valueList.Add(CONSTANT);
			}

			public enum InnerEnum
			{
				RETURN,
				BOOSTED_SKILL_LEVELS,
				REAL_SKILL_LEVELS,
				SKILL_EXPERIENCE,
				WIDGET_CONTAINS_ITEM_GET_QUANTITY,
				VARP,
				EXPERIENCE_AT_LEVEL_FOR_SKILL,
				VARP_TIMES_469,
				COMBAT_LEVEL,
				TOTAL_LEVEL,
				WIDGET_CONTAINS_ITEM_STAR,
				RUN_ENERGY,
				WEIGHT,
				VARP_TESTBIT,
				VARBIT,
				MINUS,
				DIV,
				MUL,
				WORLD_X,
				WORLD_Y,
				CONSTANT
			}

			public readonly InnerEnum innerEnumValue;
			private readonly string nameValue;
			private readonly int ordinalValue;
			private static int nextOrdinal = 0;

			public readonly int argumentCount;

			public static Opcode[] values()
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

			public static Opcode valueOf(string name)
			{
				foreach (Opcode enumInstance in Opcode.valueList)
				{
					if (enumInstance.nameValue == name)
					{
						return enumInstance;
					}
				}
				throw new System.ArgumentException(name);
			}
		}

		public Opcode opcode;
		public int[] operands;
	}

}