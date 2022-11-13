#include "ItemSpriteFactory.h"
#include "RSTextureProvider.h"
#include "Graphics3D.h"

namespace net::runelite::cache::item
{
	using BufferedImage = java::awt::image::BufferedImage;
	using IOException = java::io::IOException;
	using ItemDefinition = net::runelite::cache::definitions::ItemDefinition;
	using ModelDefinition = net::runelite::cache::definitions::ModelDefinition;
	using ItemProvider = net::runelite::cache::definitions::providers::ItemProvider;
	using ModelProvider = net::runelite::cache::definitions::providers::ModelProvider;
	using SpriteProvider = net::runelite::cache::definitions::providers::SpriteProvider;
	using TextureProvider = net::runelite::cache::definitions::providers::TextureProvider;
	using FaceNormal = net::runelite::cache::models::FaceNormal;
	using JagexColor = net::runelite::cache::models::JagexColor;
	using VertexNormal = net::runelite::cache::models::VertexNormal;

	std::shared_ptr<BufferedImage> ItemSpriteFactory::createSprite(std::shared_ptr<ItemProvider> itemProvider, std::shared_ptr<ModelProvider> modelProvider, std::shared_ptr<SpriteProvider> spriteProvider, std::shared_ptr<TextureProvider> textureProvider, int itemId, int quantity, int border, int shadowColor, bool noted)
	{
		std::shared_ptr<SpritePixels> spritePixels = createSpritePixels(itemProvider, modelProvider, spriteProvider, textureProvider, itemId, quantity, border, shadowColor, noted);
		return spritePixels == nullptr ? nullptr : spritePixels->toBufferedImage();
	}

	std::shared_ptr<SpritePixels> ItemSpriteFactory::createSpritePixels(std::shared_ptr<ItemProvider> itemProvider, std::shared_ptr<ModelProvider> modelProvider, std::shared_ptr<SpriteProvider> spriteProvider, std::shared_ptr<TextureProvider> textureProvider, int itemId, int quantity, int border, int shadowColor, bool noted)
	{
		std::shared_ptr<ItemDefinition> item = itemProvider->provide(itemId);

		if (quantity > 1 && !item->countObj.empty())
		{
			int stackItemID = -1;

			for (int i = 0; i < 10; ++i)
			{
				if (quantity >= item->countCo[i] && item->countCo[i] != 0)
				{
					stackItemID = item->countObj[i];
				}
			}

			if (stackItemID != -1)
			{
				item = itemProvider->provide(stackItemID);
			}
		}

		std::shared_ptr<Model> itemModel = getModel(modelProvider, item);
		if (itemModel == nullptr)
		{
			return nullptr;
		}

		std::shared_ptr<SpritePixels> auxSpritePixels = nullptr;
		if (item->notedTemplate != -1)
		{
			auxSpritePixels = createSpritePixels(itemProvider, modelProvider, spriteProvider, textureProvider, item->notedID, 10, 1, 0, true);
			if (auxSpritePixels == nullptr)
			{
				return nullptr;
			}
		}
		else if (item->boughtTemplateId != -1)
		{
			auxSpritePixels = createSpritePixels(itemProvider, modelProvider, spriteProvider, textureProvider, item->boughtId, quantity, border, 0, false);
			if (auxSpritePixels == nullptr)
			{
				return nullptr;
			}
		}
		else if (item->placeholderTemplateId != -1)
		{
			auxSpritePixels = createSpritePixels(itemProvider, modelProvider, spriteProvider, textureProvider, item->placeholderId, quantity, 0, 0, false);
			if (auxSpritePixels == nullptr)
			{
				return nullptr;
			}
		}

		std::shared_ptr<RSTextureProvider> rsTextureProvider = std::make_shared<RSTextureProvider>(textureProvider, spriteProvider);

		std::shared_ptr<SpritePixels> spritePixels = std::make_shared<SpritePixels>(36, 32);
		std::shared_ptr<Graphics3D> graphics = std::make_shared<Graphics3D>(rsTextureProvider);
		graphics->setBrightness(JagexColor::BRIGHTNESS_MAX);
		graphics->setRasterBuffer(spritePixels->pixels, 36, 32);
		graphics->reset();
		graphics->setRasterClipping();
		graphics->setOffset(16, 16);
		graphics->rasterGouraudLowRes = false;
		if (item->placeholderTemplateId != -1)
		{
			auxSpritePixels->drawAtOn(graphics, 0, 0);
		}

		int zoom2d = item->zoom2d;
		if (noted)
		{
			zoom2d = static_cast<int>(static_cast<double>(zoom2d) * 1.5);
		}
		else if (border == 2)
		{
			zoom2d = static_cast<int>(static_cast<double>(zoom2d) * 1.04);
		}

		int var17 = zoom2d * Graphics3D::SINE[item->xan2d] >> 16;
		int var18 = zoom2d * Graphics3D::COSINE[item->xan2d] >> 16;

		itemModel->calculateBoundsCylinder();
		itemModel->rotateAndProject(graphics, 0, item->yan2d, item->zan2d, item->xan2d, item->xOffset2d, itemModel->modelHeight / 2 + var17 + item->yOffset2d, var18 + item->yOffset2d);
		if (item->boughtTemplateId != -1)
		{
			auxSpritePixels->drawAtOn(graphics, 0, 0);
		}

		if (border >= 1)
		{
			spritePixels->drawBorder(1);
		}

		if (border >= 2)
		{
			spritePixels->drawBorder(0xffffff);
		}

		if (shadowColor != 0)
		{
			spritePixels->drawShadow(shadowColor);
		}

		graphics->setRasterBuffer(spritePixels->pixels, 36, 32);
		if (item->notedTemplate != -1)
		{
			auxSpritePixels->drawAtOn(graphics, 0, 0);
		}

		graphics->setRasterBuffer(graphics->graphicsPixels, graphics->graphicsPixelsWidth, graphics->graphicsPixelsHeight);

		graphics->setRasterClipping();
		graphics->rasterGouraudLowRes = true;
		return spritePixels;
	}

	std::shared_ptr<Model> ItemSpriteFactory::getModel(std::shared_ptr<ModelProvider> modelProvider, std::shared_ptr<ItemDefinition> item)
	{
		std::shared_ptr<Model> itemModel;
		std::shared_ptr<ModelDefinition> inventoryModel = modelProvider->provide(item->inventoryModel);
		if (inventoryModel == nullptr)
		{
			return nullptr;
		}

		if (item->resizeX != 128 || item->resizeY != 128 || item->resizeZ != 128)
		{
			inventoryModel->resize(item->resizeX, item->resizeY, item->resizeZ);
		}

		if (!item->colorFind.empty())
		{
			for (int i = 0; i < item->colorFind->size(); ++i)
			{
				inventoryModel->recolor(item->colorFind[i], item->colorReplace[i]);
			}
		}

		if (!item->textureFind.empty())
		{
			for (int i = 0; i < item->textureFind->size(); ++i)
			{
				inventoryModel->retexture(item->textureFind[i], item->textureReplace[i]);
			}
		}

		itemModel = light(inventoryModel, item->ambient + 64, item->contrast + 768, -50, -10, -50);
		itemModel->isItemModel = true;
		return itemModel;
	}

	std::shared_ptr<Model> ItemSpriteFactory::light(std::shared_ptr<ModelDefinition> def, int ambient, int contrast, int x, int y, int z)
	{
		def->computeNormals();
		int somethingMagnitude = static_cast<int>(std::sqrt(static_cast<double>(z * z + x * x + y * y)));
		int var7 = somethingMagnitude * contrast >> 8;
		std::shared_ptr<Model> litModel = std::make_shared<Model>();
		litModel->field1856 = std::vector<int>(def->faceCount);
		litModel->field1854 = std::vector<int>(def->faceCount);
		litModel->field1823 = std::vector<int>(def->faceCount);
		if (def->numTextureFaces > 0 && !def->textureCoords.empty())
		{
			std::vector<int> var9(def->numTextureFaces);

			int var10;
			for (var10 = 0; var10 < def->faceCount; ++var10)
			{
				if (def->textureCoords[var10] != -1)
				{
					++var9[def->textureCoords[var10] & 255];
				}
			}

			litModel->field1852 = 0;

			for (var10 = 0; var10 < def->numTextureFaces; ++var10)
			{
				if (var9[var10] > 0 && def->textureRenderTypes[var10] == 0)
				{
					++litModel->field1852;
				}
			}

			litModel->field1844 = std::vector<int>(litModel->field1852);
			litModel->field1865 = std::vector<int>(litModel->field1852);
			litModel->field1846 = std::vector<int>(litModel->field1852);
			var10 = 0;


			for (int i = 0; i < def->numTextureFaces; ++i)
			{
				if (var9[i] > 0 && def->textureRenderTypes[i] == 0)
				{
					litModel->field1844[var10] = def->texIndices1[i] & L'\uffff';
					litModel->field1865[var10] = def->texIndices2[i] & L'\uffff';
					litModel->field1846[var10] = def->texIndices3[i] & L'\uffff';
					var9[i] = var10++;
				}
				else
				{
					var9[i] = -1;
				}
			}

			litModel->field1840 = std::vector<signed char>(def->faceCount);

			for (int i = 0; i < def->faceCount; ++i)
			{
				if (def->textureCoords[i] != -1)
				{
					litModel->field1840[i] = static_cast<signed char>(var9[def->textureCoords[i] & 255]);
				}
				else
				{
					litModel->field1840[i] = -1;
				}
			}
		}

		for (int faceIdx = 0; faceIdx < def->faceCount; ++faceIdx)
		{
			signed char faceType;
			if (def->faceRenderTypes.empty())
			{
				faceType = 0;
			}
			else
			{
				faceType = def->faceRenderTypes[faceIdx];
			}

			signed char faceAlpha;
			if (def->faceTransparencies.empty())
			{
				faceAlpha = 0;
			}
			else
			{
				faceAlpha = def->faceTransparencies[faceIdx];
			}

			short faceTexture;
			if (def->faceTextures.empty())
			{
				faceTexture = -1;
			}
			else
			{
				faceTexture = def->faceTextures[faceIdx];
			}

			if (faceAlpha == -2)
			{
				faceType = 3;
			}

			if (faceAlpha == -1)
			{
				faceType = 2;
			}

			std::shared_ptr<VertexNormal> vertexNormal;
			int tmp;
			std::shared_ptr<FaceNormal> faceNormal;
			if (faceTexture == -1)
			{
				if (faceType != 0)
				{
					if (faceType == 1)
					{
						faceNormal = def->faceNormals[faceIdx];
						tmp = (y * faceNormal->y + z * faceNormal->z + x * faceNormal->x) / (var7 / 2 + var7) + ambient;
						litModel->field1856[faceIdx] = method2608(def->faceColors[faceIdx] & L'\uffff', tmp);
						litModel->field1823[faceIdx] = -1;
					}
					else if (faceType == 3)
					{
						litModel->field1856[faceIdx] = 128;
						litModel->field1823[faceIdx] = -1;
					}
					else
					{
						litModel->field1823[faceIdx] = -2;
					}
				}
				else
				{
					int var15 = def->faceColors[faceIdx] & L'\uffff';
					vertexNormal = def->vertexNormals[def->faceIndices1[faceIdx]];

					tmp = (y * vertexNormal->y + z * vertexNormal->z + x * vertexNormal->x) / (var7 * vertexNormal->magnitude) + ambient;
					litModel->field1856[faceIdx] = method2608(var15, tmp);
					vertexNormal = def->vertexNormals[def->faceIndices2[faceIdx]];

					tmp = (y * vertexNormal->y + z * vertexNormal->z + x * vertexNormal->x) / (var7 * vertexNormal->magnitude) + ambient;
					litModel->field1854[faceIdx] = method2608(var15, tmp);
					vertexNormal = def->vertexNormals[def->faceIndices3[faceIdx]];

					tmp = (y * vertexNormal->y + z * vertexNormal->z + x * vertexNormal->x) / (var7 * vertexNormal->magnitude) + ambient;
					litModel->field1823[faceIdx] = method2608(var15, tmp);
				}
			}
			else if (faceType != 0)
			{
				if (faceType == 1)
				{
					faceNormal = def->faceNormals[faceIdx];
					tmp = (y * faceNormal->y + z * faceNormal->z + x * faceNormal->x) / (var7 / 2 + var7) + ambient;
					litModel->field1856[faceIdx] = bound2to126(tmp);
					litModel->field1823[faceIdx] = -1;
				}
				else
				{
					litModel->field1823[faceIdx] = -2;
				}
			}
			else
			{
				vertexNormal = def->vertexNormals[def->faceIndices1[faceIdx]];

				tmp = (y * vertexNormal->y + z * vertexNormal->z + x * vertexNormal->x) / (var7 * vertexNormal->magnitude) + ambient;
				litModel->field1856[faceIdx] = bound2to126(tmp);
				vertexNormal = def->vertexNormals[def->faceIndices2[faceIdx]];

				tmp = (y * vertexNormal->y + z * vertexNormal->z + x * vertexNormal->x) / (var7 * vertexNormal->magnitude) + ambient;
				litModel->field1854[faceIdx] = bound2to126(tmp);
				vertexNormal = def->vertexNormals[def->faceIndices3[faceIdx]];

				tmp = (y * vertexNormal->y + z * vertexNormal->z + x * vertexNormal->x) / (var7 * vertexNormal->magnitude) + ambient;
				litModel->field1823[faceIdx] = bound2to126(tmp);
			}
		}

		litModel->verticesCount = def->vertexCount;
		litModel->verticesX = def->vertexX;
		litModel->verticesY = def->vertexY;
		litModel->verticesZ = def->vertexZ;
		litModel->indicesCount = def->faceCount;
		litModel->indices1 = def->faceIndices1;
		litModel->indices2 = def->faceIndices2;
		litModel->indices3 = def->faceIndices3;
		litModel->field1838 = def->faceRenderPriorities;
		litModel->field1882 = def->faceTransparencies;
		litModel->field1842 = def->priority;
		litModel->field1841 = def->faceTextures;
		return litModel;
	}

	int ItemSpriteFactory::method2608(int var0, int var1)
	{
		var1 = ((var0 & 127) * var1) >> 7;
		var1 = bound2to126(var1);

		return (var0 & 65408) + var1;
	}

	int ItemSpriteFactory::bound2to126(int var0)
	{
		if (var0 < 2)
		{
			var0 = 2;
		}
		else if (var0 > 126)
		{
			var0 = 126;
		}

		return var0;
	}
}
