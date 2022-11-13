#include "Instruction.h"

namespace net::runelite::cache::script
{

	Instruction::Instruction(int opcode) : opcode(opcode)
	{
	}

	int Instruction::getOpcode()
	{
		return opcode;
	}

	std::wstring Instruction::getName()
	{
		return name;
	}

	void Instruction::setName(const std::wstring &name)
	{
		this->name = name;
	}
}
