#include "FileData.h"

namespace net::runelite::cache::index
{

	int FileData::getId()
	{
		return id;
	}

	void FileData::setId(int id)
	{
		this->id = id;
	}

	int FileData::getNameHash()
	{
		return nameHash;
	}

	void FileData::setNameHash(int nameHash)
	{
		this->nameHash = nameHash;
	}
}
