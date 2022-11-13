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
//ORIGINAL LINE: @Data public class ObjectDefinition
	class ObjectDefinition : public std::enable_shared_from_this<ObjectDefinition>
	{
	private:
		int id = 0;
		std::vector<short> retextureToFind;
		int decorDisplacement = 16;
		bool isHollow = false;
		std::wstring name = L"null";
		std::vector<int> objectModels;
		std::vector<int> objectTypes;
		std::vector<short> recolorToFind;
		int mapAreaId = -1;
		std::vector<short> textureToReplace;
		int sizeX = 1;
		int sizeY = 1;
		int anInt2083 = 0;
		std::vector<int> ambientSoundIds;
		int offsetX = 0;
		bool mergeNormals = false;
		int wallOrDoor = -1;
		int animationID = -1;
		int varbitID = -1;
		int ambient = 0;
		int contrast = 0;
		std::vector<std::wstring> actions = std::vector<std::wstring>(5);
		int interactType = 2;
		int mapSceneID = -1;
		int blockingMask = 0;
		std::vector<short> recolorToReplace;
		bool shadow = true;
		int modelSizeX = 128;
		int modelSizeHeight = 128;
		int modelSizeY = 128;
		int objectID = 0;
		int offsetHeight = 0;
		int offsetY = 0;
		bool obstructsGround = false;
		int contouredGround = -1;
		int supportsItems = -1;
		std::vector<int> configChangeDest;
		int category = 0;
		bool isRotated = false;
		int varpID = -1;
		int ambientSoundId = -1;
		bool aBool2111 = false;
		int anInt2112 = 0;
		int anInt2113 = 0;
		bool blocksProjectile = true;
		bool randomizeAnimStart = false;
		std::unordered_map<int, std::any> params;
	};

}
