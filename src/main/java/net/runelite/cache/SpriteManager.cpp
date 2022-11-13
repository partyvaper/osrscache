#include "SpriteManager.h"
#include "IndexType.h"

namespace net::runelite::cache
{
	using LinkedListMultimap = com::google::common::collect::LinkedListMultimap;
	using Multimap = com::google::common::collect::Multimap;
	using BufferedImage = java::awt::image::BufferedImage;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using Collection = java::util::Collection;
	using Collections = java::util::Collections;
	using SpriteDefinition = net::runelite::cache::definitions::SpriteDefinition;
	using SpriteExporter = net::runelite::cache::definitions::exporters::SpriteExporter;
	using SpriteLoader = net::runelite::cache::definitions::loaders::SpriteLoader;
	using SpriteProvider = net::runelite::cache::definitions::providers::SpriteProvider;
	using Archive = net::runelite::cache::fs::Archive;
	using Index = net::runelite::cache::fs::Index;
	using Storage = net::runelite::cache::fs::Storage;
	using Store = net::runelite::cache::fs::Store;

	SpriteManager::SpriteManager(std::shared_ptr<Store> store) : store(store)
	{
	}

	void SpriteManager::load()
	{
		std::shared_ptr<Storage> storage = store->getStorage();
		std::shared_ptr<Index> index = store->getIndex(IndexType::SPRITES);

		for (auto a : index->getArchives())
		{
			std::vector<signed char> contents = a->decompress(storage->loadArchive(a));

			std::shared_ptr<SpriteLoader> loader = std::make_shared<SpriteLoader>();
			std::vector<std::shared_ptr<SpriteDefinition>> defs = loader->load(a->getArchiveId(), contents);

			for (auto sprite : defs)
			{
				sprites->put(sprite->getId(), sprite);
			}
		}
	}

	std::shared_ptr<Collection<std::shared_ptr<SpriteDefinition>>> SpriteManager::getSprites()
	{
		return Collections::unmodifiableCollection(sprites->values());
	}

	std::shared_ptr<SpriteDefinition> SpriteManager::findSprite(int spriteId, int frameId)
	{
		for (std::shared_ptr<SpriteDefinition> sprite : sprites->get(spriteId))
		{
			if (sprite->getFrame() == frameId)
			{
				return sprite;
			}
		}
		return nullptr;
	}

	std::shared_ptr<BufferedImage> SpriteManager::getSpriteImage(std::shared_ptr<SpriteDefinition> sprite)
	{
		std::shared_ptr<BufferedImage> image = std::make_shared<BufferedImage>(sprite->getWidth(), sprite->getHeight(), BufferedImage::TYPE_INT_ARGB);
		image->setRGB(0, 0, sprite->getWidth(), sprite->getHeight(), sprite->getPixels(), 0, sprite->getWidth());
		return image;
	}

	void SpriteManager::export_Keyword(std::shared_ptr<File> outDir)
	{
		for (auto sprite : sprites)
		{
			// I don't know why this happens
			if (sprite->second.getHeight() <= 0 || sprite->second.getWidth() <= 0)
			{
				continue;
			}

			std::shared_ptr<SpriteExporter> exporter = std::make_shared<SpriteExporter>(sprite->second);
			std::shared_ptr<File> png = std::make_shared<File>(outDir, sprite->second.getId() + L"-" + sprite->second.getFrame() + L".png");

			exporter->exportTo(png);
		}
	}

	std::shared_ptr<SpriteDefinition> SpriteManager::provide(int spriteId, int frameId)
	{
		return findSprite(spriteId, frameId);
	}
}
