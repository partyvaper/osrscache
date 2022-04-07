using System.Collections.Generic;

namespace OSRSCache.definitions
{
	public class ClientScript1Instruction
	{
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

			public Opcode(string name, InnerEnum innerEnum, int argCount)
			{
				nameValue = name;
				innerEnumValue = innerEnum;
				argumentCount = argCount;
			}

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
			public readonly int argumentCount;
			private static int nextOrdinal = 0;

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