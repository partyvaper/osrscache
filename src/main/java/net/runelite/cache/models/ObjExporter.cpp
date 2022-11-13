#include "ObjExporter.h"

namespace net::runelite::cache::models
{
	using PrintWriter = java::io::PrintWriter;
	using TextureManager = net::runelite::cache::TextureManager;
	using ModelDefinition = net::runelite::cache::definitions::ModelDefinition;
	using TextureDefinition = net::runelite::cache::definitions::TextureDefinition;

	ObjExporter::ObjExporter(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<ModelDefinition> model) : textureManager(textureManager), model(model)
	{
	}

	void ObjExporter::export_Keyword(std::shared_ptr<PrintWriter> objWriter, std::shared_ptr<PrintWriter> mtlWriter)
	{
		model->computeNormals();
		model->computeTextureUVCoordinates();

		objWriter->println(L"mtllib " + std::to_wstring(model->id) + L".mtl");

		objWriter->println(L"o runescapemodel");

		for (int i = 0; i < model->vertexCount; ++i)
		{
			objWriter->println(L"v " + std::to_wstring(model->vertexX[i]) + L" " + std::to_wstring(model->vertexY[i] * -1) + L" " + model->vertexZ[i] * -1);
		}

		if (!model->faceTextures.empty())
		{
			std::vector<std::vector<float>> u = model->faceTextureUCoordinates;
			std::vector<std::vector<float>> v = model->faceTextureVCoordinates;

			for (int i = 0; i < model->faceCount; ++i)
			{
				objWriter->println(L"vt " + std::to_wstring(u[i][0]) + L" " + std::to_wstring(v[i][0]));
				objWriter->println(L"vt " + std::to_wstring(u[i][1]) + L" " + std::to_wstring(v[i][1]));
				objWriter->println(L"vt " + std::to_wstring(u[i][2]) + L" " + std::to_wstring(v[i][2]));
			}
		}

		for (auto normal : model->vertexNormals)
		{
			objWriter->println(L"vn " + std::to_wstring(normal->x) + L" " + std::to_wstring(normal->y) + L" " + std::to_wstring(normal->z));
		}

		for (int i = 0; i < model->faceCount; ++i)
		{
			int x = model->faceIndices1[i] + 1;
			int y = model->faceIndices2[i] + 1;
			int z = model->faceIndices3[i] + 1;

			objWriter->println(L"usemtl m" + std::to_wstring(i));
			if (!model->faceTextures.empty())
			{
				objWriter->println(L"f " + std::to_wstring(x) + L"/" + std::to_wstring(i * 3 + 1) + L" " + std::to_wstring(y) + L"/" + std::to_wstring(i * 3 + 2) + L" " + std::to_wstring(z) + L"/" + std::to_wstring(i * 3 + 3));

			}
			else
			{
				objWriter->println(L"f " + std::to_wstring(x) + L" " + std::to_wstring(y) + L" " + std::to_wstring(z));
			}
			objWriter->println(L"");
		}

		// Write material
		for (int i = 0; i < model->faceCount; ++i)
		{
			short textureId = -1;

			if (!model->faceTextures.empty())
			{
				textureId = model->faceTextures[i];
			}

			mtlWriter->println(L"newmtl m" + std::to_wstring(i));

			if (textureId == -1)
			{
				int rgb = JagexColor::HSLtoRGB(model->faceColors[i], BRIGHTNESS);
				double r = ((rgb >> 16) & 0xff) / 255.0;
				double g = ((rgb >> 8) & 0xff) / 255.0;
				double b = (rgb & 0xff) / 255.0;

				mtlWriter->println(L"Kd " + std::to_wstring(r) + L" " + std::to_wstring(g) + L" " + std::to_wstring(b));
			}
			else
			{
				std::shared_ptr<TextureDefinition> texture = textureManager->findTexture(textureId);
				assert(texture != nullptr);

				mtlWriter->println(L"map_Kd sprite/" + texture->getFileIds()[0] + L"-0.png");
			}

			int alpha = 0;

			if (!model->faceTransparencies.empty())
			{
				alpha = model->faceTransparencies[i] & 0xFF;
			}

			if (alpha != 0)
			{
				mtlWriter->println(L"d " + std::to_wstring(alpha / 255.0));
			}
		}
	}
}
