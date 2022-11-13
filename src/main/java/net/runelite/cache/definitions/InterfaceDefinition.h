#pragma once

#include "ClientScript1Instruction.h"
#include <string>
#include <vector>
#include <any>
#include <memory>

/*
 * Copyright (c) 2017, Adam <Adam@sigterm.info>
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
//ORIGINAL LINE: @Data public class InterfaceDefinition
	class InterfaceDefinition : public std::enable_shared_from_this<InterfaceDefinition>
	{
	public:
		int id = -1;
		bool isIf3 = false;
		int type = 0;
		int contentType = 0;
		int originalX = 0;
		int originalY = 0;
		int originalWidth = 0;
		int originalHeight = 0;
		int widthMode = 0;
		int heightMode = 0;
		int xPositionMode = 0;
		int yPositionMode = 0;
		int parentId = -1;
		bool isHidden = false;
		int scrollWidth = 0;
		int scrollHeight = 0;
		bool noClickThrough = false;
		int spriteId = -1;
		int textureId = 0;
		bool spriteTiling = false;
		int opacity = 0;
		int borderType = 0;
		int shadowColor = 0;
		bool flippedVertically = false;
		bool flippedHorizontally = false;
		int modelType = 1;
		int modelId = -1;
		int offsetX2d = 0;
		int offsetY2d = 0;
		int rotationX = 0;
		int rotationY = 0;
		int rotationZ = 0;
		int modelZoom = 100;
		int animation = -1;
		bool orthogonal = false;
		int modelHeightOverride = 0;
		int fontId = -1;
		std::wstring text = L"";
		int lineHeight = 0;
		int xTextAlignment = 0;
		int yTextAlignment = 0;
		bool textShadowed = false;
		int textColor = 0;
		bool filled = false;
		int lineWidth = 1;
		bool lineDirection = false;
		int clickMask = 0;
		std::wstring name = L"";
		std::vector<std::wstring> actions;
		int dragDeadZone = 0;
		int dragDeadTime = 0;
		bool dragRenderBehavior = false;
		std::wstring targetVerb = L"";
		std::vector<std::any> onLoadListener;
		std::vector<std::any> onMouseOverListener;
		std::vector<std::any> onMouseLeaveListener;
		std::vector<std::any> onTargetLeaveListener;
		std::vector<std::any> onTargetEnterListener;
		std::vector<std::any> onVarTransmitListener;
		std::vector<std::any> onInvTransmitListener;
		std::vector<std::any> onStatTransmitListener;
		std::vector<std::any> onTimerListener;
		std::vector<std::any> onOpListener;
		std::vector<std::any> onMouseRepeatListener;
		std::vector<std::any> onClickListener;
		std::vector<std::any> onClickRepeatListener;
		std::vector<std::any> onReleaseListener;
		std::vector<std::any> onHoldListener;
		std::vector<std::any> onDragListener;
		std::vector<std::any> onDragCompleteListener;
		std::vector<std::any> onScrollWheelListener;
		std::vector<int> varTransmitTriggers;
		std::vector<int> invTransmitTriggers;
		std::vector<int> statTransmitTriggers;
		bool hasListener = false;

		int menuType = 0;
		// This is set to a siblings' child id when that widget should get a hover effect when this one is hovered
		int hoveredSiblingId = 0;
		std::vector<int> alternateOperators;
		std::vector<int> alternateRhs;
		std::vector<std::vector<std::shared_ptr<ClientScript1Instruction>>> clientScripts;
		std::vector<int> itemIds;
		std::vector<int> itemQuantities;
		int xPitch = 0;
		int yPitch = 0;
		std::vector<int> xOffsets;
		std::vector<int> yOffsets;
		std::vector<int> sprites;
		std::vector<std::wstring> configActions;
		std::wstring alternateText = L"";
		int alternateTextColor = 0;
		int hoveredTextColor = 0;
		int alternateHoveredTextColor = 0;
		int alternateSpriteId = -1;
		int alternateModelId = -1;
		int alternateAnimation = -1;
		std::wstring spellName = L"";
		std::wstring tooltip = L"Ok";
	};

}
