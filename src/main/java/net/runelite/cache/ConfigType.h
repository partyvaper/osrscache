#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <utility>

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

namespace net::runelite::cache
{

	enum class ConfigType
	{
		// types from https://github.com/im-frizzy/OpenRS/blob/master/source/net/openrs/cache/type/ConfigArchive.java
		UNDERLAY = 1,
		IDENTKIT = 3,
		OVERLAY = 4,
		INV = 5,
		OBJECT = 6,
		ENUM = 8,
		NPC = 9,
		ITEM = 10,
		PARAMS = 11,
		SEQUENCE = 12,
		SPOTANIM = 13,
		VARBIT = 14,
		VARCLIENT = 19,
		VARCLIENTSTRING = 15,
		VARPLAYER = 16,
		HITSPLAT = 32,
		HEALTHBAR = 33,
		STRUCT = 34,
		AREA = 35,
		DBROW = 38,
		DBTABLE = 39

//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//		private final int id;

//JAVA TO C++ CONVERTER TODO TASK: Enum methods are not converted by Java to C++ Converter:
//		ConfigType(int id)
	//	{
	//		this.id = id;
	//	}

//JAVA TO C++ CONVERTER TODO TASK: Enum methods are not converted by Java to C++ Converter:
//		public int getId()
	//	{
	//		return id;
	//	}
	};

	class ConfigTypeHelper
	{
	private:
		static std::vector<std::pair<ConfigType, std::wstring>> pairs()
		{
			return
			{
				{ConfigType::UNDERLAY, L"UNDERLAY"},
				{ConfigType::IDENTKIT, L"IDENTKIT"},
				{ConfigType::OVERLAY, L"OVERLAY"},
				{ConfigType::INV, L"INV"},
				{ConfigType::OBJECT, L"OBJECT"},
				{ConfigType::ENUM, L"ENUM"},
				{ConfigType::NPC, L"NPC"},
				{ConfigType::ITEM, L"ITEM"},
				{ConfigType::PARAMS, L"PARAMS"},
				{ConfigType::SEQUENCE, L"SEQUENCE"},
				{ConfigType::SPOTANIM, L"SPOTANIM"},
				{ConfigType::VARBIT, L"VARBIT"},
				{ConfigType::VARCLIENT, L"VARCLIENT"},
				{ConfigType::VARCLIENTSTRING, L"VARCLIENTSTRING"},
				{ConfigType::VARPLAYER, L"VARPLAYER"},
				{ConfigType::HITSPLAT, L"HITSPLAT"},
				{ConfigType::HEALTHBAR, L"HEALTHBAR"},
				{ConfigType::STRUCT, L"STRUCT"},
				{ConfigType::AREA, L"AREA"},
				{ConfigType::DBROW, L"DBROW"},
				{ConfigType::DBTABLE, L"DBTABLE"}
			};
		}

	public:
		static std::vector<ConfigType> values()
		{
			std::vector<ConfigType> temp;
			for (auto pair : pairs())
			{
				temp.push_back(pair.first);
			}
			return temp;
		}

		static std::wstring enumName(ConfigType value)
		{
			for (auto pair : pairs())
			{
				if (pair.first == value)
					return pair.second;
			}

			throw std::runtime_error("Enum not found.");
		}

		static int ordinal(ConfigType value)
		{
			std::vector<std::pair<ConfigType, std::wstring>> temp = pairs();
			for (std::size_t i = 0; i < temp.size(); i++)
			{
				if (temp[i].first == value)
					return i;
			}

			throw std::runtime_error("Enum not found.");
		}

		static ConfigType enumFromString(std::wstring value)
		{
			for (auto pair : pairs())
			{
				if (pair.second == value)
					return pair.first;
			}

			throw std::runtime_error("Enum not found.");
		}
	};


}
