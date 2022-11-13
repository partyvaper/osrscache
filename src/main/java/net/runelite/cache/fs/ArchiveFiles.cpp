#include "ArchiveFiles.h"

namespace net::runelite::cache::fs
{
	using Preconditions = com::google::common::base::Preconditions;
	using ArrayList = java::util::ArrayList;
	using Collections = java::util::Collections;
	using HashMap = java::util::HashMap;
	using List = java::util::List;
	using Map = java::util::Map;
	using Objects = java::util::Objects;
	using InputStream = net::runelite::cache::io::InputStream;
	using OutputStream = net::runelite::cache::io::OutputStream;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> ArchiveFiles::logger = org::slf4j::LoggerFactory::getLogger(ArchiveFiles::class);

	int ArchiveFiles::hashCode()
	{
		int hash = 7;
		hash = 67 * hash + Objects::hashCode(this->files);
		return hash;
	}

	bool ArchiveFiles::equals(std::any obj)
	{
		if (!obj.has_value())
		{
			return false;
		}
		if (getClass() != obj.type())
		{
			return false;
		}
		constexpr std::shared_ptr<ArchiveFiles> other = std::any_cast<std::shared_ptr<ArchiveFiles>>(obj);
		if (!Objects::equals(this->files, other->files))
		{
			return false;
		}
		return true;
	}

	void ArchiveFiles::addFile(std::shared_ptr<FSFile> file)
	{
		Preconditions::checkArgument(file->getFileId() != -1);

		if (fileMap.find(file->getFileId()) != fileMap.end())
		{
			throw IllegalStateException("duplicate file ids");
		}

		files.push_back(file);
		fileMap.emplace(file->getFileId(), file);
	}

	std::vector<std::shared_ptr<FSFile>> ArchiveFiles::getFiles()
	{
		return Collections::unmodifiableList(files);
	}

	std::shared_ptr<FSFile> ArchiveFiles::findFile(int fileId)
	{
		return fileMap[fileId];
	}

	void ArchiveFiles::clear()
	{
		files.clear();
		fileMap.clear();
	}

	void ArchiveFiles::loadContents(std::vector<signed char> &data)
	{
		logger->trace(L"Loading contents of archive ({} files)", files.size());

		assert(!this->getFiles().empty());

		if (this->getFiles().size() == 1)
		{
			this->getFiles()[0]->setContents(data);
			return;
		}

		int filesCount = this->getFiles().size();

		std::shared_ptr<InputStream> stream = std::make_shared<InputStream>(data);
		stream->setOffset(stream->getLength() - 1);
		int chunks = stream->readUnsignedByte();

		// -1 for chunks count + one int per file slot per chunk
		stream->setOffset(stream->getLength() - 1 - chunks * filesCount * 4);
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: int[][] chunkSizes = new int[filesCount][chunks];
		std::vector<std::vector<int>> chunkSizes = RectangularVectors::RectangularIntVector(filesCount, chunks);
		std::vector<int> filesSize(filesCount);

		for (int chunk = 0; chunk < chunks; ++chunk)
		{
			int chunkSize = 0;

			for (int id = 0; id < filesCount; ++id)
			{
				int delta = stream->readInt();
				chunkSize += delta; // size of this chunk

				chunkSizes[id][chunk] = chunkSize; // store size of chunk

				filesSize[id] += chunkSize; // add chunk size to file size
			}
		}

		std::vector<std::vector<signed char>> fileContents(filesCount);
		std::vector<int> fileOffsets(filesCount);

		for (int i = 0; i < filesCount; ++i)
		{
			fileContents[i] = std::vector<signed char>(filesSize[i]);
		}

		// the file data is at the beginning of the stream
		stream->setOffset(0);

		for (int chunk = 0; chunk < chunks; ++chunk)
		{
			for (int id = 0; id < filesCount; ++id)
			{
				int chunkSize = chunkSizes[id][chunk];

				stream->readBytes(fileContents[id], fileOffsets[id], chunkSize);

				fileOffsets[id] += chunkSize;
			}
		}

		for (int i = 0; i < filesCount; ++i)
		{
			std::shared_ptr<FSFile> f = this->getFiles()[i];
			f->setContents(fileContents[i]);
		}
	}

	std::vector<signed char> ArchiveFiles::saveContents()
	{
		std::shared_ptr<OutputStream> stream = std::make_shared<OutputStream>();

		int filesCount = this->getFiles().size();

		if (filesCount == 1)
		{
			std::shared_ptr<FSFile> file = this->getFiles()[0];
			stream->writeBytes(file->getContents());
		}
		else
		{
			for (auto file : this->getFiles())
			{
				std::vector<signed char> contents = file->getContents();
				stream->writeBytes(contents);
			}

			int offset = 0;

			for (auto file : this->getFiles())
			{
				int chunkSize = file->getSize();

				int sz = chunkSize - offset;
				offset = chunkSize;
				stream->writeInt(sz);
			}

			stream->writeByte(1); // chunks
		}

		std::vector<signed char> fileData = stream->flip();

		logger->trace(L"Saved contents of archive ({} files), {} bytes", files.size(), fileData.size());
		return fileData;
	}
}
