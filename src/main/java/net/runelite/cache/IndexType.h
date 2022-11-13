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

	enum class IndexType
	{
		ANIMATIONS = 0,
		SKELETONS = 1,
		CONFIGS = 2,
		INTERFACES = 3,
		SOUNDEFFECTS = 4,
		MAPS = 5,
		MUSIC_TRACKS = 6,
		MODELS = 7,
		SPRITES = 8,
		TEXTURES = 9,
		BINARY = 10,
		MUSIC_JINGLES = 11,
		CLIENTSCRIPT = 12,
		FONTS = 13,
		MUSIC_SAMPLES = 14,
		MUSIC_PATCHES = 15,
		WORLDMAP_OLD = 16, // looks unused
		WORLDMAP_GEOGRAPHY = 18,
		WORLDMAP = 19,
		WORLDMAP_GROUND = 20,
		DBTABLEINDEX = 21

//JAVA TO C++ CONVERTER TODO TASK: Enum fields are not converted by Java to C++ Converter:
//		private int id;

//JAVA TO C++ CONVERTER TODO TASK: Enum methods are not converted by Java to C++ Converter:
//		IndexType(int id)
	//	{
	//		this.id = id;
	//	}

//JAVA TO C++ CONVERTER TODO TASK: Enum methods are not converted by Java to C++ Converter:
//		public int getNumber()
	//	{
	//		return id;
	//	}
	};

	class IndexTypeHelper
	{
	private:
		static std::vector<std::pair<IndexType, std::wstring>> pairs()
		{
			return
			{
				{IndexType::ANIMATIONS, L"ANIMATIONS"},
				{IndexType::SKELETONS, L"SKELETONS"},
				{IndexType::CONFIGS, L"CONFIGS"},
				{IndexType::INTERFACES, L"INTERFACES"},
				{IndexType::SOUNDEFFECTS, L"SOUNDEFFECTS"},
				{IndexType::MAPS, L"MAPS"},
				{IndexType::MUSIC_TRACKS, L"MUSIC_TRACKS"},
				{IndexType::MODELS, L"MODELS"},
				{IndexType::SPRITES, L"SPRITES"},
				{IndexType::TEXTURES, L"TEXTURES"},
				{IndexType::BINARY, L"BINARY"},
				{IndexType::MUSIC_JINGLES, L"MUSIC_JINGLES"},
				{IndexType::CLIENTSCRIPT, L"CLIENTSCRIPT"},
				{IndexType::FONTS, L"FONTS"},
				{IndexType::MUSIC_SAMPLES, L"MUSIC_SAMPLES"},
				{IndexType::MUSIC_PATCHES, L"MUSIC_PATCHES"},
				{IndexType::WORLDMAP_OLD, L"WORLDMAP_OLD"},
				{IndexType::WORLDMAP_GEOGRAPHY, L"WORLDMAP_GEOGRAPHY"},
				{IndexType::WORLDMAP, L"WORLDMAP"},
				{IndexType::WORLDMAP_GROUND, L"WORLDMAP_GROUND"},
				{IndexType::DBTABLEINDEX, L"DBTABLEINDEX"}
			};
		}

	public:
		static std::vector<IndexType> values()
		{
			std::vector<IndexType> temp;
			for (auto pair : pairs())
			{
				temp.push_back(pair.first);
			}
			return temp;
		}

		static std::wstring enumName(IndexType value)
		{
			for (auto pair : pairs())
			{
				if (pair.first == value)
					return pair.second;
			}

			throw std::runtime_error("Enum not found.");
		}

		static int ordinal(IndexType value)
		{
			std::vector<std::pair<IndexType, std::wstring>> temp = pairs();
			for (std::size_t i = 0; i < temp.size(); i++)
			{
				if (temp[i].first == value)
					return i;
			}

			throw std::runtime_error("Enum not found.");
		}

		static IndexType enumFromString(std::wstring value)
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
