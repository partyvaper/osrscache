#pragma once

#include "../io/InputStream.h"
#include "../io/OutputStream.h"
#include "FSFile.h"
#include <unordered_map>
#include <vector>
#include <any>
#include "tangible_exception_helper.h"
#include <cassert>
#include <memory>
#include "../../../../../../../tangible_rectangular_vectors.h"

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

	using ArrayList = java::util::ArrayList;
	using HashMap = java::util::HashMap;
	using List = java::util::List;
	using Map = java::util::Map;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;

	class ArchiveFiles : public std::enable_shared_from_this<ArchiveFiles>
	{
	private:
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		static const std::shared_ptr<Logger> logger;

//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final java.util.List<FSFile> files = new java.util.ArrayList<>();
		std::vector<std::shared_ptr<FSFile>> files = std::vector<std::shared_ptr<FSFile>>();
//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final java.util.Map<int, FSFile> fileMap = new java.util.HashMap<>();
		std::unordered_map<int, std::shared_ptr<FSFile>> fileMap = std::unordered_map<int, std::shared_ptr<FSFile>>();

	public:
		virtual int hashCode();

		virtual bool equals(std::any obj);

		virtual void addFile(std::shared_ptr<FSFile> file);

		virtual std::vector<std::shared_ptr<FSFile>> getFiles();

		virtual std::shared_ptr<FSFile> findFile(int fileId);

		virtual void clear();

		virtual void loadContents(std::vector<signed char> &data);

		virtual std::vector<signed char> saveContents();
	};

}
