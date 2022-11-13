#include "InterfaceLoader.h"

namespace net::runelite::cache::definitions::loaders
{
	using ArrayList = java::util::ArrayList;
	using Arrays = java::util::Arrays;
	using List = java::util::List;
	using ClientScript1Instruction = net::runelite::cache::definitions::ClientScript1Instruction;
	using InterfaceDefinition = net::runelite::cache::definitions::InterfaceDefinition;
	using InputStream = net::runelite::cache::io::InputStream;

	std::shared_ptr<InterfaceDefinition> InterfaceLoader::load(int id, std::vector<signed char> &b)
	{
		std::shared_ptr<InterfaceDefinition> iface = std::make_shared<InterfaceDefinition>();
		iface->id = id;
		if (b[0] == -1)
		{
			decodeIf3(iface, std::make_shared<InputStream>(b));
		}
		else
		{
			decodeIf1(iface, std::make_shared<InputStream>(b));
		}

		return iface;
	}

	void InterfaceLoader::decodeIf1(std::shared_ptr<InterfaceDefinition> iface, std::shared_ptr<InputStream> var1)
	{
		iface->isIf3 = false;
		iface->type = var1->readUnsignedByte();
		iface->menuType = var1->readUnsignedByte();
		iface->contentType = var1->readUnsignedShort();
		iface->originalX = var1->readShort();
		iface->originalY = var1->readShort();
		iface->originalWidth = var1->readUnsignedShort();
		iface->originalHeight = var1->readUnsignedShort();
		iface->opacity = var1->readUnsignedByte();
		iface->parentId = var1->readUnsignedShort();
		if (iface->parentId == 0xFFFF)
		{
			iface->parentId = -1;
		}
		else
		{
			iface->parentId += iface->id & ~0xFFFF;
		}

		iface->hoveredSiblingId = var1->readUnsignedShort();
		if (iface->hoveredSiblingId == 0xFFFF)
		{
			iface->hoveredSiblingId = -1;
		}

		int var2 = var1->readUnsignedByte();
		int var3;
		if (var2 > 0)
		{
			iface->alternateOperators = std::vector<int>(var2);
			iface->alternateRhs = std::vector<int>(var2);

			for (var3 = 0; var3 < var2; ++var3)
			{
				iface->alternateOperators[var3] = var1->readUnsignedByte();
				iface->alternateRhs[var3] = var1->readUnsignedShort();
			}
		}

		var3 = var1->readUnsignedByte();
		int var4;
		int var5;
		int var6;
		if (var3 > 0)
		{
			iface->clientScripts = std::vector<std::vector<std::shared_ptr<ClientScript1Instruction>>>(var3);

			for (var4 = 0; var4 < var3; ++var4)
			{
				var5 = var1->readUnsignedShort();
				std::vector<int> bytecode(var5);

				for (var6 = 0; var6 < var5; ++var6)
				{
					bytecode[var6] = var1->readUnsignedShort();
					if (bytecode[var6] == 0xFFFF)
					{
						bytecode[var6] = -1;
					}

					std::vector<std::shared_ptr<ClientScript1Instruction>> instructions;
					for (int i = 0; i < bytecode.size();)
					{
						std::shared_ptr<ClientScript1Instruction> ins = std::make_shared<ClientScript1Instruction>();

						ins->opcode = ClientScript1Instruction::OpcodeHelper::values()[bytecode[i++]];

						int ac = ins->opcode.argumentCount;
						ins->operands = std::vector<int>(bytecode.cbegin() + i, bytecode.cbegin() + i + ac);

						instructions.push_back(ins);
						i += ac;
					}
					iface->clientScripts[var4] = instructions.toArray(std::vector<std::shared_ptr<ClientScript1Instruction>>(0));
				}
			}
		}

		if (iface->type == 0)
		{
			iface->scrollHeight = var1->readUnsignedShort();
			iface->isHidden = var1->readUnsignedByte() == 1;
		}

		if (iface->type == 1)
		{
			var1->readUnsignedShort();
			var1->readUnsignedByte();
		}

		if (iface->type == 2)
		{
			iface->itemIds = std::vector<int>(iface->originalWidth * iface->originalHeight);
			iface->itemQuantities = std::vector<int>(iface->originalHeight * iface->originalWidth);
			var4 = var1->readUnsignedByte();
			if (var4 == 1)
			{
				iface->clickMask |= 268435456;
			}

			var5 = var1->readUnsignedByte();
			if (var5 == 1)
			{
				iface->clickMask |= 1073741824;
			}

			var6 = var1->readUnsignedByte();
			if (var6 == 1)
			{
				iface->clickMask |= std::numeric_limits<int>::min();
			}

			int var7 = var1->readUnsignedByte();
			if (var7 == 1)
			{
				iface->clickMask |= 536870912;
			}

			iface->xPitch = var1->readUnsignedByte();
			iface->yPitch = var1->readUnsignedByte();
			iface->xOffsets = std::vector<int>(20);
			iface->yOffsets = std::vector<int>(20);
			iface->sprites = std::vector<int>(20);

			int var8;
			for (var8 = 0; var8 < 20; ++var8)
			{
				int var9 = var1->readUnsignedByte();
				if (var9 == 1)
				{
					iface->xOffsets[var8] = var1->readShort();
					iface->yOffsets[var8] = var1->readShort();
					iface->sprites[var8] = var1->readInt();
				}
				else
				{
					iface->sprites[var8] = -1;
				}
			}

			iface->configActions = std::vector<std::wstring>(5);

			for (var8 = 0; var8 < 5; ++var8)
			{
				std::wstring var11 = var1->readString();
				if (var11.length() > 0)
				{
					iface->configActions[var8] = var11;
					iface->clickMask |= 1 << var8 + 23;
				}
			}
		}

		if (iface->type == 3)
		{
			iface->filled = var1->readUnsignedByte() == 1;
		}

		if (iface->type == 4 || iface->type == 1)
		{
			iface->xTextAlignment = var1->readUnsignedByte();
			iface->yTextAlignment = var1->readUnsignedByte();
			iface->lineHeight = var1->readUnsignedByte();
			iface->fontId = var1->readUnsignedShort();
			if (iface->fontId == 0xFFFF)
			{
				iface->fontId = -1;
			}

			iface->textShadowed = var1->readUnsignedByte() == 1;
		}

		if (iface->type == 4)
		{
			iface->text = var1->readString();
			iface->alternateText = var1->readString();
		}

		if (iface->type == 1 || iface->type == 3 || iface->type == 4)
		{
			iface->textColor = var1->readInt();
		}

		if (iface->type == 3 || iface->type == 4)
		{
			iface->alternateTextColor = var1->readInt();
			iface->hoveredTextColor = var1->readInt();
			iface->alternateHoveredTextColor = var1->readInt();
		}

		if (iface->type == 5)
		{
			iface->spriteId = var1->readInt();
			iface->alternateSpriteId = var1->readInt();
		}

		if (iface->type == 6)
		{
			iface->modelType = 1;
			iface->modelId = var1->readUnsignedShort();
			if (iface->modelId == 0xFFFF)
			{
				iface->modelId = -1;
			}

			iface->alternateModelId = var1->readUnsignedShort();
			if (iface->alternateModelId == 0xFFFF)
			{
				iface->alternateModelId = -1;
			}

			iface->animation = var1->readUnsignedShort();
			if (iface->animation == 0xFFFF)
			{
				iface->animation = -1;
			}

			iface->alternateAnimation = var1->readUnsignedShort();
			if (iface->alternateAnimation == 0xFFFF)
			{
				iface->alternateAnimation = -1;
			}

			iface->modelZoom = var1->readUnsignedShort();
			iface->rotationX = var1->readUnsignedShort();
			iface->rotationZ = var1->readUnsignedShort();
		}

		if (iface->type == 7)
		{
			iface->itemIds = std::vector<int>(iface->originalWidth * iface->originalHeight);
			iface->itemQuantities = std::vector<int>(iface->originalWidth * iface->originalHeight);
			iface->xTextAlignment = var1->readUnsignedByte();
			iface->fontId = var1->readUnsignedShort();
			if (iface->fontId == 0xFFFF)
			{
				iface->fontId = -1;
			}

			iface->textShadowed = var1->readUnsignedByte() == 1;
			iface->textColor = var1->readInt();
			iface->xPitch = var1->readShort();
			iface->yPitch = var1->readShort();
			var4 = var1->readUnsignedByte();
			if (var4 == 1)
			{
				iface->clickMask |= 1073741824;
			}

			iface->configActions = std::vector<std::wstring>(5);

			for (var5 = 0; var5 < 5; ++var5)
			{
				std::wstring var10 = var1->readString();
				if (var10.length() > 0)
				{
					iface->configActions[var5] = var10;
					iface->clickMask |= 1 << var5 + 23;
				}
			}
		}

		if (iface->type == 8)
		{
			iface->text = var1->readString();
		}

		if (iface->menuType == 2 || iface->type == 2)
		{
			iface->targetVerb = var1->readString();
			iface->spellName = var1->readString();
			var4 = var1->readUnsignedShort() & 63;
			iface->clickMask |= var4 << 11;
		}

		if (iface->menuType == 1 || iface->menuType == 4 || iface->menuType == 5 || iface->menuType == 6)
		{
			iface->tooltip = var1->readString();
			if (iface->tooltip.length() == 0)
			{
				if (iface->menuType == 1)
				{
					iface->tooltip = L"Ok";
				}

				if (iface->menuType == 4)
				{
					iface->tooltip = L"Select";
				}

				if (iface->menuType == 5)
				{
					iface->tooltip = L"Select";
				}

				if (iface->menuType == 6)
				{
					iface->tooltip = L"Continue";
				}
			}
		}

		if (iface->menuType == 1 || iface->menuType == 4 || iface->menuType == 5)
		{
			iface->clickMask |= 4194304;
		}

		if (iface->menuType == 6)
		{
			iface->clickMask |= 1;
		}

	}

	void InterfaceLoader::decodeIf3(std::shared_ptr<InterfaceDefinition> iface, std::shared_ptr<InputStream> var1)
	{
		var1->readUnsignedByte();
		iface->isIf3 = true;
		iface->type = var1->readUnsignedByte();
		iface->contentType = var1->readUnsignedShort();
		iface->originalX = var1->readShort();
		iface->originalY = var1->readShort();
		iface->originalWidth = var1->readUnsignedShort();
		if (iface->type == 9)
		{
			iface->originalHeight = var1->readShort();
		}
		else
		{
			iface->originalHeight = var1->readUnsignedShort();
		}

		iface->widthMode = var1->readByte();
		iface->heightMode = var1->readByte();
		iface->xPositionMode = var1->readByte();
		iface->yPositionMode = var1->readByte();
		iface->parentId = var1->readUnsignedShort();
		if (iface->parentId == 0xFFFF)
		{
			iface->parentId = -1;
		}
		else
		{
			iface->parentId += iface->id & ~0xFFFF;
		}

		iface->isHidden = var1->readUnsignedByte() == 1;
		if (iface->type == 0)
		{
			iface->scrollWidth = var1->readUnsignedShort();
			iface->scrollHeight = var1->readUnsignedShort();
			iface->noClickThrough = var1->readUnsignedByte() == 1;
		}

		if (iface->type == 5)
		{
			iface->spriteId = var1->readInt();
			iface->textureId = var1->readUnsignedShort();
			iface->spriteTiling = var1->readUnsignedByte() == 1;
			iface->opacity = var1->readUnsignedByte();
			iface->borderType = var1->readUnsignedByte();
			iface->shadowColor = var1->readInt();
			iface->flippedVertically = var1->readUnsignedByte() == 1;
			iface->flippedHorizontally = var1->readUnsignedByte() == 1;
		}

		if (iface->type == 6)
		{
			iface->modelType = 1;
			iface->modelId = var1->readUnsignedShort();
			if (iface->modelId == 0xFFFF)
			{
				iface->modelId = -1;
			}

			iface->offsetX2d = var1->readShort();
			iface->offsetY2d = var1->readShort();
			iface->rotationX = var1->readUnsignedShort();
			iface->rotationZ = var1->readUnsignedShort();
			iface->rotationY = var1->readUnsignedShort();
			iface->modelZoom = var1->readUnsignedShort();
			iface->animation = var1->readUnsignedShort();
			if (iface->animation == 0xFFFF)
			{
				iface->animation = -1;
			}

			iface->orthogonal = var1->readUnsignedByte() == 1;
			var1->readUnsignedShort();
			if (iface->widthMode != 0)
			{
				iface->modelHeightOverride = var1->readUnsignedShort();
			}

			if (iface->heightMode != 0)
			{
				var1->readUnsignedShort();
			}
		}

		if (iface->type == 4)
		{
			iface->fontId = var1->readUnsignedShort();
			if (iface->fontId == 0xFFFF)
			{
				iface->fontId = -1;
			}

			iface->text = var1->readString();
			iface->lineHeight = var1->readUnsignedByte();
			iface->xTextAlignment = var1->readUnsignedByte();
			iface->yTextAlignment = var1->readUnsignedByte();
			iface->textShadowed = var1->readUnsignedByte() == 1;
			iface->textColor = var1->readInt();
		}

		if (iface->type == 3)
		{
			iface->textColor = var1->readInt();
			iface->filled = var1->readUnsignedByte() == 1;
			iface->opacity = var1->readUnsignedByte();
		}

		if (iface->type == 9)
		{
			iface->lineWidth = var1->readUnsignedByte();
			iface->textColor = var1->readInt();
			iface->lineDirection = var1->readUnsignedByte() == 1;
		}

		iface->clickMask = var1->read24BitInt();
		iface->name = var1->readString();
		int var2 = var1->readUnsignedByte();
		if (var2 > 0)
		{
			iface->actions = std::vector<std::wstring>(var2);

			for (int var3 = 0; var3 < var2; ++var3)
			{
				iface->actions[var3] = var1->readString();
			}
		}

		iface->dragDeadZone = var1->readUnsignedByte();
		iface->dragDeadTime = var1->readUnsignedByte();
		iface->dragRenderBehavior = var1->readUnsignedByte() == 1;
		iface->targetVerb = var1->readString();
		iface->onLoadListener = this->decodeListener(iface, var1);
		iface->onMouseOverListener = this->decodeListener(iface, var1);
		iface->onMouseLeaveListener = this->decodeListener(iface, var1);
		iface->onTargetLeaveListener = this->decodeListener(iface, var1);
		iface->onTargetEnterListener = this->decodeListener(iface, var1);
		iface->onVarTransmitListener = this->decodeListener(iface, var1);
		iface->onInvTransmitListener = this->decodeListener(iface, var1);
		iface->onStatTransmitListener = this->decodeListener(iface, var1);
		iface->onTimerListener = this->decodeListener(iface, var1);
		iface->onOpListener = this->decodeListener(iface, var1);
		iface->onMouseRepeatListener = this->decodeListener(iface, var1);
		iface->onClickListener = this->decodeListener(iface, var1);
		iface->onClickRepeatListener = this->decodeListener(iface, var1);
		iface->onReleaseListener = this->decodeListener(iface, var1);
		iface->onHoldListener = this->decodeListener(iface, var1);
		iface->onDragListener = this->decodeListener(iface, var1);
		iface->onDragCompleteListener = this->decodeListener(iface, var1);
		iface->onScrollWheelListener = this->decodeListener(iface, var1);
		iface->varTransmitTriggers = this->decodeTriggers(var1);
		iface->invTransmitTriggers = this->decodeTriggers(var1);
		iface->statTransmitTriggers = this->decodeTriggers(var1);
	}

	std::vector<std::any> InterfaceLoader::decodeListener(std::shared_ptr<InterfaceDefinition> iface, std::shared_ptr<InputStream> var1)
	{
		int var2 = var1->readUnsignedByte();
		if (var2 == 0)
		{
			return std::vector<std::any>();
		}
		else
		{
			std::vector<std::any> var3(var2);

			for (int var4 = 0; var4 < var2; ++var4)
			{
				int var5 = var1->readUnsignedByte();
				if (var5 == 0)
				{
					var3[var4] = std::optional<int>(var1->readInt());
				}
				else if (var5 == 1)
				{
					var3[var4] = var1->readString();
				}
			}

			iface->hasListener = true;
			return var3;
		}
	}

	std::vector<int> InterfaceLoader::decodeTriggers(std::shared_ptr<InputStream> var1)
	{
		int var2 = var1->readUnsignedByte();
		if (var2 == 0)
		{
			return std::vector<int>();
		}
		else
		{
			std::vector<int> var3(var2);

			for (int var4 = 0; var4 < var2; ++var4)
			{
				var3[var4] = var1->readInt();
			}

			return var3;
		}
	}
}
