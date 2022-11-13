#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <any>
#include <memory>

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
namespace net::runelite::cache::definitions
{

	using Map = java::util::Map;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Data public class ItemDefinition
	class ItemDefinition : public std::enable_shared_from_this<ItemDefinition>
	{
	public:
		const int id;

		std::wstring name = L"null";
		std::wstring unknown1;

		int resizeX = 128;
		int resizeY = 128;
		int resizeZ = 128;

		int xan2d = 0;
		int yan2d = 0;
		int zan2d = 0;

		int cost = 1;
		bool isTradeable = false;
		int stackable = 0;
		int inventoryModel = 0;

		int wearPos1 = 0;
		int wearPos2 = 0;
		int wearPos3 = 0;

		bool members = false;

		std::vector<short> colorFind;
		std::vector<short> colorReplace;
		std::vector<short> textureFind;
		std::vector<short> textureReplace;

		int zoom2d = 2000;
		int xOffset2d = 0;
		int yOffset2d = 0;

		int ambient = 0;
		int contrast = 0;

		std::vector<int> countCo;
		std::vector<int> countObj;

		std::vector<std::wstring> options = std::vector<std::wstring>{L"", L"", L"Take", L"", L""};

		std::vector<std::wstring> interfaceOptions = std::vector<std::wstring>{L"", L"", L"", L"", L"Drop"};

		int maleModel0 = -1;
		int maleModel1 = -1;
		int maleModel2 = -1;
		int maleOffset = 0;
		int maleHeadModel = -1;
		int maleHeadModel2 = -1;

		int femaleModel0 = -1;
		int femaleModel1 = -1;
		int femaleModel2 = -1;
		int femaleOffset = 0;
		int femaleHeadModel = -1;
		int femaleHeadModel2 = -1;

		int category = 0;

		int notedID = -1;
		int notedTemplate = -1;

		int team = 0;
		int weight = 0;

		int shiftClickDropIndex = -2;

		int boughtId = -1;
		int boughtTemplateId = -1;

		int placeholderId = -1;
		int placeholderTemplateId = -1;

		std::unordered_map<int, std::any> params;

		virtual void linkNote(std::shared_ptr<ItemDefinition> notedItem, std::shared_ptr<ItemDefinition> unnotedItem);

		virtual void linkBought(std::shared_ptr<ItemDefinition> var1, std::shared_ptr<ItemDefinition> var2);

		virtual void linkPlaceholder(std::shared_ptr<ItemDefinition> var1, std::shared_ptr<ItemDefinition> var2);
	};

}
