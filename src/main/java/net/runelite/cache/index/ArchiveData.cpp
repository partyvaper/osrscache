#include "ArchiveData.h"

namespace net::runelite::cache::index
{

	int ArchiveData::getId()
	{
		return id;
	}

	void ArchiveData::setId(int id)
	{
		this->id = id;
	}

	int ArchiveData::getNameHash()
	{
		return nameHash;
	}

	void ArchiveData::setNameHash(int nameHash)
	{
		this->nameHash = nameHash;
	}

	int ArchiveData::getCrc()
	{
		return crc;
	}

	void ArchiveData::setCrc(int crc)
	{
		this->crc = crc;
	}

	int ArchiveData::getRevision()
	{
		return revision;
	}

	void ArchiveData::setRevision(int revision)
	{
		this->revision = revision;
	}

	std::vector<std::shared_ptr<FileData>> ArchiveData::getFiles()
	{
		return files;
	}

	void ArchiveData::setFiles(std::vector<std::shared_ptr<FileData>> &files)
	{
		this->files = files;
	}
}
