#pragma once

#include "../../definitions/ScriptDefinition.h"
#include "../Instruction.h"
#include "../Instructions.h"
#include "../Opcodes.h"
#include "LabelVisitor.h"
#include "LookupSwitch.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <optional>
#include <cassert>
#include <memory>
#include "../../../../../../../../tangible_string_helper.h"

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
namespace net::runelite::cache::script::assembler
{

	using ArrayList = java::util::ArrayList;
	using List = java::util::List;
	using Map = java::util::Map;
	using ScriptDefinition = net::runelite::cache::definitions::ScriptDefinition;
	using Instructions = net::runelite::cache::script::Instructions;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;

	class ScriptWriter : public rs2asmBaseListener
	{
	private:
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		static const std::shared_ptr<Logger> logger;

		const std::shared_ptr<Instructions> instructions;
		const std::shared_ptr<LabelVisitor> labelVisitor;

		int id = 0;
		int pos = 0;
		int intStackCount = 0;
		int stringStackCount = 0;
		int localIntCount = 0;
		int localStringCount = 0;
		std::vector<int> opcodes = std::vector<int>();
		std::vector<int> iops = std::vector<int>();
		std::vector<std::wstring> sops = std::vector<std::wstring>();
		std::vector<std::shared_ptr<LookupSwitch>> switches = std::vector<std::shared_ptr<LookupSwitch>>();

	public:
		ScriptWriter(std::shared_ptr<Instructions> instructions, std::shared_ptr<LabelVisitor> labelVisitor);

		void enterId_value(std::shared_ptr<rs2asmParser::Id_valueContext> ctx) override;

		void enterInt_stack_value(std::shared_ptr<rs2asmParser::Int_stack_valueContext> ctx) override;

		void enterString_stack_value(std::shared_ptr<rs2asmParser::String_stack_valueContext> ctx) override;

		void enterInt_var_value(std::shared_ptr<rs2asmParser::Int_var_valueContext> ctx) override;

		void enterString_var_value(std::shared_ptr<rs2asmParser::String_var_valueContext> ctx) override;

		void exitInstruction(std::shared_ptr<rs2asmParser::InstructionContext> ctx) override;

		void enterName_string(std::shared_ptr<rs2asmParser::Name_stringContext> ctx) override;

		void enterName_opcode(std::shared_ptr<rs2asmParser::Name_opcodeContext> ctx) override;

	private:
		void addOpcode(int opcode);

	public:
		void enterOperand_int(std::shared_ptr<rs2asmParser::Operand_intContext> ctx) override;

		void enterOperand_qstring(std::shared_ptr<rs2asmParser::Operand_qstringContext> ctx) override;

		void enterOperand_label(std::shared_ptr<rs2asmParser::Operand_labelContext> ctx) override;

		void enterSwitch_lookup(std::shared_ptr<rs2asmParser::Switch_lookupContext> ctx) override;

		void exitSwitch_key(std::shared_ptr<rs2asmParser::Switch_keyContext> ctx) override;

		void exitSwitch_value(std::shared_ptr<rs2asmParser::Switch_valueContext> ctx) override;

		virtual std::shared_ptr<ScriptDefinition> buildScript();

	private:
		void setSwitchOperands();

		std::vector<std::unordered_map<int, int>> buildSwitches();

	protected:
		std::shared_ptr<ScriptWriter> shared_from_this()
		{
			return std::static_pointer_cast<ScriptWriter>(rs2asmBaseListener::shared_from_this());
		}
	};

}
