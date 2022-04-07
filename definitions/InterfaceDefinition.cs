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
namespace OSRSCache.definitions
{

//JAVA TO C# CONVERTER TODO TASK: Most Java annotations will not have direct .NET equivalent attributes:
//ORIGINAL LINE: @Data public class InterfaceDefinition
	public class InterfaceDefinition
	{
		public int id = -1;
		public bool isIf3 = false;
		public int type;
		public int contentType;
		public int originalX;
		public int originalY;
		public int originalWidth;
		public int originalHeight;
		public int widthMode;
		public int heightMode;
		public int xPositionMode;
		public int yPositionMode;
		public int parentId = -1;
		public bool isHidden;
		public int scrollWidth;
		public int scrollHeight;
		public bool noClickThrough;
		public int spriteId = -1;
		public int textureId;
		public bool spriteTiling;
		public int opacity;
		public int borderType;
		public int shadowColor;
		public bool flippedVertically;
		public bool flippedHorizontally;
		public int modelType = 1;
		public int modelId = -1;
		public int offsetX2d;
		public int offsetY2d;
		public int rotationX;
		public int rotationY;
		public int rotationZ;
		public int modelZoom = 100;
		public int animation = -1;
		public bool orthogonal;
		public int modelHeightOverride;
		public int fontId = -1;
		public string text = "";
		public int lineHeight;
		public int xTextAlignment;
		public int yTextAlignment;
		public bool textShadowed;
		public int textColor;
		public bool filled;
		public int lineWidth = 1;
		public bool lineDirection;
		public int clickMask;
		public string name = "";
		public string[] actions;
		public int dragDeadZone;
		public int dragDeadTime;
		public bool dragRenderBehavior;
		public string targetVerb = "";
		public object[] onLoadListener;
		public object[] onMouseOverListener;
		public object[] onMouseLeaveListener;
		public object[] onTargetLeaveListener;
		public object[] onTargetEnterListener;
		public object[] onVarTransmitListener;
		public object[] onInvTransmitListener;
		public object[] onStatTransmitListener;
		public object[] onTimerListener;
		public object[] onOpListener;
		public object[] onMouseRepeatListener;
		public object[] onClickListener;
		public object[] onClickRepeatListener;
		public object[] onReleaseListener;
		public object[] onHoldListener;
		public object[] onDragListener;
		public object[] onDragCompleteListener;
		public object[] onScrollWheelListener;
		public int[] varTransmitTriggers;
		public int[] invTransmitTriggers;
		public int[] statTransmitTriggers;
		public bool hasListener;

		public int menuType;
		// This is set to a siblings' child id when that widget should get a hover effect when this one is hovered
		public int hoveredSiblingId;
		public int[] alternateOperators;
		public int[] alternateRhs;
		public ClientScript1Instruction[][] clientScripts;
		public int[] itemIds;
		public int[] itemQuantities;
		public int xPitch;
		public int yPitch;
		public int[] xOffsets;
		public int[] yOffsets;
		public int[] sprites;
		public string[] configActions;
		public string alternateText = "";
		public int alternateTextColor;
		public int hoveredTextColor;
		public int alternateHoveredTextColor;
		public int alternateSpriteId = -1;
		public int alternateModelId = -1;
		public int alternateAnimation = -1;
		public string spellName = "";
		public string tooltip = "Ok";
	}

}