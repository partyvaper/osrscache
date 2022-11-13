#include "Container.h"

namespace net::runelite::cache::fs
{
//	import static com.google.common.primitives.Bytes.concat;
	using Ints = com::google::common::primitives::Ints;
	using IOException = java::io::IOException;
	using CompressionType = net::runelite::cache::fs::jagex::CompressionType;
	using InputStream = net::runelite::cache::io::InputStream;
	using OutputStream = net::runelite::cache::io::OutputStream;
	using BZip2 = net::runelite::cache::util::BZip2;
	using Crc32 = net::runelite::cache::util::Crc32;
	using GZip = net::runelite::cache::util::GZip;
	using Xtea = net::runelite::cache::util::Xtea;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> Container::logger = org::slf4j::LoggerFactory::getLogger(Container::class);

	Container::Container(int compression, int revision)
	{
		this->compression = compression;
		this->revision = revision;
	}

	void Container::compress(std::vector<signed char> &data, std::vector<int> &keys)
	{
		std::shared_ptr<OutputStream> stream = std::make_shared<OutputStream>();

		std::vector<signed char> compressedData;
		int length;
		switch (compression)
		{
			case CompressionType::NONE:
				compressedData = data;
				length = compressedData.size();
				break;
			case CompressionType::BZ2:
				compressedData = concat(Ints::toByteArray(data.size()), BZip2::compress(data));
				length = compressedData.size() - 4;
				break;
			case CompressionType::GZ:
				compressedData = concat(Ints::toByteArray(data.size()), GZip::compress(data));
				length = compressedData.size() - 4;
				break;
			default:
				throw std::runtime_error("Unknown compression type");
		}

		compressedData = encrypt(compressedData, compressedData.size(), keys);

		stream->writeByte(compression);
		stream->writeInt(length);

		stream->writeBytes(compressedData);
		if (revision != -1)
		{
			stream->writeShort(revision);
		}

		this->data = stream->flip();
	}

	std::shared_ptr<Container> Container::decompress(std::vector<signed char> &b, std::vector<int> &keys)
	{
		std::shared_ptr<InputStream> stream = std::make_shared<InputStream>(b);

		int compression = stream->readUnsignedByte();
		int compressedLength = stream->readInt();
		if (compressedLength < 0 || compressedLength > 1000000)
		{
			throw std::runtime_error("Invalid data");
		}

		std::shared_ptr<Crc32> crc32 = std::make_shared<Crc32>();
		crc32->update(b, 0, 5); // compression + length

		std::vector<signed char> data;
		int revision = -1;
		switch (compression)
		{
			case CompressionType::NONE:
			{
				std::vector<signed char> encryptedData(compressedLength);
				stream->readBytes(encryptedData, 0, compressedLength);

				crc32->update(encryptedData, 0, compressedLength);
				std::vector<signed char> decryptedData = decrypt(encryptedData, encryptedData.size(), keys);

				if (stream->remaining() >= 2)
				{
					revision = stream->readUnsignedShort();
					assert(revision != -1);
				}

				data = decryptedData;

				break;
			}
			case CompressionType::BZ2:
			{
				std::vector<signed char> encryptedData(compressedLength + 4);
				stream->readBytes(encryptedData);

				crc32->update(encryptedData, 0, encryptedData.size());
				std::vector<signed char> decryptedData = decrypt(encryptedData, encryptedData.size(), keys);

				if (stream->remaining() >= 2)
				{
					revision = stream->readUnsignedShort();
					assert(revision != -1);
				}

				stream = std::make_shared<InputStream>(decryptedData);

				int decompressedLength = stream->readInt();
				data = BZip2::decompress(stream->getRemaining(), compressedLength);

				if (data.empty())
				{
					return nullptr;
				}

				assert(data.size() == decompressedLength);

				break;
			}
			case CompressionType::GZ:
			{
				std::vector<signed char> encryptedData(compressedLength + 4);
				stream->readBytes(encryptedData);

				crc32->update(encryptedData, 0, encryptedData.size());
				std::vector<signed char> decryptedData = decrypt(encryptedData, encryptedData.size(), keys);

				if (stream->remaining() >= 2)
				{
					revision = stream->readUnsignedShort();
					assert(revision != -1);
				}

				stream = std::make_shared<InputStream>(decryptedData);

				int decompressedLength = stream->readInt();
				data = GZip::decompress(stream->getRemaining(), compressedLength);

				if (data.empty())
				{
					return nullptr;
				}

				assert(data.size() == decompressedLength);

				break;
			}
			default:
				throw std::runtime_error("Unknown decompression type");
		}

		std::shared_ptr<Container> container = std::make_shared<Container>(compression, revision);
		container->data = data;
		container->crc = crc32->getHash();
		return container;
	}

	std::vector<signed char> Container::decrypt(std::vector<signed char> &data, int length, std::vector<int> &keys)
	{
		if (keys.empty())
		{
			return data;
		}

		std::shared_ptr<Xtea> xtea = std::make_shared<Xtea>(keys);
		return xtea->decrypt(data, length);
	}

	std::vector<signed char> Container::encrypt(std::vector<signed char> &data, int length, std::vector<int> &keys)
	{
		if (keys.empty())
		{
			return data;
		}

		std::shared_ptr<Xtea> xtea = std::make_shared<Xtea>(keys);
		return xtea->encrypt(data, length);
	}
}
