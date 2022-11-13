#pragma once

#include "../DBTableDefinition.h"
#include "../../io/InputStream.h"
#include "../../util/ScriptVarType.h"
#include <vector>
#include <any>
#include <memory>

/*
 * Copyright (c) 2022, Joshua Filby <joshua@filby.me>
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
namespace net::runelite::cache::definitions::loaders
{

	using DBTableDefinition = net::runelite::cache::definitions::DBTableDefinition;
	using InputStream = net::runelite::cache::io::InputStream;
	using ScriptVarType = net::runelite::cache::util::ScriptVarType;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Slf4j public class DBTableLoader
	class DBTableLoader : public std::enable_shared_from_this<DBTableLoader>
	{
	public:
		virtual std::shared_ptr<DBTableDefinition> load(int id, std::vector<signed char> &b);

	private:
		void decode(int opcode, std::shared_ptr<DBTableDefinition> def, std::shared_ptr<InputStream> stream);

	public:
		static std::vector<std::any> decodeColumnFields(std::shared_ptr<InputStream> stream, std::vector<ScriptVarType> &types);
	};

}
