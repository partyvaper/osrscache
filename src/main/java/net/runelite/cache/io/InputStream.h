#pragma once

#include <string>
#include <vector>
#include <limits>
#include "tangible_exception_helper.h"
#include <cassert>
#include <memory>
#include "../../../../../../../tangible_stringbuilder.h"

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
namespace net::runelite::cache::io
{

	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;

	class InputStream : public java::io::InputStream
	{
	private:
		static const std::vector<wchar_t> CHARACTERS;

		const std::shared_ptr<ByteBuffer> buffer;

	public:
		InputStream(std::vector<signed char> &buffer);

		virtual std::vector<signed char> getArray();

		virtual std::wstring toString();

		virtual int read24BitInt();

		virtual void skip(int length);

		virtual void setOffset(int offset);

		virtual int getOffset();

		virtual int getLength();

		virtual int remaining();

		virtual signed char readByte();

		virtual void readBytes(std::vector<signed char> &buffer, int off, int len);

		virtual void readBytes(std::vector<signed char> &buffer);

		virtual int readUnsignedByte();

		virtual int readUnsignedShort();

		virtual short readShort();

		virtual int readInt();

		virtual long long readLong();

		virtual signed char peek();

		virtual int readBigSmart();

		virtual int readBigSmart2();

		virtual int readShortSmart();

		virtual int readUnsignedShortSmart();

		virtual int readUnsignedIntSmartShortCompat();

		virtual std::wstring readString();

		virtual std::wstring readString2();

		virtual std::wstring readStringOrNull();

		virtual int readVarInt();

		virtual int readVarInt2();

		virtual std::vector<signed char> getRemaining();

		int read() override;

	protected:
		std::shared_ptr<InputStream> shared_from_this()
		{
			return std::static_pointer_cast<InputStream>(java::io::InputStream::shared_from_this());
		}
	};

}
