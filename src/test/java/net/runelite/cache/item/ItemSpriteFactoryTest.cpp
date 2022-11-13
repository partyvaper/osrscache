#include "ItemSpriteFactoryTest.h"
#include "../../../../../../main/java/net/runelite/cache/item/ItemSpriteFactory.h"

namespace net::runelite::cache::item
{
	using BufferedImage = java::awt::image::BufferedImage;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using ImageIO = javax::imageio::ImageIO;
	using Slf4j = lombok::extern_Keyword::slf4j::Slf4j;
	using IndexType = net::runelite::cache::IndexType;
	using ItemManager = net::runelite::cache::ItemManager;
	using SpriteManager = net::runelite::cache::SpriteManager;
	using StoreLocation = net::runelite::cache::StoreLocation;
	using TextureManager = net::runelite::cache::TextureManager;
	using ItemDefinition = net::runelite::cache::definitions::ItemDefinition;
	using ModelDefinition = net::runelite::cache::definitions::ModelDefinition;
	using ModelLoader = net::runelite::cache::definitions::loaders::ModelLoader;
	using ModelProvider = net::runelite::cache::definitions::providers::ModelProvider;
	using Archive = net::runelite::cache::fs::Archive;
	using Index = net::runelite::cache::fs::Index;
	using Store = net::runelite::cache::fs::Store;
	using Ignore = org::junit::Ignore;
	using Rule = org::junit::Rule;
	using Test = org::junit::Test;
	using TemporaryFolder = org::junit::rules::TemporaryFolder;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Test @Ignore public void test() throws java.io.IOException
	void ItemSpriteFactoryTest::test()
	{
		std::shared_ptr<File> __super = StoreLocation::LOCATION, outDir = folder->newFolder();

		int count = 0;

//JAVA TO C++ CONVERTER NOTE: The following 'try with resources' block is replaced by its C++ equivalent:
//ORIGINAL LINE: try (net.runelite.cache.fs.Store store = new net.runelite.cache.fs.Store(super))
		{
			Store store = Store(base);
			store.load();

			std::shared_ptr<ItemManager> itemManager = std::make_shared<ItemManager>(store);
			itemManager->load();
			itemManager->link();

			std::shared_ptr<ModelProvider> modelProvider = std::make_shared<ModelProviderAnonymousInnerClass>(shared_from_this(), store);

			std::shared_ptr<SpriteManager> spriteManager = std::make_shared<SpriteManager>(store);
			spriteManager->load();

			std::shared_ptr<TextureManager> textureManager = std::make_shared<TextureManager>(store);
			textureManager->load();

			for (auto itemDef : itemManager->getItems())
			{
//JAVA TO C++ CONVERTER TODO TASK: The following Java case-insensitive String method call is not converted:
				if (itemDef->name == L"" || itemDef->name.equalsIgnoreCase(L"null"))
				{
					continue;
				}

				try
				{
					std::shared_ptr<BufferedImage> sprite = ItemSpriteFactory::createSprite(itemManager, modelProvider, spriteManager, textureManager, itemDef->id, 1, 1, 3153952, false);

					std::shared_ptr<File> out = std::make_shared<File>(outDir, std::to_wstring(itemDef->id) + L".png");
					std::shared_ptr<BufferedImage> img = sprite;
					ImageIO::write(img, L"PNG", out);

					++count;
				}
				catch (const std::runtime_error &ex)
				{
					log::warn(L"error dumping item {}", itemDef->id, ex);
				}
			}
		}

		log::info(L"Dumped {} item images to {}", count, outDir);
	}

	ItemSpriteFactoryTest::ModelProviderAnonymousInnerClass::ModelProviderAnonymousInnerClass(std::shared_ptr<ItemSpriteFactoryTest> outerInstance, std::shared_ptr<Store> store) : outerInstance(outerInstance)
	{
		this->store = store;
	}

	std::shared_ptr<ModelDefinition> ItemSpriteFactoryTest::ModelProviderAnonymousInnerClass::provide(int modelId)
	{
		std::shared_ptr<Index> models = store->getIndex(IndexType::MODELS);
		std::shared_ptr<Archive> archive = models->getArchive(modelId);

		std::vector<signed char> data = archive->decompress(store->getStorage()->loadArchive(archive));
		std::shared_ptr<ModelDefinition> inventoryModel = (std::make_shared<ModelLoader>())->load(modelId, data);
		return inventoryModel;
	}
}
