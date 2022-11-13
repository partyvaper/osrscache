#pragma once

#include "../index/FileData.h"
#include "Index.h"
#include "ArchiveFiles.h"
#include <vector>
#include <any>
#include "tangible_exception_helper.h"
#include <memory>
#include "../../../../../../../tangible_string_helper.h"

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

	using IOException = java::io::IOException;
	using FileData = net::runelite::cache::index::FileData;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;

	class Archive : public std::enable_shared_from_this<Archive>
	{
	private:
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		static const std::shared_ptr<Logger> logger;

		const std::shared_ptr<Index> index; // member of this index

		const int archiveId;
		int nameHash = 0;
		int crc = 0;
		int revision = 0;
		int compression = 0;
		std::vector<std::shared_ptr<FileData>> fileData;
		std::vector<signed char> hash; // used by webservice, sha256 hash of content

	public:
		Archive(std::shared_ptr<Index> index, int id);

		virtual int hashCode();

		virtual bool equals(std::any obj);

		virtual std::shared_ptr<Index> getIndex();

		virtual std::vector<signed char> decompress(std::vector<signed char> &data);

		virtual std::vector<signed char> decompress(std::vector<signed char> &data, std::vector<int> &keys);

		virtual std::shared_ptr<ArchiveFiles> getFiles(std::vector<signed char> &data);

		virtual std::shared_ptr<ArchiveFiles> getFiles(std::vector<signed char> &data, std::vector<int> &keys);

		virtual int getArchiveId();

		virtual int getNameHash();

		virtual void setNameHash(int nameHash);

		virtual int getCrc();

		virtual void setCrc(int crc);

		virtual int getRevision();

		virtual void setRevision(int revision);

		virtual int getCompression();

		virtual void setCompression(int compression);

		virtual std::vector<std::shared_ptr<FileData>> getFileData();

		virtual void setFileData(std::vector<std::shared_ptr<FileData>> &fileData);

		virtual std::vector<signed char> getHash();

		virtual void setHash(std::vector<signed char> &hash);
	};

}
