#include "FSFile.h"

namespace net::runelite::cache::fs
{
	using Arrays = java::util::Arrays;

	FSFile::FSFile(int fileId) : fileId(fileId)
	{
	}

	int FSFile::hashCode()
	{
		int hash = 7;
		hash = 97 * hash + this->fileId;
		hash = 97 * hash + this->nameHash;
		hash = 97 * hash + Arrays::hashCode(this->contents);
		return hash;
	}

	bool FSFile::equals(std::any obj)
	{
		if (!obj.has_value())
		{
			return false;
		}
		if (getClass() != obj.type())
		{
			return false;
		}
		constexpr std::shared_ptr<FSFile> other = std::any_cast<std::shared_ptr<FSFile>>(obj);
		if (this->fileId != other->fileId)
		{
			return false;
		}
		if (this->nameHash != other->nameHash)
		{
			return false;
		}
		if (!Arrays::equals(this->contents, other->contents))
		{
			return false;
		}
		return true;
	}

	int FSFile::getFileId()
	{
		return fileId;
	}

	int FSFile::getNameHash()
	{
		return nameHash;
	}

	void FSFile::setNameHash(int nameHash)
	{
		this->nameHash = nameHash;
	}

	std::vector<signed char> FSFile::getContents()
	{
		return contents;
	}

	void FSFile::setContents(std::vector<signed char> &contents)
	{
		this->contents = contents;
	}

	int FSFile::getSize()
	{
		return contents.size();
	}
}
