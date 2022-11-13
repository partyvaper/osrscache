#pragma once

#include "../index/ArchiveData.h"
#include "../index/FileData.h"
#include "../index/IndexData.h"
#include "../util/Djb2.h"
#include "Archive.h"
#include <string>
#include <vector>
#include <any>
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
namespace net::runelite::cache::fs
{

	using ArrayList = java::util::ArrayList;
	using List = java::util::List;
	using IndexData = net::runelite::cache::index::IndexData;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;

	class Index : public std::enable_shared_from_this<Index>
	{
	private:
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		static const std::shared_ptr<Logger> logger;

		const int id;

		int protocol = 6;
		bool named = true;
		int revision = 0;
		int crc = 0;
		int compression = 0; // compression method of this index's data in 255

//JAVA TO C++ CONVERTER WARNING: C++ has no equivalent to a 'final' collection which allows modification of internal state:
//ORIGINAL LINE: private final java.util.List<Archive> archives = new java.util.ArrayList<>();
		std::vector<std::shared_ptr<Archive>> archives = std::vector<std::shared_ptr<Archive>>();

	public:
		Index(int id);

		virtual int hashCode();

		virtual bool equals(std::any obj);

		virtual int getId();

		virtual int getProtocol();

		virtual void setProtocol(int protocol);

		virtual bool isNamed();

		virtual void setNamed(bool named);

		virtual int getRevision();

		virtual void setRevision(int revision);

		virtual int getCrc();

		virtual void setCrc(int crc);

		virtual int getCompression();

		virtual void setCompression(int compression);

		virtual std::vector<std::shared_ptr<Archive>> getArchives();

		virtual std::shared_ptr<Archive> addArchive(int id);

		virtual std::shared_ptr<Archive> getArchive(int id);

		virtual std::shared_ptr<Archive> findArchiveByName(const std::wstring &name);

		virtual std::shared_ptr<IndexData> toIndexData();
	};

}
