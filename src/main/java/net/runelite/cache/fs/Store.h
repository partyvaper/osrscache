#pragma once

#include "../IndexType.h"
#include "jagex/DiskStorage.h"
#include "Storage.h"
#include "Index.h"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <any>
#include <cassert>
#include <memory>
#include "../../../../../../../tangible_string_helper.h"
#include "../../../../../../../tangible_closeable_interface.h"

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
namespace net::runelite::cache::fs
{

	using Closeable = Closeable;
	using File = java::io::File;
	using FileNotFoundException = java::io::FileNotFoundException;
	using IOException = java::io::IOException;
	using ArrayList = java::util::ArrayList;
	using List = java::util::List;
	using IndexType = net::runelite::cache::IndexType;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;

	class Store final : public std::enable_shared_from_this<Store>, public Closeable
	{
	private:
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		static const std::shared_ptr<Logger> logger;

		const std::shared_ptr<Storage> storage;
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final java.util.List<Index> indexes = new java.util.ArrayList<>();
		std::vector<std::shared_ptr<Index>> indexes = std::vector<std::shared_ptr<Index>>();

	public:
		Store(std::shared_ptr<File> folder);

		Store(std::shared_ptr<Storage> storage);

		std::shared_ptr<Storage> getStorage();

		void close() override;

		int hashCode();

		bool equals(std::any obj);

		std::shared_ptr<Index> addIndex(int id);

		void removeIndex(std::shared_ptr<Index> index);

		void load();

		void save();

		std::vector<std::shared_ptr<Index>> getIndexes();

		std::shared_ptr<Index> getIndex(IndexType type);

		std::shared_ptr<Index> findIndex(int id);
	};

}
