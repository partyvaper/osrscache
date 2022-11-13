#include "InputStream.h"

namespace net::runelite::cache::io
{
	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
const std::vector<wchar_t> InputStream::CHARACTERS = std::vector<wchar_t> {L'\u20ac', L'\u0000', L'\u201a', L'\u0192', L'\u201e', L'\u2026', L'\u2020', L'\u2021', L'\u02c6', L'\u2030', L'\u0160', L'\u2039', L'\u0152', L'\u0000', L'\u017d', L'\u0000', L'\u0000', L'\u2018', L'\u2019', L'\u201c', L'\u201d', L'\u2022', L'\u2013', L'\u2014', L'\u02dc', L'\u2122', L'\u0161', L'\u203a', L'\u0153', L'\u0000', L'\u017e', L'\u0178'};

	InputStream::InputStream(std::vector<signed char> &buffer) : buffer(ByteBuffer::wrap(buffer))
	{
	}

	std::vector<signed char> InputStream::getArray()
	{
		assert(buffer->hasArray());
		return buffer->array();
	}

	std::wstring InputStream::toString()
	{
		return L"InputStream{" + L"buffer=" + buffer + L'}';
	}

	int InputStream::read24BitInt()
	{
		return (this->readUnsignedByte() << 16) + (this->readUnsignedByte() << 8) + this->readUnsignedByte();
	}

	void InputStream::skip(int length)
	{
		int pos = buffer->position();
		pos += length;
		buffer->position(pos);
	}

	void InputStream::setOffset(int offset)
	{
		buffer->position(offset);
	}

	int InputStream::getOffset()
	{
		return buffer->position();
	}

	int InputStream::getLength()
	{
		return buffer->limit();
	}

	int InputStream::remaining()
	{
		return buffer->remaining();
	}

	signed char InputStream::readByte()
	{
		return buffer->get();
	}

	void InputStream::readBytes(std::vector<signed char> &buffer, int off, int len)
	{
		this->buffer->get(buffer, off, len);
	}

	void InputStream::readBytes(std::vector<signed char> &buffer)
	{
		this->buffer->get(buffer);
	}

	int InputStream::readUnsignedByte()
	{
		return this->readByte() & 0xFF;
	}

	int InputStream::readUnsignedShort()
	{
		return buffer->getShort() & 0xFFFF;
	}

	short InputStream::readShort()
	{
		return buffer->getShort();
	}

	int InputStream::readInt()
	{
		return buffer->getInt();
	}

	long long InputStream::readLong()
	{
		return buffer->getLong();
	}

	signed char InputStream::peek()
	{
		return buffer->get(buffer->position());
	}

	int InputStream::readBigSmart()
	{
		return peek() >= 0 ? (this->readUnsignedShort() & 0xFFFF) : (this->readInt() & std::numeric_limits<int>::max());
	}

	int InputStream::readBigSmart2()
	{
		if (peek() < 0)
		{
			return readInt() & std::numeric_limits<int>::max(); // and off sign bit
		}
		int value = readUnsignedShort();
		return value == 32767 ? -1 : value;
	}

	int InputStream::readShortSmart()
	{
		int peek = this->peek() & 0xFF;
		return peek < 128 ? this->readUnsignedByte() - 64 : this->readUnsignedShort() - 0xc000;
	}

	int InputStream::readUnsignedShortSmart()
	{
		int peek = this->peek() & 0xFF;
		return peek < 128 ? this->readUnsignedByte() : this->readUnsignedShort() - 0x8000;
	}

	int InputStream::readUnsignedIntSmartShortCompat()
	{
		int var1 = 0;

		int var2;
		for (var2 = this->readUnsignedShortSmart(); var2 == 32767; var2 = this->readUnsignedShortSmart())
		{
			var1 += 32767;
		}

		var1 += var2;
		return var1;
	}

	std::wstring InputStream::readString()
	{
		std::shared_ptr<StringBuilder> sb = std::make_shared<StringBuilder>();

		for (; ;)
		{
			int ch = this->readUnsignedByte();

			if (ch == 0)
			{
				break;
			}

			if (ch >= 128 && ch < 160)
			{
				wchar_t var7 = CHARACTERS[ch - 128];
				if (0 == var7)
				{
					var7 = L'?';
				}

				ch = var7;
			}

			sb->append(static_cast<wchar_t>(ch));
		}
		return sb->toString();
	}

	std::wstring InputStream::readString2()
	{
		if (this->readByte() != 0)
		{
			throw IllegalStateException("Invalid jstr2");
		}
		else
		{
			return readString();
		}
	}

	std::wstring InputStream::readStringOrNull()
	{
		if (this->peek() != 0)
		{
			return readString();
		}
		else
		{
			this->readByte(); // discard
			return L"";
		}
	}

	int InputStream::readVarInt()
	{
		signed char var1 = this->readByte();

		int var2;
		for (var2 = 0; var1 < 0; var1 = this->readByte())
		{
			var2 = (var2 | var1 & 127) << 7;
		}

		return var2 | var1;
	}

	int InputStream::readVarInt2()
	{
		int value = 0;
		int bits = 0;
		int read;
		do
		{
			read = readUnsignedByte();
			value |= (read & 0x7F) << bits;
			bits += 7;
		} while (read > 127);
		return value;
	}

	std::vector<signed char> InputStream::getRemaining()
	{
		std::vector<signed char> b(buffer->remaining());
		buffer->get(b);
		return b;
	}

	int InputStream::read()
	{
		return this->readUnsignedByte();
	}
}
