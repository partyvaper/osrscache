#pragma once

#include "../../definitions/ScriptDefinition.h"
#include "../Instruction.h"
#include "../Instructions.h"
#include "../Opcodes.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <memory>
#include "../../../../../../../../tangible_stringbuilder.h"

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
namespace net::runelite::cache::script::disassembler
{

	using Escaper = com::google::common::escape::Escaper;
	using Escapers = com::google::common::escape::Escapers;
	using IOException = java::io::IOException;
	using ScriptDefinition = net::runelite::cache::definitions::ScriptDefinition;
	using Instructions = net::runelite::cache::script::Instructions;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;

	class Disassembler : public std::enable_shared_from_this<Disassembler>
	{
	private:
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		static const std::shared_ptr<Logger> logger;
		static const std::shared_ptr<Escaper> ESCAPER;

		const std::shared_ptr<Instructions> instructions = std::make_shared<Instructions>();

	public:
		Disassembler();

	private:
		bool isJump(int opcode);

		std::vector<bool> needLabel(std::shared_ptr<ScriptDefinition> script);

	public:
		virtual std::wstring disassemble(std::shared_ptr<ScriptDefinition> script);

	private:
		bool shouldWriteIntOperand(int opcode, int operand);

		void writerHeader(std::shared_ptr<StringBuilder> writer, std::shared_ptr<ScriptDefinition> script);
	};

}
