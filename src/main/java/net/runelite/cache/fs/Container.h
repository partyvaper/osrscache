#pragma once

#include "jagex/CompressionType.h"
#include "../io/InputStream.h"
#include "../io/OutputStream.h"
#include "../util/BZip2.h"
#include "../util/Crc32.h"
#include "../util/GZip.h"
#include "../util/Xtea.h"
#include <vector>
#include <stdexcept>
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
namespace net::runelite::cache::fs
{

//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static com.google.common.primitives.Bytes.concat;
	using IOException = java::io::IOException;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;

	class Container : public std::enable_shared_from_this<Container>
	{
	private:
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		static const std::shared_ptr<Logger> logger;

	public:
		std::vector<signed char> data;
		int compression = 0; // compression
		int revision = 0;
		int crc = 0; // crc of compressed data

		Container(int compression, int revision);

		virtual void compress(std::vector<signed char> &data, std::vector<int> &keys);

		static std::shared_ptr<Container> decompress(std::vector<signed char> &b, std::vector<int> &keys);

	private:
		static std::vector<signed char> decrypt(std::vector<signed char> &data, int length, std::vector<int> &keys);

		static std::vector<signed char> encrypt(std::vector<signed char> &data, int length, std::vector<int> &keys);
	};

}
