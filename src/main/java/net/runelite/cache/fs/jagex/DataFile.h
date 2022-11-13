#pragma once

#include "DataFileWriteResult.h"
#include <vector>
#include <mutex>
#include <memory>
#include "../../../../../../../../tangible_closeable_interface.h"

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

	using Closeable = Closeable;
	using File = java::io::File;
	using FileNotFoundException = java::io::FileNotFoundException;
	using IOException = java::io::IOException;
	using RandomAccessFile = java::io::RandomAccessFile;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;

	class DataFile : public std::enable_shared_from_this<DataFile>, public Closeable
	{
		private:
			std::mutex lock_object;

//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		static const std::shared_ptr<Logger> logger;

		static constexpr int SECTOR_SIZE = 520;

		const std::shared_ptr<RandomAccessFile> dat;

	public:
		DataFile(std::shared_ptr<File> file);

		void close() override;

		virtual void clear();

		/**
		 *
		 * @param indexId expected index of archive of contents being read
		 * @param archiveId expected archive of contents being read
		 * @param sector sector to start reading at
		 * @param size size of file
		 * @return
		 * @throws IOException
		 */
		virtual std::vector<signed char> read(int indexId, int archiveId, int sector, int size);

		virtual std::shared_ptr<DataFileWriteResult> write(int indexId, int archiveId, std::vector<signed char> &compressedData);
	};

}
