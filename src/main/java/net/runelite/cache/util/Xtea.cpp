#include "Xtea.h"

namespace net::runelite::cache::util
{
	using InputStream = net::runelite::cache::io::InputStream;
	using OutputStream = net::runelite::cache::io::OutputStream;

	Xtea::Xtea(std::vector<int> &key) : key(key)
	{
	}

	std::vector<signed char> Xtea::encrypt(std::vector<signed char> &data, int len)
	{
		std::shared_ptr<InputStream> in = std::make_shared<InputStream>(data);
		std::shared_ptr<OutputStream> out = std::make_shared<OutputStream>(len);
		int numBlocks = len / 8;
		for (int block = 0; block < numBlocks; ++block)
		{
			int v0 = in->readInt();
			int v1 = in->readInt();
			int sum = 0;
			for (int i = 0; i < ROUNDS; ++i)
			{
				v0 += (((v1 << 4) ^ (static_cast<int>(static_cast<unsigned int>(v1) >> 5))) + v1) ^ (sum + key[sum & 3]);
				sum += GOLDEN_RATIO;
				v1 += (((v0 << 4) ^ (static_cast<int>(static_cast<unsigned int>(v0) >> 5))) + v0) ^ (sum + key[(static_cast<int>(static_cast<unsigned int>(sum) >> 11)) & 3]);
			}
			out->writeInt(v0);
			out->writeInt(v1);
		}
		out->writeBytes(in->getRemaining());
		return out->flip();
	}

	std::vector<signed char> Xtea::decrypt(std::vector<signed char> &data, int len)
	{
		std::shared_ptr<InputStream> in = std::make_shared<InputStream>(data);
		std::shared_ptr<OutputStream> out = std::make_shared<OutputStream>(len);
		int numBlocks = len / 8;
		for (int block = 0; block < numBlocks; ++block)
		{
			int v0 = in->readInt();
			int v1 = in->readInt();
			int sum = GOLDEN_RATIO * ROUNDS;
			for (int i = 0; i < ROUNDS; ++i)
			{
				v1 -= (((v0 << 4) ^ (static_cast<int>(static_cast<unsigned int>(v0) >> 5))) + v0) ^ (sum + key[(static_cast<int>(static_cast<unsigned int>(sum) >> 11)) & 3]);
				sum -= GOLDEN_RATIO;
				v0 -= (((v1 << 4) ^ (static_cast<int>(static_cast<unsigned int>(v1) >> 5))) + v1) ^ (sum + key[sum & 3]);
			}
			out->writeInt(v0);
			out->writeInt(v1);
		}
		out->writeBytes(in->getRemaining());
		return out->flip();
	}
}
