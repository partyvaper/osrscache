#pragma once

#include "Opcodes.h"
#include "Instruction.h"
#include <string>
#include <unordered_map>
#include <cassert>
#include <memory>

/*
 * Copyright (c) 2017, Adam <Adam@sigterm.info>
 * Copyright (c) 2018-2019, Hunter WB <hunterwb.com>
 * Copyright (c) 2019, Abex
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
namespace net::runelite::cache::script
{

	using HashMap = java::util::HashMap;
	using Map = java::util::Map;

	class Instructions : public std::enable_shared_from_this<Instructions>, public Opcodes
	{
	private:
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final java.util.Map<int, Instruction> instructions = new java.util.HashMap<>();
		std::unordered_map<int, std::shared_ptr<Instruction>> instructions = std::unordered_map<int, std::shared_ptr<Instruction>>();
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final java.util.Map<String, Instruction> instructionsByName = new java.util.HashMap<>();
		std::unordered_map<std::wstring, std::shared_ptr<Instruction>> instructionsByName = std::unordered_map<std::wstring, std::shared_ptr<Instruction>>();

	public:
		virtual void init();

	protected:
		virtual void add(int opcode, const std::wstring &name);

	public:
		virtual std::shared_ptr<Instruction> find(int opcode);

		virtual std::shared_ptr<Instruction> find(const std::wstring &name);
	};

}
