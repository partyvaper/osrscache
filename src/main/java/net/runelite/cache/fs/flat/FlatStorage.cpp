#include "FlatStorage.h"

namespace net::runelite::cache::fs::flat
{
	using BufferedReader = java::io::BufferedReader;
	using File = java::io::File;
	using FileInputStream = java::io::FileInputStream;
	using FileOutputStream = java::io::FileOutputStream;
	using IOException = java::io::IOException;
	using InputStream = java::io::InputStream;
	using InputStreamReader = java::io::InputStreamReader;
	using OutputStream = java::io::OutputStream;
	using PrintStream = java::io::PrintStream;
	using StandardCharsets = java::nio::charset::StandardCharsets;
	using ArrayList = java::util::ArrayList;
	using Base64 = java::util::Base64;
	using Comparator = java::util::Comparator;
	using HashMap = java::util::HashMap;
	using List = java::util::List;
	using Map = java::util::Map;
	using Archive = net::runelite::cache::fs::Archive;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;
	using FileData = net::runelite::cache::index::FileData;
const std::wstring FlatStorage::EXTENSION = L".flatcache";

	FlatStorage::FlatStorage(std::shared_ptr<File> directory) : directory(directory)
	{
	}

	FlatStorage::FlatStorage() : directory(nullptr)
	{
	}

	std::shared_ptr<InputStream> FlatStorage::openReader(const std::wstring &filename)
	{
		return std::make_shared<FileInputStream>(std::make_shared<File>(directory, filename));
	}

	std::shared_ptr<OutputStream> FlatStorage::openWriter(const std::wstring &filename)
	{
		return std::make_shared<FileOutputStream>(std::make_shared<File>(directory, filename));
	}

	std::vector<std::wstring> FlatStorage::listFlatcacheFiles()
	{
		return directory->list([&] (dir, name)
		{
		return name->endsWith(EXTENSION);
		});
	}

	void FlatStorage::init(std::shared_ptr<Store> store)
	{
		std::vector<std::wstring> idxs = listFlatcacheFiles();
		for (auto idx : idxs)
		{
			int id = std::stoi(idx.substr(0, idx.length() - EXTENSION.length()));
			store->addIndex(id);
		}
	}

	void FlatStorage::close()
	{
	}

	void FlatStorage::load(std::shared_ptr<Store> store)
	{
		for (auto idx : store->getIndexes())
		{
			std::wstring file = std::to_wstring(idx->getId()) + EXTENSION;
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (java.io.BufferedReader br = new java.io.BufferedReader(new java.io.InputStreamReader(openReader(file), java.nio.charset.StandardCharsets.UTF_8)))
			{
				BufferedReader br = BufferedReader(std::make_shared<InputStreamReader>(openReader(file), StandardCharsets::UTF_8));
				int lineNo = 0;
				std::shared_ptr<Archive> archive = nullptr;
				std::vector<std::shared_ptr<FileData>> fileData;
				for (std::wstring line = br.readLine(); line != L""; line = br.readLine())
				{
					lineNo++;

					try
					{
						int lidx = (int)line.find(L'=');
						std::wstring key = line.substr(0, lidx);
						std::wstring value = line.substr(lidx + 1);

						if (L"file" == key)
						{
							if (fileData.empty())
							{
								fileData = std::vector<FileData>();
							}

							int vidx = (int)value.find(L'=');
							std::shared_ptr<FileData> fd = std::make_shared<FileData>();
							fd->setId(std::stoi(value.substr(0, vidx)));
							fd->setNameHash(std::stoi(value.substr(vidx + 1)));
							fileData.push_back(fd);
							continue;
						}
						else if (!fileData.empty())
						{
							archive->setFileData(fileData.toArray(std::vector<std::shared_ptr<FileData>>(0)));
							fileData = std::vector<FileData>();
						}

						if (L"id" == key)
						{
							archive = idx->addArchive(std::stoi(value));
							continue;
						}

						if (archive == nullptr)
						{
//JAVA TO C++ CONVERTER NOTE: The following 'switch' operated on a string and was converted to C++ 'if-else' logic:
//							switch (key)
//ORIGINAL LINE: case "protocol":
							if (key == L"protocol")
							{
									idx->setProtocol(std::stoi(value));
									continue;
							}
//ORIGINAL LINE: case "revision":
							else if (key == L"revision")
							{
									idx->setRevision(std::stoi(value));
									continue;
							}
//ORIGINAL LINE: case "compression":
							else if (key == L"compression")
							{
									idx->setCompression(std::stoi(value));
									continue;
							}
//ORIGINAL LINE: case "crc":
							else if (key == L"crc")
							{
									idx->setCrc(std::stoi(value));
									continue;
							}
//ORIGINAL LINE: case "named":
							else if (key == L"named")
							{
									idx->setNamed(StringHelper::fromString<bool>(value));
									continue;
							}
						}
						else
						{
//JAVA TO C++ CONVERTER NOTE: The following 'switch' operated on a string and was converted to C++ 'if-else' logic:
//							switch (key)
//ORIGINAL LINE: case "namehash":
							if (key == L"namehash")
							{
									archive->setNameHash(std::stoi(value));
									continue;
							}
//ORIGINAL LINE: case "revision":
							else if (key == L"revision")
							{
									archive->setRevision(std::stoi(value));
									continue;
							}
//ORIGINAL LINE: case "crc":
							else if (key == L"crc")
							{
									archive->setCrc(std::stoi(value));
									continue;
							}
//ORIGINAL LINE: case "hash":
							else if (key == L"hash")
							{
									archive->setHash(Base64::getDecoder().decode(value));
									continue;
							}
//ORIGINAL LINE: case "compression":
							else if (key == L"compression")
							{
									archive->setCompression(std::stoi(value));
									continue;
							}
//ORIGINAL LINE: case "contents":
							else if (key == L"contents")
							{
									data.emplace(static_cast<long long>(idx->getId()) << 32 | archive->getArchiveId(), Base64::getDecoder().decode(value));
									continue;
							}
						}
						throw IOException(StringHelper::wstring_to_string(L"unknown key: \"" + key + L"\""));
					}
					catch (const std::runtime_error &e)
					{
						throw IOException(StringHelper::wstring_to_string(L"error reading flatcache at " + file + L":" + std::to_wstring(lineNo), e));
					}
				}

				if (!fileData.empty())
				{
					archive->setFileData(fileData.toArray(std::vector<std::shared_ptr<FileData>>(0)));
					fileData = std::vector<FileData>();
				}
			}
		}
	}

	void FlatStorage::save(std::shared_ptr<Store> store)
	{
//JAVA TO C++ CONVERTER TODO TASK: Method reference arbitrary object instance method syntax is not converted by Java to C++ Converter:
		store.getIndexes().sort(java.util.Comparator.comparingInt(net.runelite.cache.fs.Index::getId));
		for (auto idx : store->getIndexes())
		{
			std::wstring file = std::to_wstring(idx->getId()) + EXTENSION;
//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (java.io.PrintStream br = new java.io.PrintStream(openWriter(file), false, java.nio.charset.StandardCharsets.UTF_8.name()))
			{
				PrintStream br = PrintStream(openWriter(file), false, StandardCharsets::UTF_8::name());
				br.printf(L"protocol=%d\n", idx->getProtocol());
				br.printf(L"revision=%d\n", idx->getRevision());
				br.printf(L"compression=%d\n", idx->getCompression());
				br.printf(L"crc=%d\n", idx->getCrc());
				br.printf(L"named=%b\n", idx->isNamed());

//JAVA TO C++ CONVERTER TODO TASK: Method reference arbitrary object instance method syntax is not converted by Java to C++ Converter:
				idx.getArchives().sort(java.util.Comparator.comparingInt(net.runelite.cache.fs.Archive::getArchiveId));
				for (auto archive : idx->getArchives())
				{
					br.printf(L"id=%d\n", archive->getArchiveId());
					br.printf(L"namehash=%d\n", archive->getNameHash());
					br.printf(L"revision=%d\n", archive->getRevision());
					br.printf(L"crc=%d\n", archive->getCrc());

					if (!archive->getHash().empty())
					{
						br.append(L"hash=");
						br.write(Base64::getEncoder().encode(archive->getHash()));
						br.append(L"\n");
					}

					std::vector<signed char> contents = store->getStorage()->loadArchive(archive);
					if (!contents.empty())
					{
						br.append(L"contents=");
						br.write(Base64::getEncoder().encode(contents));
						br.append(L"\n");
					}

					br.printf(L"compression=%d\n", archive->getCompression());
					for (auto fd : archive->getFileData())
					{
						br.printf(L"file=%d=%d\n", fd->getId(), fd->getNameHash());
					}
				}
			}
		}
	}

	std::vector<signed char> FlatStorage::loadArchive(std::shared_ptr<Archive> archive)
	{
		return data[static_cast<long long>(archive->getIndex()->getId()) << 32 | archive->getArchiveId()];
	}

	void FlatStorage::saveArchive(std::shared_ptr<Archive> archive, std::vector<signed char> &bytes)
	{
		data.emplace(static_cast<long long>(archive->getIndex()->getId()) << 32 | archive->getArchiveId(), bytes);
	}
}
