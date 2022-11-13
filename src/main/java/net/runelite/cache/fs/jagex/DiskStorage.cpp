#include "DiskStorage.h"
#include "IndexEntry.h"
#include "DataFileWriteResult.h"
#include "CompressionType.h"

namespace net::runelite::cache::fs::jagex
{
	using Ints = com::google::common::primitives::Ints;
	using File = java::io::File;
	using FileNotFoundException = java::io::FileNotFoundException;
	using IOException = java::io::IOException;
	using ArrayList = java::util::ArrayList;
	using List = java::util::List;
	using Archive = net::runelite::cache::fs::Archive;
	using Container = net::runelite::cache::fs::Container;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
	using ArchiveData = net::runelite::cache::index::ArchiveData;
	using IndexData = net::runelite::cache::index::IndexData;
	using Crc32 = net::runelite::cache::util::Crc32;
	using Logger = org::slf4j::Logger;
	using LoggerFactory = org::slf4j::LoggerFactory;
const std::shared_ptr<org::slf4j::Logger> DiskStorage::logger = org::slf4j::LoggerFactory::getLogger(DiskStorage::class);
const std::wstring DiskStorage::MAIN_FILE_CACHE_DAT = L"main_file_cache.dat2";
const std::wstring DiskStorage::MAIN_FILE_CACHE_IDX = L"main_file_cache.idx";

	DiskStorage::DiskStorage(std::shared_ptr<File> folder) : folder(folder), data(std::make_shared<DataFile>(std::make_shared<File>(folder, MAIN_FILE_CACHE_DAT))), index255(std::make_shared<IndexFile>(255, std::make_shared<File>(folder, MAIN_FILE_CACHE_IDX + L"255")))
	{

	}

	void DiskStorage::init(std::shared_ptr<Store> store)
	{
		for (int i = 0; i < index255->getIndexCount(); ++i)
		{
			store->addIndex(i);
			getIndex(i);
		}

		assert(store->getIndexes().size() == indexFiles.size());
	}

	void DiskStorage::close()
	{
		data->close();
		index255->close();
		for (auto indexFile : indexFiles)
		{
			indexFile->close();
		}
	}

	std::shared_ptr<IndexFile> DiskStorage::getIndex(int i)
	{
		for (auto indexFile : indexFiles)
		{
			if (indexFile->getIndexFileId() == i)
			{
				return indexFile;
			}
		}

		std::shared_ptr<IndexFile> indexFile = std::make_shared<IndexFile>(i, std::make_shared<File>(folder, MAIN_FILE_CACHE_IDX + std::to_wstring(i)));
		indexFiles.push_back(indexFile);
		return indexFile;
	}

	void DiskStorage::load(std::shared_ptr<Store> store)
	{
		for (auto index : store->getIndexes())
		{
			loadIndex(index);
		}
	}

	std::vector<signed char> DiskStorage::readIndex(int indexId)
	{
		std::shared_ptr<IndexEntry> entry = index255->read(indexId);
		if (entry == nullptr)
		{
			return std::vector<signed char>();
		}

		std::vector<signed char> indexData = data->read(index255->getIndexFileId(), entry->getId(), entry->getSector(), entry->getLength());
		return indexData;
	}

	void DiskStorage::loadIndex(std::shared_ptr<Index> index)
	{
		logger->trace(L"Loading index {}", index->getId());

		std::vector<signed char> indexData = readIndex(index->getId());
		if (indexData.empty())
		{
			return;
		}

		std::shared_ptr<Container> res = Container::decompress(indexData, std::vector<int>());
		std::vector<signed char> data = res->data;

		std::shared_ptr<IndexData> id = std::make_shared<IndexData>();
		id->load(data);

		index->setProtocol(id->getProtocol());
		index->setRevision(id->getRevision());
		index->setNamed(id->isNamed());

		for (auto ad : id->getArchives())
		{
			std::shared_ptr<Archive> archive = index->addArchive(ad->getId());
			archive->setNameHash(ad->getNameHash());
			archive->setCrc(ad->getCrc());
			archive->setRevision(ad->getRevision());
			archive->setFileData(ad->getFiles());

			assert(ad->getFiles().size() > 0);
		}

		index->setCrc(res->crc);
		index->setCompression(res->compression);
		assert(res->revision == -1);
	}

	std::vector<signed char> DiskStorage::loadArchive(std::shared_ptr<Archive> archive)
	{
		std::shared_ptr<Index> index = archive->getIndex();
		std::shared_ptr<IndexFile> indexFile = getIndex(index->getId());

		assert(indexFile->getIndexFileId() == index->getId());

		std::shared_ptr<IndexEntry> entry = indexFile->read(archive->getArchiveId());
		if (entry == nullptr)
		{
			logger->debug(L"can't read archive " + std::to_wstring(archive->getArchiveId()) + L" from index " + std::to_wstring(index->getId()));
			return std::vector<signed char>();
		}

		assert(entry->getId() == archive->getArchiveId());

		logger->trace(L"Loading archive {} for index {} from sector {} length {}", archive->getArchiveId(), index->getId(), entry->getSector(), entry->getLength());

		std::vector<signed char> archiveData = data->read(index->getId(), entry->getId(), entry->getSector(), entry->getLength());
		return archiveData;
	}

	void DiskStorage::save(std::shared_ptr<Store> store)
	{
		logger->debug(L"Saving store");

		for (auto i : store->getIndexes())
		{
			saveIndex(i);
		}
	}

	void DiskStorage::saveIndex(std::shared_ptr<Index> index)
	{
		std::shared_ptr<IndexData> indexData = index->toIndexData();
		std::vector<signed char> data = indexData->writeIndexData();

		std::shared_ptr<Container> container = std::make_shared<Container>(index->getCompression(), -1); // index data revision is always -1
		container->compress(data, std::vector<int>());
		std::vector<signed char> compressedData = container->data;
		std::shared_ptr<DataFileWriteResult> res = this->data->write(index255->getIndexFileId(), index->getId(), compressedData);

		index255->write(std::make_shared<IndexEntry>(index255, index->getId(), res->sector, res->compressedLength));

		std::shared_ptr<Crc32> crc = std::make_shared<Crc32>();
		crc->update(compressedData, 0, compressedData.size());
		index->setCrc(crc->getHash());
	}

	void DiskStorage::saveArchive(std::shared_ptr<Archive> a, std::vector<signed char> &archiveData)
	{
		std::shared_ptr<Index> index = a->getIndex();
		std::shared_ptr<IndexFile> indexFile = getIndex(index->getId());
		assert(indexFile->getIndexFileId() == index->getId());

		std::shared_ptr<DataFileWriteResult> res = data->write(index->getId(), a->getArchiveId(), archiveData);
		indexFile->write(std::make_shared<IndexEntry>(indexFile, a->getArchiveId(), res->sector, res->compressedLength));

		signed char compression = archiveData[0];
		int compressedSize = Ints::fromBytes(archiveData[1], archiveData[2], archiveData[3], archiveData[4]);

		// don't crc the appended revision, if it is there
		int length = 1 + 4 + compressedSize + (compression != CompressionType::NONE ? 4 : 0);

		std::shared_ptr<Crc32> crc = std::make_shared<Crc32>();
		crc->update(archiveData, 0, length);
		a->setCrc(crc->getHash());

		logger->trace(L"Saved archive {}/{} at sector {}, compressed length {}", index->getId(), a->getArchiveId(), res->sector, res->compressedLength);
	}
}
