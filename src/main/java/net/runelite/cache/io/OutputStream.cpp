#include "OutputStream.h"

namespace net::runelite::cache::io
{
	using Preconditions = com::google::common::base::Preconditions;
	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
	using StandardCharsets = java::nio::charset::StandardCharsets;

	OutputStream::OutputStream(int capacity)
	{
		buffer = ByteBuffer::allocate(capacity);
	}

	OutputStream::OutputStream() : OutputStream(16)
	{
	}

	std::vector<signed char> OutputStream::getArray()
	{
		assert(buffer->hasArray());
		return buffer->array();
	}

	void OutputStream::ensureRemaining(int remaining)
	{
		while (remaining > buffer->remaining())
		{
			int newCapacity = buffer->capacity() * 2;

			std::shared_ptr<ByteBuffer> old = buffer;
			old->flip();

			buffer = ByteBuffer::allocate(newCapacity);

			buffer->put(old);
		}
	}

	void OutputStream::skip(int length)
	{
		int pos = buffer->position();
		pos += length;
		buffer->position(pos);
	}

	int OutputStream::getOffset()
	{
		return buffer->position();
	}

	void OutputStream::setOffset(int offset)
	{
		buffer->position(offset);
	}

	void OutputStream::writeBytes(std::vector<signed char> &b)
	{
		writeBytes(b, 0, b.size());
	}

	void OutputStream::writeBytes(std::vector<signed char> &b, int offset, int length)
	{
		ensureRemaining(length);
		buffer->put(b, offset, length);
	}

	void OutputStream::writeByte(int i)
	{
		ensureRemaining(1);
		buffer->put(static_cast<signed char>(i));
	}

	void OutputStream::writeBigSmart(int value)
	{
		Preconditions::checkArgument(value >= 0);
		if (value >= 32768)
		{
			ensureRemaining(4);
			this->writeInt((1 << 31) | value);
		}
		else
		{
			ensureRemaining(2);
			this->writeShort(value);
		}
	}

	void OutputStream::writeShort(int i)
	{
		ensureRemaining(2);
		buffer->putShort(static_cast<short>(i));
	}

	void OutputStream::writeShortSmart(int value)
	{
		Preconditions::checkArgument(value >= 0);
		if (value < 128)
		{
			writeByte(value);
		}
		else
		{
			writeShort(0x8000 | value);
		}
	}

	void OutputStream::write24BitInt(int i)
	{
		ensureRemaining(3);
		buffer->put(static_cast<signed char>(static_cast<int>(static_cast<unsigned int>(i) >> 16)));
		buffer->put(static_cast<signed char>(static_cast<int>(static_cast<unsigned int>(i) >> 8)));
		buffer->put(static_cast<signed char>(i & 0xFF));
	}

	void OutputStream::writeInt(int i)
	{
		ensureRemaining(4);
		buffer->putInt(i);
	}

	void OutputStream::writeVarInt(int var1)
	{
		if ((var1 & -128) != 0)
		{
			if ((var1 & -16384) != 0)
			{
				if ((var1 & -2097152) != 0)
				{
					if ((var1 & -268435456) != 0)
					{
						this->writeByte(static_cast<int>(static_cast<unsigned int>(var1) >> 28) | 128);
					}

					this->writeByte(static_cast<int>(static_cast<unsigned int>(var1) >> 21) | 128);
				}

				this->writeByte(static_cast<int>(static_cast<unsigned int>(var1) >> 14) | 128);
			}

			this->writeByte(static_cast<int>(static_cast<unsigned int>(var1) >> 7) | 128);
		}

		this->writeByte(var1 & 127);
	}

	void OutputStream::writeLengthFromMark(int var1)
	{
		this->getArray()[this->getOffset() - var1 - 4] = static_cast<signed char>(var1 >> 24);
		this->getArray()[this->getOffset() - var1 - 3] = static_cast<signed char>(var1 >> 16);
		this->getArray()[this->getOffset() - var1 - 2] = static_cast<signed char>(var1 >> 8);
		this->getArray()[this->getOffset() - var1 - 1] = static_cast<signed char>(var1);
	}

	void OutputStream::writeString(const std::wstring &str)
	{
		writeBytes(str.getBytes(StandardCharsets::ISO_8859_1));
		writeByte(0);
	}

	std::vector<signed char> OutputStream::flip()
	{
		buffer->flip();
		std::vector<signed char> b(buffer->limit());
		buffer->get(b);
		return b;
	}

	void OutputStream::write(int b)
	{
		buffer->put(static_cast<signed char>(b));
	}
}
