#pragma once

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
namespace net::runelite::cache::io
{

	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;

	class OutputStream final : public java::io::OutputStream
	{
	private:
		std::shared_ptr<ByteBuffer> buffer;

	public:
		OutputStream(int capacity);

		OutputStream();

		std::vector<signed char> getArray();

	private:
		void ensureRemaining(int remaining);

	public:
		void skip(int length);

		int getOffset();

		void setOffset(int offset);

		void writeBytes(std::vector<signed char> &b);

		void writeBytes(std::vector<signed char> &b, int offset, int length);

		void writeByte(int i);

		void writeBigSmart(int value);

		void writeShort(int i);

		void writeShortSmart(int value);

		void write24BitInt(int i);

		void writeInt(int i);

		void writeVarInt(int var1);

		void writeLengthFromMark(int var1);

		void writeString(const std::wstring &str);

		std::vector<signed char> flip();

		void write(int b) override;


	protected:
		std::shared_ptr<OutputStream> shared_from_this()
		{
			return std::static_pointer_cast<OutputStream>(java::io::OutputStream::shared_from_this());
		}
	};

}
