#include "TextureManager.h"
#include "IndexType.h"

namespace net::runelite::cache
{
	using IOException = java::io::IOException;
	using ArrayList = java::util::ArrayList;
	using List = java::util::List;
	using TextureDefinition = net::runelite::cache::definitions::TextureDefinition;
	using TextureLoader = net::runelite::cache::definitions::loaders::TextureLoader;
	using TextureProvider = net::runelite::cache::definitions::providers::TextureProvider;
	using Archive = net::runelite::cache::fs::Archive;
	using ArchiveFiles = net::runelite::cache::fs::ArchiveFiles;
	using FSFile = net::runelite::cache::fs::FSFile;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;

	TextureManager::TextureManager(std::shared_ptr<Store> store) : store(store)
	{
	}

	void TextureManager::load()
	{
		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::TEXTURES);
		std::shared_ptr<Archive> archive = index->getArchive(0);

		std::vector<signed char> archiveData = storage->loadArchive(archive);
		std::shared_ptr<ArchiveFiles> files = archive->getFiles(archiveData);

		std::shared_ptr<TextureLoader> loader = std::make_shared<TextureLoader>();

		for (auto file : files->getFiles())
		{
			std::shared_ptr<TextureDefinition> texture = loader->load(file->getFileId(), file->getContents());
			textures.push_back(texture);
		}
	}

	std::vector<std::shared_ptr<TextureDefinition>> TextureManager::getTextures()
	{
		return textures;
	}

	std::shared_ptr<TextureDefinition> TextureManager::findTexture(int id)
	{
		for (auto td : textures)
		{
			if (td->getId() == id)
			{
				return td;
			}
		}
		return nullptr;
	}

	std::vector<std::shared_ptr<TextureDefinition>> TextureManager::provide()
	{
		return textures.toArray(std::vector<std::shared_ptr<TextureDefinition>>(textures.size()));
	}
}
