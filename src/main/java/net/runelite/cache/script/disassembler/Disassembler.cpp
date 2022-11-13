#include "Disassembler.h"

namespace net::runelite::cache::script::disassembler
{
	using Escaper = com::google::common::escape::Escaper;
	using Escapers = com::google::common::escape::Escapers;
	using IOException = java::io::IOException;
	using Map = java::util::Map;
	using Entry = java::util::Map::Entry;
	using ScriptDefinition = net::runelite::cache::definitions::ScriptDefinition;
	using Instruction = net::runelite::cache::script::Instruction;
	using Instructions = net::runelite::cache::script::Instructions;
	using Opcodes = net::runelite::cache::script::Opcodes;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> Disassembler::logger = org::slf4j::LoggerFactory::getLogger(Disassembler::class);
const std::shared_ptr<com::google::common::escape::Escaper> Disassembler::ESCAPER = com::google::common::escape::Escapers::builder().addEscape(L'"', L"\\\"").addEscape(L'\\', L"\\\\").build();

	Disassembler::Disassembler()
	{
		instructions->init();
	}

	bool Disassembler::isJump(int opcode)
	{
		switch (opcode)
		{
			case Opcodes::JUMP:
			case Opcodes::IF_ICMPEQ:
			case Opcodes::IF_ICMPGE:
			case Opcodes::IF_ICMPGT:
			case Opcodes::IF_ICMPLE:
			case Opcodes::IF_ICMPLT:
			case Opcodes::IF_ICMPNE:
				return true;
			default:
				return false;
		}
	}

	std::vector<bool> Disassembler::needLabel(std::shared_ptr<ScriptDefinition> script)
	{
		std::vector<int> instructions = script->getInstructions();
		std::vector<int> iops = script->getIntOperands();
		std::vector<std::unordered_map<int, int>> switches = script->getSwitches();

		std::vector<bool> jumped(instructions.size());

		for (int i = 0; i < instructions.size(); ++i)
		{
			int opcode = instructions[i];
			int iop = iops[i];

			if (opcode == Opcodes::SWITCH)
			{
				std::unordered_map<int, int> switchMap = switches[iop];

				for (auto entry : switchMap)
				{
					int offset = entry.second;

					int to = i + offset + 1;
					assert(to >= 0 && to < instructions.size());
					jumped[to] = true;
				}
			}

			if (!isJump(opcode))
			{
				continue;
			}

			// + 1 because the jumps go to the instructions prior to the
			// one you really want, because the pc is incremented on the
			// next loop
			int to = i + iop + 1;
			assert(to >= 0 && to < instructions.size());

			jumped[to] = true;
		}

		return jumped;
	}

	std::wstring Disassembler::disassemble(std::shared_ptr<ScriptDefinition> script)
	{
		std::vector<int> instructions = script->getInstructions();
		std::vector<int> iops = script->getIntOperands();
		std::vector<std::wstring> sops = script->getStringOperands();
		std::vector<std::unordered_map<int, int>> switches = script->getSwitches();

		assert(iops.size() == instructions.size());
		assert(sops.size() == instructions.size());

		std::vector<bool> jumps = needLabel(script);

		std::shared_ptr<StringBuilder> writer = std::make_shared<StringBuilder>();
		writerHeader(writer, script);

		for (int i = 0; i < instructions.size(); ++i)
		{
			int opcode = instructions[i];
			int iop = iops[i];
			std::wstring sop = sops[i];

			std::shared_ptr<Instruction> ins = this->instructions->find(opcode);
			if (ins == nullptr)
			{
				logger->warn(L"Unknown instruction {} in script {}", opcode, script->getId());
			}

			if (jumps[i])
			{
				// something jumps here
				writer->append(L"LABEL")->append(i)->append(L":\n");
			}

			std::wstring name;
			if (ins != nullptr && ins->getName() != L"")
			{
				name = ins->getName();
			}
			else
			{
				name = String::format(L"%03d", opcode);
			}

			writer->append(String::format(L"   %-22s", name));

			if (shouldWriteIntOperand(opcode, iop))
			{
				if (isJump(opcode))
				{
					writer->append(L" LABEL")->append(i + iop + 1);
				}
				else
				{
					writer->append(L" ")->append(iop);
				}
			}

			if (sop != L"")
			{
				writer->append(L" \"")->append(ESCAPER->escape(sop))->append(L"\"");
			}

			if (opcode == Opcodes::SWITCH)
			{
				std::unordered_map<int, int> switchMap = switches[iop];

				for (auto entry : switchMap)
				{
					int value = entry.first;
					int jump = entry.second;

					writer->append(L"\n");
					writer->append(L"      ")->append(value)->append(L": LABEL")->append(i + jump + 1);
				}
			}

			writer->append(L"\n");
		}

		return writer->toString();
	}

	bool Disassembler::shouldWriteIntOperand(int opcode, int operand)
	{
		if (opcode == Opcodes::SWITCH)
		{
			// table follows instruction
			return false;
		}

		if (operand != 0)
		{
			// always write non-zero operand
			return true;
		}

		switch (opcode)
		{
			case Opcodes::ICONST:
			case Opcodes::ILOAD:
			case Opcodes::SLOAD:
			case Opcodes::ISTORE:
			case Opcodes::SSTORE:
				return true;
		}

		// int operand is not used, don't write it
		return false;
	}

	void Disassembler::writerHeader(std::shared_ptr<StringBuilder> writer, std::shared_ptr<ScriptDefinition> script)
	{
		int id = script->getId();
		int intStackCount = script->getIntStackCount();
		int stringStackCount = script->getStringStackCount();
		int localIntCount = script->getLocalIntCount();
		int localStringCount = script->getLocalStringCount();

		writer->append(L".id                 ")->append(id)->append(L'\n');
		writer->append(L".int_stack_count    ")->append(intStackCount)->append(L'\n');
		writer->append(L".string_stack_count ")->append(stringStackCount)->append(L'\n');
		writer->append(L".int_var_count      ")->append(localIntCount)->append(L'\n');
		writer->append(L".string_var_count   ")->append(localStringCount)->append(L'\n');
	}
}
