#pragma once

#include "../ClientScript1Instruction.h"
#include "../InterfaceDefinition.h"
#include "../../io/InputStream.h"
#include <string>
#include <vector>
#include <limits>
#include <any>
#include <optional>
#include <memory>

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
namespace net::runelite::cache::definitions::loaders
{

	using InterfaceDefinition = net::runelite::cache::definitions::InterfaceDefinition;
	using InputStream = net::runelite::cache::io::InputStream;

	class InterfaceLoader : public std::enable_shared_from_this<InterfaceLoader>
	{
	public:
		virtual std::shared_ptr<InterfaceDefinition> load(int id, std::vector<signed char> &b);

	private:
		void decodeIf1(std::shared_ptr<InterfaceDefinition> iface, std::shared_ptr<InputStream> var1);

		void decodeIf3(std::shared_ptr<InterfaceDefinition> iface, std::shared_ptr<InputStream> var1);

		std::vector<std::any> decodeListener(std::shared_ptr<InterfaceDefinition> iface, std::shared_ptr<InputStream> var1);

		std::vector<int> decodeTriggers(std::shared_ptr<InputStream> var1);
	};

}
