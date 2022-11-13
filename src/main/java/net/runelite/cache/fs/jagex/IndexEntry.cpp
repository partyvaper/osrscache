#include "IndexEntry.h"

namespace net::runelite::cache::fs::jagex
{
	using Objects = java::util::Objects;

	IndexEntry::IndexEntry(std::shared_ptr<IndexFile> indexFile, int id, int sector, int length) : indexFile(indexFile), id(id), sector(sector), length(length)
	{
	}

	std::shared_ptr<IndexFile> IndexEntry::getIndexFile()
	{
		return indexFile;
	}

	int IndexEntry::getId()
	{
		return id;
	}

	int IndexEntry::getSector()
	{
		return sector;
	}

	int IndexEntry::getLength()
	{
		return length;
	}

	int IndexEntry::hashCode()
	{
		int hash = 7;
		hash = 19 * hash + Objects::hashCode(this->indexFile);
		hash = 19 * hash + this->id;
		hash = 19 * hash + this->sector;
		hash = 19 * hash + this->length;
		return hash;
	}

	bool IndexEntry::equals(std::any obj)
	{
		if (!obj.has_value())
		{
			return false;
		}
		if (getClass() != obj.type())
		{
			return false;
		}
		constexpr std::shared_ptr<IndexEntry> other = std::any_cast<std::shared_ptr<IndexEntry>>(obj);
		if (!Objects::equals(this->indexFile, other->indexFile))
		{
			return false;
		}
		if (this->id != other->id)
		{
			return false;
		}
		if (this->sector != other->sector)
		{
			return false;
		}
		if (this->length != other->length)
		{
			return false;
		}
		return true;
	}
}
