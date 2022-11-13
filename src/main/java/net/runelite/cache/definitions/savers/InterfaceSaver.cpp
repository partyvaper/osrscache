#include "InterfaceSaver.h"

namespace net::runelite::cache::definitions::savers
{
	using ClientScript1Instruction = net::runelite::cache::definitions::ClientScript1Instruction;
	using InterfaceDefinition = net::runelite::cache::definitions::InterfaceDefinition;
	using OutputStream = net::runelite::cache::io::OutputStream;

	std::vector<signed char> InterfaceSaver::save(std::shared_ptr<InterfaceDefinition> def)
	{
		if (def->isIf3)
		{
			return saveIf3(def);
		}
		else
		{
			return saveIf1(def);
		}
	}

	std::vector<signed char> InterfaceSaver::saveIf3(std::shared_ptr<InterfaceDefinition> def)
	{
		throw UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
	}

	std::vector<signed char> InterfaceSaver::saveIf1(std::shared_ptr<InterfaceDefinition> def)
	{
		std::shared_ptr<OutputStream> out = std::make_shared<OutputStream>();
		out->writeByte(def->type);
		out->writeByte(def->menuType);
		out->writeShort(def->contentType);
		out->writeShort(def->originalX);
		out->writeShort(def->originalY);
		out->writeShort(def->originalWidth);
		out->writeShort(def->originalHeight);
		out->writeByte(def->opacity);
		out->writeShort(def->parentId);
		out->writeShort(def->hoveredSiblingId);
		if (!def->alternateOperators.empty())
		{
			out->writeByte(def->alternateOperators.size());
			for (int i = 0; i < def->alternateOperators.size(); ++i)
			{
				out->writeByte(def->alternateOperators[i]);
				out->writeShort(def->alternateRhs[i]);
			}
		}
		else
		{
			out->writeByte(0);
		}
		if (!def->clientScripts.empty())
		{
			out->writeByte(def->clientScripts.size());
			for (int i = 0; i < def->clientScripts.size(); ++i)
			{
				int len = 0;
				for (int j = 0; j < def->clientScripts[i].length; ++j)
				{
					std::shared_ptr<ClientScript1Instruction> ins = def->clientScripts[i][j];
					len++;
					if (!ins->operands.empty())
					{
						len += ins->operands.size();
					}
				}
				out->writeShort(len);
				for (int j = 0; j < def->clientScripts[i].length; ++j)
				{
					std::shared_ptr<ClientScript1Instruction> ins = def->clientScripts[i][j];
					out->writeShort(ClientScript1Instruction::OpcodeHelper::ordinal(ins->opcode));
					if (!ins->operands.empty())
					{
						for (auto op : ins->operands)
						{
							out->writeShort(op);
						}
					}
				}
			}
		}
		else
		{
			out->writeByte(0);
		}
		if (def->type == 0)
		{
			out->writeShort(def->scrollHeight);
			out->writeByte(def->isHidden ? 1 : 0);
		}
		if (def->type == 1)
		{
			out->writeShort(0);
			out->writeByte(0);
		}
		if (def->type == 2)
		{
			out->writeByte((def->clickMask & 268435456) != 0 ? 1 : 0);
			out->writeByte((def->clickMask & 1073741824) != 0 ? 1 : 0);
			out->writeByte((def->clickMask & std::numeric_limits<int>::min()) != 0 ? 1 : 0);
			out->writeByte((def->clickMask & 536870912) != 0 ? 1 : 0);
			out->writeByte(def->xPitch);
			out->writeByte(def->yPitch);
			for (int i = 0; i < 20; ++i)
			{
				if (def->sprites[i] != -1)
				{
					out->writeByte(1);
					out->writeShort(def->xOffsets[i]);
					out->writeShort(def->yOffsets[i]);
					out->writeShort(def->sprites[i]);
				}
				else
				{
					out->writeByte(0);
				}
			}
			for (int i = 0; i < 5; ++i)
			{
				if (def->configActions[i] != L"")
				{
					out->writeString(def->configActions[i]);
				}
				else
				{
					out->writeString(L"");
				}
			}
		}
		if (def->type == 3)
		{
			out->writeByte(def->filled ? 1 : 0);
		}
		if (def->type == 4 || def->type == 1)
		{
			out->writeByte(def->xTextAlignment);
			out->writeByte(def->yTextAlignment);
			out->writeByte(def->lineHeight);
			out->writeShort(def->fontId);
			out->writeByte(def->textShadowed ? 1 : 0);
		}
		if (def->type == 4)
		{
			out->writeString(def->text);
			out->writeString(def->alternateText);
		}
		if (def->type == 1 || def->type == 3 || def->type == 4)
		{
			out->writeInt(def->textColor);
		}
		if (def->type == 3 || def->type == 4)
		{
			out->writeInt(def->alternateTextColor);
			out->writeInt(def->hoveredTextColor);
			out->writeInt(def->alternateHoveredTextColor);
		}
		if (def->type == 5)
		{
			out->writeInt(def->spriteId);
			out->writeInt(def->alternateSpriteId);
		}
		if (def->type == 6)
		{
			out->writeShort(def->modelId);
			out->writeShort(def->alternateModelId);
			out->writeShort(def->animation);
			out->writeShort(def->alternateAnimation);
			out->writeShort(def->modelZoom);
			out->writeShort(def->rotationX);
			out->writeShort(def->rotationZ);
		}
		if (def->type == 7)
		{
			out->writeByte(def->xTextAlignment);
			out->writeShort(def->fontId);
			out->writeByte(def->textShadowed ? 1 : 0);
			out->writeInt(def->textColor);
			out->writeShort(def->xPitch);
			out->writeShort(def->yPitch);
			out->writeByte((def->clickMask & 1073741824) != 0 ? 1 : 0);
			for (int i = 0; i < 5; ++i)
			{
				out->writeString(def->configActions[i]);
			}
		}
		if (def->type == 8)
		{
			out->writeString(def->text);
		}
		if (def->menuType == 2 || def->type == 2)
		{
			out->writeString(def->targetVerb);
			out->writeString(def->spellName);
			out->writeShort((static_cast<int>(static_cast<unsigned int>(def->clickMask) >> 11)) & 63);
		}
		if (def->menuType == 1 || def->menuType == 4 || def->menuType == 5 || def->menuType == 6)
		{
			out->writeString(def->tooltip);
		}
		return out->flip();
	}
}
