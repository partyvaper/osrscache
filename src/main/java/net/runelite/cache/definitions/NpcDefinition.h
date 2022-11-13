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
//ORIGINAL LINE: @Data public class NpcDefinition
	class NpcDefinition : public std::enable_shared_from_this<NpcDefinition>
	{
	public:
		const int id;
		std::wstring name = L"null";
		int size = 1;
		std::vector<int> models;
		std::vector<int> chatheadModels;
		int standingAnimation = -1;
		int idleRotateLeftAnimation = -1;
		int idleRotateRightAnimation = -1;
		int walkingAnimation = -1;
		int rotate180Animation = -1;
		int rotateLeftAnimation = -1;
		int rotateRightAnimation = -1;
		int runAnimation = -1;
		int runRotate180Animation = -1;
		int runRotateLeftAnimation = -1;
		int runRotateRightAnimation = -1;
		int crawlAnimation = -1;
		int crawlRotate180Animation = -1;
		int crawlRotateLeftAnimation = -1;
		int crawlRotateRightAnimation = -1;
		std::vector<short> recolorToFind;
		std::vector<short> recolorToReplace;
		std::vector<short> retextureToFind;
		std::vector<short> retextureToReplace;
		std::vector<std::wstring> actions = std::vector<std::wstring>(5);
		bool isMinimapVisible = true;
		int combatLevel = -1;
		int widthScale = 128;
		int heightScale = 128;
		bool hasRenderPriority = false;
		int ambient = 0;
		int contrast = 0;
		int headIcon = -1;
		int rotationSpeed = 32;
		std::vector<int> configs;
		int varbitId = -1;
		int varpIndex = -1;
		bool isInteractable = true;
		bool rotationFlag = true;
		bool isPet = false;
		std::unordered_map<int, std::any> params;
		int category = 0;
	};

}
