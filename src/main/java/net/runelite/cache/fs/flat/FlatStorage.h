#pragma once

#include "../Archive.h"
#include "../Index.h"
#include "../Storage.h"
#include "../Store.h"
#include "../../index/FileData.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include "tangible_exception_helper.h"
#include <memory>
#include "../../../../../../../../tangible_string_helper.h"

/*
 * Copyright (c) 2018 Abex
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
namespace net::runelite::cache::fs::flat
{

	using File = java::io::File;
	using IOException = java::io::IOException;
	using InputStream = java::io::InputStream;
	using OutputStream = java::io::OutputStream;
	using HashMap = java::util::HashMap;
	using Map = java::util::Map;
	using Archive = net::runelite::cache::fs::Archive;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;

	/**
	 * A Storage that stores the cache as a series of flat files, designed
	 * to be git revisioned.
	 */
	class FlatStorage : public std::enable_shared_from_this<FlatStorage>, public Storage
	{
	protected:
		static const std::wstring EXTENSION;

	private:
		const std::shared_ptr<File> directory;
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final java.util.Map<long, byte[]> data = new java.util.HashMap<>();
		std::unordered_map<long long, std::vector<signed char>> data = std::unordered_map<long long, std::vector<signed char>>();

	public:
		FlatStorage(std::shared_ptr<File> directory);

	protected:
		FlatStorage();

		virtual std::shared_ptr<InputStream> openReader(const std::wstring &filename);

		virtual std::shared_ptr<OutputStream> openWriter(const std::wstring &filename);

		virtual std::vector<std::wstring> listFlatcacheFiles();

	public:
		void init(std::shared_ptr<Store> store) override;

		void close() override;

		void load(std::shared_ptr<Store> store) override;

		void save(std::shared_ptr<Store> store) override;

		std::vector<signed char> loadArchive(std::shared_ptr<Archive> archive) override;

		void saveArchive(std::shared_ptr<Archive> archive, std::vector<signed char> &bytes) override;
	};

}