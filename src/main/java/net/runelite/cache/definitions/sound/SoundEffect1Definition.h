#pragma once

#include "SoundEffect2Definition.h"
#include "SoundEffect3Definition.h"
#include <vector>
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
namespace net::runelite::cache::definitions::sound
{

	class SoundEffect1Definition : public std::enable_shared_from_this<SoundEffect1Definition>
	{
	public:
		std::shared_ptr<SoundEffect2Definition> field1173;
		std::shared_ptr<SoundEffect2Definition> field1174;
		std::shared_ptr<SoundEffect2Definition> field1175;
		int field1176 = 500;
		std::vector<int> field1177 = std::vector<int> {0, 0, 0, 0, 0};
		std::shared_ptr<SoundEffect2Definition> field1178;
		std::vector<int> field1179 = std::vector<int> {0, 0, 0, 0, 0};
		std::vector<int> field1180 = std::vector<int> {0, 0, 0, 0, 0};
		std::shared_ptr<SoundEffect2Definition> field1181;
		std::shared_ptr<SoundEffect3Definition> field1182;
		std::shared_ptr<SoundEffect2Definition> field1183;
		int field1184 = 100;
		std::shared_ptr<SoundEffect2Definition> field1186;
		int field1187 = 0;
		int field1188 = 0;
		std::shared_ptr<SoundEffect2Definition> field1192;
		std::shared_ptr<SoundEffect2Definition> field1193;
	};

}
