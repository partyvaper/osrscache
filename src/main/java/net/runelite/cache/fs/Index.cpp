#include "Index.h"

namespace net::runelite::cache::fs
{
	using ArrayList = java::util::ArrayList;
	using List = java::util::List;
	using Objects = java::util::Objects;
	using ArchiveData = net::runelite::cache::index::ArchiveData;
	using FileData = net::runelite::cache::index::FileData;
	using IndexData = net::runelite::cache::index::IndexData;
	using Djb2 = net::runelite::cache::util::Djb2;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> Index::logger = org::slf4j::LoggerFactory::getLogger(Index::class);

	Index::Index(int id) : id(id)
	{
	}

	int Index::hashCode()
	{
		int hash = 3;
		hash = 97 * hash + this->id;
		hash = 97 * hash + this->revision;
		hash = 97 * hash + Objects::hashCode(this->archives);
		return hash;
	}

	bool Index::equals(std::any obj)
	{
		if (!obj.has_value())
		{
			return false;
		}
		if (getClass() != obj.type())
		{
			return false;
		}
		constexpr std::shared_ptr<Index> other = std::any_cast<std::shared_ptr<Index>>(obj);
		if (this->id != other->id)
		{
			return false;
		}
		if (this->revision != other->revision)
		{
			return false;
		}
		if (!Objects::equals(this->archives, other->archives))
		{
			return false;
		}
		return true;
	}

	int Index::getId()
	{
		return id;
	}

	int Index::getProtocol()
	{
		return protocol;
	}

	void Index::setProtocol(int protocol)
	{
		this->protocol = protocol;
	}

	bool Index::isNamed()
	{
		return named;
	}

	void Index::setNamed(bool named)
	{
		this->named = named;
	}

	int Index::getRevision()
	{
		return revision;
	}

	void Index::setRevision(int revision)
	{
		this->revision = revision;
	}

	int Index::getCrc()
	{
		return crc;
	}

	void Index::setCrc(int crc)
	{
		this->crc = crc;
	}

	int Index::getCompression()
	{
		return compression;
	}

	void Index::setCompression(int compression)
	{
		this->compression = compression;
	}

	std::vector<std::shared_ptr<Archive>> Index::getArchives()
	{
		return archives;
	}

	std::shared_ptr<Archive> Index::addArchive(int id)
	{
		std::shared_ptr<Archive> archive = std::make_shared<Archive>(shared_from_this(), id);
		this->archives.push_back(archive);
		return archive;
	}

	std::shared_ptr<Archive> Index::getArchive(int id)
	{
		for (auto a : archives)
		{
			if (a->getArchiveId() == id)
			{
				return a;
			}
		}
		return nullptr;
	}

	std::shared_ptr<Archive> Index::findArchiveByName(const std::wstring &name)
	{
		int hash = Djb2::hash(name);
		for (auto a : archives)
		{
			if (a->getNameHash() == hash)
			{
				return a;
			}
		}
		return nullptr;
	}

	std::shared_ptr<IndexData> Index::toIndexData()
	{
		std::shared_ptr<IndexData> data = std::make_shared<IndexData>();
		data->setProtocol(protocol);
		data->setRevision(revision);
		data->setNamed(named);

		std::vector<std::shared_ptr<ArchiveData>> archiveDatas(archives.size());
		data->setArchives(archiveDatas);

		int idx = 0;
		for (auto archive : archives)
		{
			std::shared_ptr<ArchiveData> ad = archiveDatas[idx++] = std::make_shared<ArchiveData>();
			ad->setId(archive->getArchiveId());
			ad->setNameHash(archive->getNameHash());
			ad->setCrc(archive->getCrc());
			ad->setRevision(archive->getRevision());

			std::vector<std::shared_ptr<FileData>> files = archive->getFileData();
			ad->setFiles(files);
		}
		return data;
	}
}
