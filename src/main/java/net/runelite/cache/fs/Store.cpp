#include "Store.h"

namespace net::runelite::cache::fs
{
	using Closeable = Closeable;
	using File = java::io::File;
	using FileNotFoundException = java::io::FileNotFoundException;
	using IOException = java::io::IOException;
	using ArrayList = java::util::ArrayList;
	using List = java::util::List;
	using Objects = java::util::Objects;
	using IndexType = net::runelite::cache::IndexType;
	using DiskStorage = net::runelite::cache::fs::jagex::DiskStorage;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> Store::logger = org::slf4j::LoggerFactory::getLogger(Store::class);

	Store::Store(std::shared_ptr<File> folder) : storage(std::make_shared<DiskStorage>(folder))
	{
//JAVA TO C++ CONVERTER TODO TASK: You cannot use 'shared_from_this' in a constructor:
		storage->init(shared_from_this());
	}

	Store::Store(std::shared_ptr<Storage> storage) : storage(storage)
	{

//JAVA TO C++ CONVERTER TODO TASK: You cannot use 'shared_from_this' in a constructor:
		storage->init(shared_from_this());
	}

	std::shared_ptr<Storage> Store::getStorage()
	{
		return storage;
	}

	void Store::close()
	{
		storage->close();
	}

	int Store::hashCode()
	{
		int hash = 5;
		hash = 79 * hash + Objects::hashCode(this->indexes);
		return hash;
	}

	bool Store::equals(std::any obj)
	{
		if (!obj.has_value())
		{
			return false;
		}
		if (getClass() != obj.type())
		{
			return false;
		}
		constexpr std::shared_ptr<Store> other = std::any_cast<std::shared_ptr<Store>>(obj);
		if (!Objects::equals(this->indexes, other->indexes))
		{
			return false;
		}
		return true;
	}

	std::shared_ptr<Index> Store::addIndex(int id)
	{
		for (auto i : indexes)
		{
			if (i->getId() == id)
			{
				throw std::invalid_argument(StringHelper::wstring_to_string(L"index " + std::to_wstring(id) + L" already exists"));
			}
		}

		std::shared_ptr<Index> index = std::make_shared<Index>(id);
		this->indexes.push_back(index);

		return index;
	}

	void Store::removeIndex(std::shared_ptr<Index> index)
	{
		assert(std::find(indexes.begin(), indexes.end(), index) != indexes.end());
//JAVA TO C++ CONVERTER TODO TASK: The Java Collection 'remove(Object)' method is not converted:
		indexes.remove(index);
	}

	void Store::load()
	{
		storage->load(shared_from_this());
	}

	void Store::save()
	{
		storage->save(shared_from_this());
	}

	std::vector<std::shared_ptr<Index>> Store::getIndexes()
	{
		return indexes;
	}

	std::shared_ptr<Index> Store::getIndex(IndexType type)
	{
		return findIndex(type.getNumber());
	}

	std::shared_ptr<Index> Store::findIndex(int id)
	{
		for (auto i : indexes)
		{
			if (i->getId() == id)
			{
				return i;
			}
		}
		return nullptr;
	}
}
