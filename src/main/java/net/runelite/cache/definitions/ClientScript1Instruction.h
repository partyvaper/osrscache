#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <utility>
#include <memory>

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
namespace net::runelite::cache::definitions
{


//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Data public class ClientScript1Instruction
	class ClientScript1Instruction : public std::enable_shared_from_this<ClientScript1Instruction>
	{
	public:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @RequiredArgsConstructor public enum Opcode
		enum class Opcode
		{
			RETURN = 0,
			BOOSTED_SKILL_LEVELS = 1,
			REAL_SKILL_LEVELS = 1,
			SKILL_EXPERIENCE = 1,
			WIDGET_CONTAINS_ITEM_GET_QUANTITY = 3,
			VARP = 1,
			EXPERIENCE_AT_LEVEL_FOR_SKILL = 1,
			VARP_TIMES_469 = 1,
			COMBAT_LEVEL = 1,
			TOTAL_LEVEL = 0,
			WIDGET_CONTAINS_ITEM_STAR = 3,
			RUN_ENERGY = 0,
			WEIGHT = 0,
			VARP_TESTBIT = 2,
			VARBIT = 1,
			MINUS = 0,
			DIV = 0,
			MUL = 0,
			WORLD_X = 0,
			WORLD_Y = 1,
			CONSTANT = 1

//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//			public final int argumentCount;
		};

		class OpcodeHelper
		{
		private:
			static std::vector<std::pair<Opcode, std::wstring>> pairs()
			{
				return
				{
					{Opcode::RETURN, L"RETURN"},
					{Opcode::BOOSTED_SKILL_LEVELS, L"BOOSTED_SKILL_LEVELS"},
					{Opcode::REAL_SKILL_LEVELS, L"REAL_SKILL_LEVELS"},
					{Opcode::SKILL_EXPERIENCE, L"SKILL_EXPERIENCE"},
					{Opcode::WIDGET_CONTAINS_ITEM_GET_QUANTITY, L"WIDGET_CONTAINS_ITEM_GET_QUANTITY"},
					{Opcode::VARP, L"VARP"},
					{Opcode::EXPERIENCE_AT_LEVEL_FOR_SKILL, L"EXPERIENCE_AT_LEVEL_FOR_SKILL"},
					{Opcode::VARP_TIMES_469, L"VARP_TIMES_469"},
					{Opcode::COMBAT_LEVEL, L"COMBAT_LEVEL"},
					{Opcode::TOTAL_LEVEL, L"TOTAL_LEVEL"},
					{Opcode::WIDGET_CONTAINS_ITEM_STAR, L"WIDGET_CONTAINS_ITEM_STAR"},
					{Opcode::RUN_ENERGY, L"RUN_ENERGY"},
					{Opcode::WEIGHT, L"WEIGHT"},
					{Opcode::VARP_TESTBIT, L"VARP_TESTBIT"},
					{Opcode::VARBIT, L"VARBIT"},
					{Opcode::MINUS, L"MINUS"},
					{Opcode::DIV, L"DIV"},
					{Opcode::MUL, L"MUL"},
					{Opcode::WORLD_X, L"WORLD_X"},
					{Opcode::WORLD_Y, L"WORLD_Y"},
					{Opcode::CONSTANT, L"CONSTANT"}
				};
			}

		public:
			static std::vector<Opcode> values()
			{
				std::vector<Opcode> temp;
				for (auto pair : pairs())
				{
					temp.push_back(pair.first);
				}
				return temp;
			}

			static std::wstring enumName(Opcode value)
			{
				for (auto pair : pairs())
				{
					if (pair.first == value)
						return pair.second;
				}

				throw std::runtime_error("Enum not found.");
			}

			static int ordinal(Opcode value)
			{
				std::vector<std::pair<Opcode, std::wstring>> temp = pairs();
				for (std::size_t i = 0; i < temp.size(); i++)
				{
					if (temp[i].first == value)
						return i;
				}

				throw std::runtime_error("Enum not found.");
			}

			static Opcode enumFromString(std::wstring value)
			{
				for (auto pair : pairs())
				{
					if (pair.second == value)
						return pair.first;
				}

				throw std::runtime_error("Enum not found.");
			}
		};


	public:
		Opcode opcode = static_cast<Opcode>(0);
		std::vector<int> operands;
	};

}
