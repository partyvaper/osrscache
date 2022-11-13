#include "IndexData.h"
#include "FileData.h"

namespace net::runelite::cache::index
{
	using InputStream = net::runelite::cache::io::InputStream;
	using OutputStream = net::runelite::cache::io::OutputStream;

	void IndexData::load(std::vector<signed char> &data)
	{
		std::shared_ptr<InputStream> stream = std::make_shared<InputStream>(data);
		protocol = stream->readUnsignedByte();
		if (protocol < 5 || protocol > 7)
		{
			throw std::invalid_argument("Unsupported protocol");
		}

		if (protocol >= 6)
		{
			this->revision = stream->readInt();
		}

		int hash = stream->readUnsignedByte();
		named = (1 & hash) != 0;
		if ((hash & ~1) != 0)
		{
			throw std::invalid_argument("Unknown flags");
		}
		assert((hash & ~3) == 0);
		int validArchivesCount = protocol >= 7 ? stream->readBigSmart() : stream->readUnsignedShort();
		int lastArchiveId = 0;

		archives = std::vector<std::shared_ptr<ArchiveData>>(validArchivesCount);

		for (int index = 0; index < validArchivesCount; ++index)
		{
			int archive = lastArchiveId += protocol >= 7 ? stream->readBigSmart() : stream->readUnsignedShort();

			std::shared_ptr<ArchiveData> ad = std::make_shared<ArchiveData>();
			ad->id = archive;
			archives[index] = ad;
		}

		if (named)
		{
			for (int index = 0; index < validArchivesCount; ++index)
			{
				int nameHash = stream->readInt();
				std::shared_ptr<ArchiveData> ad = archives[index];
				ad->nameHash = nameHash;
			}
		}

		for (int index = 0; index < validArchivesCount; ++index)
		{
			int crc = stream->readInt();

			std::shared_ptr<ArchiveData> ad = archives[index];
			ad->crc = crc;
		}

		for (int index = 0; index < validArchivesCount; ++index)
		{
			int revision = stream->readInt();

			std::shared_ptr<ArchiveData> ad = archives[index];
			ad->revision = revision;
		}

		std::vector<int> numberOfFiles(validArchivesCount);
		for (int index = 0; index < validArchivesCount; ++index)
		{
			int num = protocol >= 7 ? stream->readBigSmart() : stream->readUnsignedShort();
			numberOfFiles[index] = num;
		}

		for (int index = 0; index < validArchivesCount; ++index)
		{
			std::shared_ptr<ArchiveData> ad = archives[index];
			int num = numberOfFiles[index];

			ad->files = std::vector<std::shared_ptr<FileData>>(num);

			int last = 0;
			for (int i = 0; i < num; ++i)
			{
				int fileId = last += protocol >= 7 ? stream->readBigSmart() : stream->readUnsignedShort();

				std::shared_ptr<FileData> fd = ad->files[i] = std::make_shared<FileData>();
				fd->id = fileId;
			}
		}

		if (named)
		{
			for (int index = 0; index < validArchivesCount; ++index)
			{
				std::shared_ptr<ArchiveData> ad = archives[index];
				int num = numberOfFiles[index];

				for (int i = 0; i < num; ++i)
				{
					std::shared_ptr<FileData> fd = ad->files[i];
					int name = stream->readInt();
					fd->nameHash = name;
				}
			}
		}
	}

	std::vector<signed char> IndexData::writeIndexData()
	{
		std::shared_ptr<OutputStream> stream = std::make_shared<OutputStream>();
		stream->writeByte(protocol);
		if (protocol >= 6)
		{
			stream->writeInt(this->revision);
		}

		stream->writeByte(named ? 1 : 0);
		if (protocol >= 7)
		{
			stream->writeBigSmart(this->archives.size());
		}
		else
		{
			stream->writeShort(this->archives.size());
		}

		for (int i = 0; i < this->archives.size(); ++i)
		{
			std::shared_ptr<ArchiveData> a = this->archives[i];
			int archive = a->getId();

			if (i != 0)
			{
				std::shared_ptr<ArchiveData> prev = this->archives[i - 1];
				archive -= prev->getId();
			}

			if (protocol >= 7)
			{
				stream->writeBigSmart(archive);
			}
			else
			{
				stream->writeShort(archive);
			}
		}

		if (named)
		{
			for (int i = 0; i < this->archives.size(); ++i)
			{
				std::shared_ptr<ArchiveData> a = this->archives[i];
				stream->writeInt(a->getNameHash());
			}
		}

		for (int i = 0; i < this->archives.size(); ++i)
		{
			std::shared_ptr<ArchiveData> a = this->archives[i];
			stream->writeInt(a->getCrc());
		}

		for (int i = 0; i < this->archives.size(); ++i)
		{
			std::shared_ptr<ArchiveData> a = this->archives[i];
			stream->writeInt(a->getRevision());
		}

		for (int i = 0; i < this->archives.size(); ++i)
		{
			std::shared_ptr<ArchiveData> a = this->archives[i];

			int len = a->getFiles().size();

			if (protocol >= 7)
			{
				stream->writeBigSmart(len);
			}
			else
			{
				stream->writeShort(len);
			}
		}

		for (int i = 0; i < this->archives.size(); ++i)
		{
			std::shared_ptr<ArchiveData> a = this->archives[i];

			for (int j = 0; j < a->getFiles().size(); ++j)
			{
				std::shared_ptr<FileData> file = a->getFiles()[j];
				int offset = file->getId();

				if (j != 0)
				{
					std::shared_ptr<FileData> prev = a->getFiles()[j - 1];
					offset -= prev->getId();
				}

				if (protocol >= 7)
				{
					stream->writeBigSmart(offset);
				}
				else
				{
					stream->writeShort(offset);
				}
			}
		}

		if (named)
		{
			for (int i = 0; i < this->archives.size(); ++i)
			{
				std::shared_ptr<ArchiveData> a = this->archives[i];

				for (int j = 0; j < a->getFiles().size(); ++j)
				{
					std::shared_ptr<FileData> file = a->getFiles()[j];
					stream->writeInt(file->getNameHash());
				}
			}
		}

		return stream->flip();
	}

	int IndexData::getProtocol()
	{
		return protocol;
	}

	void IndexData::setProtocol(int protocol)
	{
		this->protocol = protocol;
	}

	int IndexData::getRevision()
	{
		return revision;
	}

	void IndexData::setRevision(int revision)
	{
		this->revision = revision;
	}

	bool IndexData::isNamed()
	{
		return named;
	}

	void IndexData::setNamed(bool named)
	{
		this->named = named;
	}

	std::vector<std::shared_ptr<ArchiveData>> IndexData::getArchives()
	{
		return archives;
	}

	void IndexData::setArchives(std::vector<std::shared_ptr<ArchiveData>> &archives)
	{
		this->archives = archives;
	}
}
