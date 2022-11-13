#include "IndexFile.h"

namespace net::runelite::cache::fs::jagex
{
	using Closeable = Closeable;
	using File = java::io::File;
	using FileNotFoundException = java::io::FileNotFoundException;
	using IOException = java::io::IOException;
	using RandomAccessFile = java::io::RandomAccessFile;
	using Objects = java::util::Objects;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> IndexFile::logger = org::slf4j::LoggerFactory::getLogger(IndexFile::class);

	IndexFile::IndexFile(int indexFileId, std::shared_ptr<File> file) : indexFileId(indexFileId), file(file), idx(std::make_shared<RandomAccessFile>(file, L"rw"))
	{
	}

	void IndexFile::close()
	{
		idx->close();
	}

	void IndexFile::clear()
	{
		idx->setLength(0LL);
	}

	int IndexFile::hashCode()
	{
		int hash = 3;
		hash = 41 * hash + Objects::hashCode(this->file);
		return hash;
	}

	bool IndexFile::equals(std::any obj)
	{
		if (!obj.has_value())
		{
			return false;
		}
		if (getClass() != obj.type())
		{
			return false;
		}
		constexpr std::shared_ptr<IndexFile> other = std::any_cast<std::shared_ptr<IndexFile>>(obj);
		if (!Objects::equals(this->file, other->file))
		{
			return false;
		}
		return true;
	}

	int IndexFile::getIndexFileId()
	{
		return indexFileId;
	}

	void IndexFile::write(std::shared_ptr<IndexEntry> entry)
	{
		std::scoped_lock<std::mutex> lock(lock_object);
		idx->seek(entry->getId() * INDEX_ENTRY_LEN);

		buffer[0] = static_cast<signed char>(entry->getLength() >> 16);
		buffer[1] = static_cast<signed char>(entry->getLength() >> 8);
		buffer[2] = static_cast<signed char>(entry->getLength());

		buffer[3] = static_cast<signed char>(entry->getSector() >> 16);
		buffer[4] = static_cast<signed char>(entry->getSector() >> 8);
		buffer[5] = static_cast<signed char>(entry->getSector());

		idx->write(buffer);
	}

	std::shared_ptr<IndexEntry> IndexFile::read(int id)
	{
		std::scoped_lock<std::mutex> lock(lock_object);
		idx->seek(id * INDEX_ENTRY_LEN);
		int i = idx->read(buffer);
		if (i != INDEX_ENTRY_LEN)
		{
			logger->debug(L"short read for id {} on index {}: {}", id, indexFileId, i);
			return nullptr;
		}

		int length = ((buffer[0] & 0xFF) << 16) | ((buffer[1] & 0xFF) << 8) | (buffer[2] & 0xFF);
		int sector = ((buffer[3] & 0xFF) << 16) | ((buffer[4] & 0xFF) << 8) | (buffer[5] & 0xFF);

		if (length <= 0 || sector <= 0)
		{
			logger->debug(L"invalid length or sector {}/{}", length, sector);
			return nullptr;
		}

		return std::make_shared<IndexEntry>(shared_from_this(), id, sector, length);
	}

	int IndexFile::getIndexCount()
	{
		std::scoped_lock<std::mutex> lock(lock_object);
		return static_cast<int>(idx->length() / INDEX_ENTRY_LEN);
	}
}
