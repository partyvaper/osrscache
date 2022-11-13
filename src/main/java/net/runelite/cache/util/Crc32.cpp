#include "Crc32.h"

namespace net::runelite::cache::util
{
	using CRC32 = java::util::zip::CRC32;

	void Crc32::update(std::vector<signed char> &data, int offset, int length)
	{
		crc32->update(data, offset, length);
	}

	int Crc32::getHash()
	{
		return static_cast<int>(crc32->getValue());
	}
}
