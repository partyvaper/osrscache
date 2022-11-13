#include "Archive.h"
#include "Container.h"
#include "FSFile.h"

namespace net::runelite::cache::fs
{
	using IOException = java::io::IOException;
	using FileData = net::runelite::cache::index::FileData;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> Archive::logger = org::slf4j::LoggerFactory::getLogger(Archive::class);

	Archive::Archive(std::shared_ptr<Index> index, int id) : index(index), archiveId(id)
	{
	}

	int Archive::hashCode()
	{
		int hash = 7;
		hash = 47 * hash + this->archiveId;
		hash = 47 * hash + this->nameHash;
		hash = 47 * hash + this->revision;
		return hash;
	}

	bool Archive::equals(std::any obj)
	{
		if (!obj.has_value())
		{
			return false;
		}
		if (getClass() != obj.type())
		{
			return false;
		}
		constexpr std::shared_ptr<Archive> other = std::any_cast<std::shared_ptr<Archive>>(obj);
		if (this->archiveId != other->archiveId)
		{
			return false;
		}
		if (this->nameHash != other->nameHash)
		{
			return false;
		}
		if (this->revision != other->revision)
		{
			return false;
		}
		return true;
	}

	std::shared_ptr<Index> Archive::getIndex()
	{
		return index;
	}

	std::vector<signed char> Archive::decompress(std::vector<signed char> &data)
	{
		return decompress(data, std::vector<int>());
	}

	std::vector<signed char> Archive::decompress(std::vector<signed char> &data, std::vector<int> &keys)
	{
		if (data.empty())
		{
			return std::vector<signed char>();
		}

		std::vector<signed char> encryptedData = data;

		std::shared_ptr<Container> container = Container::decompress(encryptedData, keys);
		if (container == nullptr)
		{
			logger->warn(L"Unable to decrypt archive {}", shared_from_this());
			return std::vector<signed char>();
		}

		std::vector<signed char> decompressedData = container->data;

		if (this->crc != container->crc)
		{
			logger->warn(L"crc mismatch for archive {}/{}", index->getId(), this->getArchiveId());
			throw IOException(StringHelper::wstring_to_string(L"CRC mismatch for " + std::to_wstring(index->getId()) + L"/" + std::to_wstring(this->getArchiveId())));
		}

		if (container->revision != -1 && this->getRevision() != container->revision)
		{
			// compressed data doesn't always include a revision, but check it if it does
			logger->warn(L"revision mismatch for archive {}/{}, expected {} was {}", index->getId(), this->getArchiveId(), this->getRevision(), container->revision);
			// I've seen this happen with vanilla caches where the
			// revision in the index data differs from the revision
			// stored for the archive data on disk... I assume this
			// is more correct
			this->setRevision(container->revision);
		}

		setCompression(container->compression);
		return decompressedData;
	}

	std::shared_ptr<ArchiveFiles> Archive::getFiles(std::vector<signed char> &data)
	{
		return getFiles(data, std::vector<int>());
	}

	std::shared_ptr<ArchiveFiles> Archive::getFiles(std::vector<signed char> &data, std::vector<int> &keys)
	{
		std::vector<signed char> decompressedData = decompress(data, keys);

		std::shared_ptr<ArchiveFiles> files = std::make_shared<ArchiveFiles>();
		for (auto fileEntry : fileData)
		{
			std::shared_ptr<FSFile> file = std::make_shared<FSFile>(fileEntry->getId());
			file->setNameHash(fileEntry->getNameHash());
			files->addFile(file);
		}
		files->loadContents(decompressedData);
		return files;
	}

	int Archive::getArchiveId()
	{
		return archiveId;
	}

	int Archive::getNameHash()
	{
		return nameHash;
	}

	void Archive::setNameHash(int nameHash)
	{
		this->nameHash = nameHash;
	}

	int Archive::getCrc()
	{
		return crc;
	}

	void Archive::setCrc(int crc)
	{
		this->crc = crc;
	}

	int Archive::getRevision()
	{
		return revision;
	}

	void Archive::setRevision(int revision)
	{
		this->revision = revision;
	}

	int Archive::getCompression()
	{
		return compression;
	}

	void Archive::setCompression(int compression)
	{
		this->compression = compression;
	}

	std::vector<std::shared_ptr<FileData>> Archive::getFileData()
	{
		return fileData;
	}

	void Archive::setFileData(std::vector<std::shared_ptr<FileData>> &fileData)
	{
		this->fileData = fileData;
	}

	std::vector<signed char> Archive::getHash()
	{
		return hash;
	}

	void Archive::setHash(std::vector<signed char> &hash)
	{
		this->hash = hash;
	}
}
