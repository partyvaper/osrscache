#pragma once

#include "fs/Store.h"
#include <string>
#include <vector>
#include <iostream>
#include "tangible_exception_helper.h"
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
namespace net::runelite::cache
{

	using File = java::io::File;
	using IOException = java::io::IOException;
	using Store = net::runelite::cache::fs::Store;

	class Cache : public std::enable_shared_from_this<Cache>
	{
	public:
		static void main(std::vector<std::wstring> &args);

	private:
		static std::shared_ptr<Store> loadStore(const std::wstring &cache);

		static void dumpItems(std::shared_ptr<Store> store, std::shared_ptr<File> itemdir);

		static void dumpNpcs(std::shared_ptr<Store> store, std::shared_ptr<File> npcdir);

		static void dumpObjects(std::shared_ptr<Store> store, std::shared_ptr<File> objectdir);

		static void dumpSprites(std::shared_ptr<Store> store, std::shared_ptr<File> spritedir);
	};

}
