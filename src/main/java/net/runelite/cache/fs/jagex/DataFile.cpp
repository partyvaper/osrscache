#include "DataFile.h"

namespace net::runelite::cache::fs::jagex
{
	using Closeable = Closeable;
	using File = java::io::File;
	using FileNotFoundException = java::io::FileNotFoundException;
	using IOException = java::io::IOException;
	using RandomAccessFile = java::io::RandomAccessFile;
	using ByteBuffer = java::nio::ByteBuffer;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> DataFile::logger = org::slf4j::LoggerFactory::getLogger(DataFile::class);

	DataFile::DataFile(std::shared_ptr<File> file) : dat(std::make_shared<RandomAccessFile>(file, L"rw"))
	{
	}

	void DataFile::close()
	{
		dat->close();
	}

	void DataFile::clear()
	{
		dat->setLength(0LL);
	}

	std::vector<signed char> DataFile::read(int indexId, int archiveId, int sector, int size)
	{
		std::scoped_lock<std::mutex> lock(lock_object);
		if (sector <= 0LL || dat->length() / SECTOR_SIZE < static_cast<long long>(sector))
		{
			logger->warn(L"bad read, dat length {}, requested sector {}", dat->length(), sector);
			return std::vector<signed char>();
		}

		std::vector<signed char> readBuffer(SECTOR_SIZE);
		std::shared_ptr<ByteBuffer> buffer = ByteBuffer::allocate(size);

		for (int part = 0, readBytesCount = 0, nextSector; size > readBytesCount; sector = nextSector)
		{
			if (sector == 0)
			{
				logger->warn(L"Unexpected end of file");
				return std::vector<signed char>();
			}

			dat->seek(SECTOR_SIZE * sector);

			int dataBlockSize = size - readBytesCount;
			signed char headerSize;
			int currentIndex;
			int currentPart;
			int currentArchive;
			if (archiveId > 0xFFFF)
			{
				headerSize = 10;
				if (dataBlockSize > SECTOR_SIZE - headerSize)
				{
					dataBlockSize = SECTOR_SIZE - headerSize;
				}

				int i = dat->read(readBuffer, 0, headerSize + dataBlockSize);
				if (i != headerSize + dataBlockSize)
				{
					logger->warn(L"Short read when reading file data for {}/{}", indexId, archiveId);
					return std::vector<signed char>();
				}

				currentArchive = ((readBuffer[0] & 0xFF) << 24) | ((readBuffer[1] & 0xFF) << 16) | ((readBuffer[2] & 0xFF) << 8) | (readBuffer[3] & 0xFF);
				currentPart = ((readBuffer[4] & 0xFF) << 8) + (readBuffer[5] & 0xFF);
				nextSector = ((readBuffer[6] & 0xFF) << 16) | ((readBuffer[7] & 0xFF) << 8) | (readBuffer[8] & 0xFF);
				currentIndex = readBuffer[9] & 0xFF;
			}
			else
			{
				headerSize = 8;
				if (dataBlockSize > SECTOR_SIZE - headerSize)
				{
					dataBlockSize = SECTOR_SIZE - headerSize;
				}

				int i = dat->read(readBuffer, 0, headerSize + dataBlockSize);
				if (i != headerSize + dataBlockSize)
				{
					logger->warn(L"short read");
					return std::vector<signed char>();
				}

				currentArchive = ((readBuffer[0] & 0xFF) << 8) | (readBuffer[1] & 0xFF);
				currentPart = ((readBuffer[2] & 0xFF) << 8) | (readBuffer[3] & 0xFF);
				nextSector = ((readBuffer[4] & 0xFF) << 16) | ((readBuffer[5] & 0xFF) << 8) | (readBuffer[6] & 0xFF);
				currentIndex = readBuffer[7] & 0xFF;
			}

			if (archiveId != currentArchive || currentPart != part || indexId != currentIndex)
			{
				logger->warn(L"data mismatch {} != {}, {} != {}, {} != {}", archiveId, currentArchive, part, currentPart, indexId, currentIndex);
				return std::vector<signed char>();
			}

			if (nextSector < 0 || dat->length() / SECTOR_SIZE < static_cast<long long>(nextSector))
			{
				logger->warn(L"Invalid next sector");
				return std::vector<signed char>();
			}

			buffer->put(readBuffer, headerSize, dataBlockSize);
			readBytesCount += dataBlockSize;

			++part;
		}

		buffer->flip();
		return buffer->array();
	}

	std::shared_ptr<DataFileWriteResult> DataFile::write(int indexId, int archiveId, std::vector<signed char> &compressedData)
	{
		std::scoped_lock<std::mutex> lock(lock_object);
		int sector;
		int startSector;

		std::vector<signed char> writeBuffer(SECTOR_SIZE);
		std::shared_ptr<ByteBuffer> data = ByteBuffer::wrap(compressedData);

		sector = static_cast<int>((dat->length() + static_cast<long long>(SECTOR_SIZE - 1)) / static_cast<long long>(SECTOR_SIZE));
		if (sector == 0)
		{
			sector = 1;
		}
		startSector = sector;

		for (int part = 0; data->hasRemaining(); ++part)
		{
			int nextSector = sector + 1; // we always just append sectors
			int dataToWrite;

			if (0xFFFF < archiveId)
			{
				if (data->remaining() <= 510)
				{
					nextSector = 0;
				}

				writeBuffer[0] = static_cast<signed char>(archiveId >> 24);
				writeBuffer[1] = static_cast<signed char>(archiveId >> 16);
				writeBuffer[2] = static_cast<signed char>(archiveId >> 8);
				writeBuffer[3] = static_cast<signed char>(archiveId);
				writeBuffer[4] = static_cast<signed char>(part >> 8);
				writeBuffer[5] = static_cast<signed char>(part);
				writeBuffer[6] = static_cast<signed char>(nextSector >> 16);
				writeBuffer[7] = static_cast<signed char>(nextSector >> 8);
				writeBuffer[8] = static_cast<signed char>(nextSector);
				writeBuffer[9] = static_cast<signed char>(indexId);
				dat->seek(SECTOR_SIZE * sector);
				dat->write(writeBuffer, 0, 10);

				dataToWrite = data->remaining();
				if (dataToWrite > 510)
				{
					dataToWrite = 510;
				}
			}
			else
			{
				if (data->remaining() <= 512)
				{
					nextSector = 0;
				}

				writeBuffer[0] = static_cast<signed char>(archiveId >> 8);
				writeBuffer[1] = static_cast<signed char>(archiveId);
				writeBuffer[2] = static_cast<signed char>(part >> 8);
				writeBuffer[3] = static_cast<signed char>(part);
				writeBuffer[4] = static_cast<signed char>(nextSector >> 16);
				writeBuffer[5] = static_cast<signed char>(nextSector >> 8);
				writeBuffer[6] = static_cast<signed char>(nextSector);
				writeBuffer[7] = static_cast<signed char>(indexId);
				dat->seek(SECTOR_SIZE * sector);
				dat->write(writeBuffer, 0, 8);

				dataToWrite = data->remaining();
				if (dataToWrite > 512)
				{
					dataToWrite = 512;
				}
			}

			data->get(writeBuffer, 0, dataToWrite);
			dat->write(writeBuffer, 0, dataToWrite);
			sector = nextSector;
		}

		std::shared_ptr<DataFileWriteResult> res = std::make_shared<DataFileWriteResult>();
		res->sector = startSector;
		res->compressedLength = compressedData.size();
		return res;
	}
}
