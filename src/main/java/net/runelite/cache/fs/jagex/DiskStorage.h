#pragma once

#include "../Archive.h"
#include "../Container.h"
#include "../Index.h"
#include "../Storage.h"
#include "../Store.h"
#include "../../index/ArchiveData.h"
#include "../../index/IndexData.h"
#include "../../util/Crc32.h"
#include "DataFile.h"
#include "IndexFile.h"
#include <string>
#include <vector>
#include <cassert>
#include <memory>

/*
 * Copyright (c) 2016-2017, Adam <Adam@sigterm.info>
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
namespace net::runelite::cache::fs::jagex
{

	using File = java::io::File;
	using FileNotFoundException = java::io::FileNotFoundException;
	using IOException = java::io::IOException;
	using ArrayList = java::util::ArrayList;
	using List = java::util::List;
	using Archive = net::runelite::cache::fs::Archive;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;

	class DiskStorage : public std::enable_shared_from_this<DiskStorage>, public Storage
	{
	private:
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		static const std::shared_ptr<Logger> logger;

		static const std::wstring MAIN_FILE_CACHE_DAT;
		static const std::wstring MAIN_FILE_CACHE_IDX;

		const std::shared_ptr<File> folder;

		const std::shared_ptr<DataFile> data;
		const std::shared_ptr<IndexFile> index255;
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final java.util.List<IndexFile> indexFiles = new java.util.ArrayList<>();
		std::vector<std::shared_ptr<IndexFile>> indexFiles = std::vector<std::shared_ptr<IndexFile>>();

	public:
		DiskStorage(std::shared_ptr<File> folder);

		void init(std::shared_ptr<Store> store) override;

		void close() override;

	private:
		std::shared_ptr<IndexFile> getIndex(int i);

	public:
		void load(std::shared_ptr<Store> store) override;

		virtual std::vector<signed char> readIndex(int indexId);

	private:
		void loadIndex(std::shared_ptr<Index> index);

	public:
		std::vector<signed char> loadArchive(std::shared_ptr<Archive> archive) override;

		void save(std::shared_ptr<Store> store) override;

	private:
		void saveIndex(std::shared_ptr<Index> index);

	public:
		void saveArchive(std::shared_ptr<Archive> a, std::vector<signed char> &archiveData) override;
	};

}
