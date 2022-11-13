#include "ScriptWriter.h"
#include "LookupCase.h"

namespace net::runelite::cache::script::assembler
{
	using ArrayList = java::util::ArrayList;
	using LinkedHashMap = java::util::LinkedHashMap;
	using List = java::util::List;
	using Map = java::util::Map;
	using Objects = java::util::Objects;
	using ScriptDefinition = net::runelite::cache::definitions::ScriptDefinition;
	using Instruction = net::runelite::cache::script::Instruction;
	using Instructions = net::runelite::cache::script::Instructions;
	using Opcodes = net::runelite::cache::script::Opcodes;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> ScriptWriter::logger = org::slf4j::LoggerFactory::getLogger(ScriptWriter::class);

	ScriptWriter::ScriptWriter(std::shared_ptr<Instructions> instructions, std::shared_ptr<LabelVisitor> labelVisitor) : instructions(instructions), labelVisitor(labelVisitor)
	{
	}

	void ScriptWriter::enterId_value(std::shared_ptr<rs2asmParser::Id_valueContext> ctx)
	{
		int value = static_cast<int>(ctx->getText());
		id = value;
	}

	void ScriptWriter::enterInt_stack_value(std::shared_ptr<rs2asmParser::Int_stack_valueContext> ctx)
	{
		int value = static_cast<int>(ctx->getText());
		intStackCount = value;
	}

	void ScriptWriter::enterString_stack_value(std::shared_ptr<rs2asmParser::String_stack_valueContext> ctx)
	{
		int value = static_cast<int>(ctx->getText());
		stringStackCount = value;
	}

	void ScriptWriter::enterInt_var_value(std::shared_ptr<rs2asmParser::Int_var_valueContext> ctx)
	{
		int value = static_cast<int>(ctx->getText());
		localIntCount = value;
	}

	void ScriptWriter::enterString_var_value(std::shared_ptr<rs2asmParser::String_var_valueContext> ctx)
	{
		int value = static_cast<int>(ctx->getText());
		localStringCount = value;
	}

	void ScriptWriter::exitInstruction(std::shared_ptr<rs2asmParser::InstructionContext> ctx)
	{
		++pos;
	}

	void ScriptWriter::enterName_string(std::shared_ptr<rs2asmParser::Name_stringContext> ctx)
	{
		std::wstring text = ctx->getText();
		std::shared_ptr<Instruction> i = instructions->find(text);
		if (i == nullptr)
		{
			logger->warn(L"Unknown instruction {}", text);
			throw std::runtime_error(StringHelper::wstring_to_string(L"Unknown instruction " + text));
		}

		int opcode = i->getOpcode();
		addOpcode(opcode);
	}

	void ScriptWriter::enterName_opcode(std::shared_ptr<rs2asmParser::Name_opcodeContext> ctx)
	{
		std::wstring text = ctx->getText();
		int opcode = std::stoi(text);
		addOpcode(opcode);
	}

	void ScriptWriter::addOpcode(int opcode)
	{
		assert(opcodes.size() == pos);
		assert(iops.size() == pos);
		assert(sops.size() == pos);
		assert(switches.size() == pos);

		opcodes.push_back(opcode);
		iops.push_back(nullptr);
		sops.push_back(L"");
		switches.push_back(nullptr);
	}

	void ScriptWriter::enterOperand_int(std::shared_ptr<rs2asmParser::Operand_intContext> ctx)
	{
		std::wstring text = ctx->getText();
		int value = std::stoi(text);
		iops[pos] = value;
	}

	void ScriptWriter::enterOperand_qstring(std::shared_ptr<rs2asmParser::Operand_qstringContext> ctx)
	{
		std::wstring text = ctx->getText();
		text = text.substr(1, (text.length() - 1) - 1);
		sops[pos] = text;
	}

	void ScriptWriter::enterOperand_label(std::shared_ptr<rs2asmParser::Operand_labelContext> ctx)
	{
		std::wstring text = ctx->getText();
		std::optional<int> instruction = labelVisitor->getInstructionForLabel(text);
		if (!instruction)
		{
			throw std::runtime_error(StringHelper::wstring_to_string(L"reference to unknown label " + text));
		}

		int target = instruction.value() - pos - 1; // -1 to go to the instruction prior
		iops[pos] = target;
	}

	void ScriptWriter::enterSwitch_lookup(std::shared_ptr<rs2asmParser::Switch_lookupContext> ctx)
	{
		if (switches[pos - 1] != nullptr)
		{
			return;
		}

		std::shared_ptr<LookupSwitch> ls = std::make_shared<LookupSwitch>();
		switches[pos - 1] = ls;
	}

	void ScriptWriter::exitSwitch_key(std::shared_ptr<rs2asmParser::Switch_keyContext> ctx)
	{
		std::wstring text = ctx->getText();
		int key = std::stoi(text);

		std::shared_ptr<LookupSwitch> ls = switches[pos - 1];
		assert(ls != nullptr);

		std::shared_ptr<LookupCase> scase = std::make_shared<LookupCase>();
		scase->setValue(key);

		ls->getCases().push_back(scase);
	}

	void ScriptWriter::exitSwitch_value(std::shared_ptr<rs2asmParser::Switch_valueContext> ctx)
	{
		std::wstring text = ctx->getText();
		std::optional<int> instruction = labelVisitor->getInstructionForLabel(text);
		if (!instruction)
		{
			throw std::runtime_error(StringHelper::wstring_to_string(L"reference to unknown label " + text));
		}

		int target = instruction.value() - (pos - 1) - 1; // to go to the instruction prior to target

		std::shared_ptr<LookupSwitch> ls = switches[pos - 1];
		assert(ls != nullptr);

		std::shared_ptr<LookupCase> scase = ls->getCases()[ls->getCases().size() - 1];
		scase->setOffset(target);
	}

	std::shared_ptr<ScriptDefinition> ScriptWriter::buildScript()
	{
		setSwitchOperands();

		std::shared_ptr<ScriptDefinition> script = std::make_shared<ScriptDefinition>();
		script->setId(id);
		script->setIntStackCount(intStackCount);
		script->setStringStackCount(stringStackCount);
		script->setLocalIntCount(localIntCount);
		script->setLocalStringCount(localStringCount);
		script->setInstructions(opcodes.stream().mapToInt(int::valueOf).toArray());
		script->setIntOperands(iops.stream().map([&] (std::any i)
		{
		return i == nullptr ? 0 : i;
		}).mapToInt(int::valueOf).toArray());
		script->setStringOperands(sops.toArray(std::vector<std::wstring>(0)));
		script->setSwitches(buildSwitches());
		return script;
	}

	void ScriptWriter::setSwitchOperands()
	{
		int count = 0;
		for (int i = 0; i < opcodes.size(); ++i)
		{
			if (opcodes[i] != Opcodes::SWITCH)
			{
				continue;
			}

			iops[i] = count++;
		}
	}

	std::vector<std::unordered_map<int, int>> ScriptWriter::buildSwitches()
	{
		int count = static_cast<int>(switches.stream().filter(Objects::nonNull).count());

		if (count == 0)
		{
			return std::vector<std::unordered_map<int, int>>();
		}

		int index = 0;
		std::vector<std::unordered_map<int, int>> maps = std::vector<std::unordered_map>(count);
		for (auto lswitch : switches)
		{
			if (lswitch == nullptr)
			{
				continue;
			}

			std::unordered_map<int, int> map = maps[index++] = std::make_shared<LinkedHashMap<int, int>>();

			for (auto scase : lswitch->getCases())
			{
				map.emplace(scase->getValue(), scase->getOffset());
			}
		}
		return maps;
	}
}
