using System;
using System.Diagnostics;
using System.Text;

namespace OSRSCache.models
{
	using TextureManager = OSRSCache.TextureManager;
	using ModelDefinition = OSRSCache.definitions.ModelDefinition;
	using TextureDefinition = OSRSCache.definitions.TextureDefinition;

	public class ObjExporter
	{
		private const double BRIGHTNESS = JagexColor.BRIGTHNESS_MIN;

		private readonly TextureManager textureManager;
		private readonly ModelDefinition model;

		public ObjExporter(TextureManager textureManager, ModelDefinition model)
		{
			this.textureManager = textureManager;
			this.model = model;
		}

		public virtual void export(StringBuilder objWriter, StringBuilder mtlWriter)
		{
			model.computeNormals();
			model.computeTextureUVCoordinates();
			
			Console.WriteLine("ObjExporter.export not implemented!");

			return;

			objWriter.Append("mtllib " + model.id + ".mtl");
			
			objWriter.Append("o runescapemodel");
			
			for (int i = 0; i < model.vertexCount; ++i)
			{
				objWriter.Append("v " + model.vertexPositionsX[i] + " " + model.vertexPositionsY[i] * -1 + " " + model.vertexPositionsZ[i] * -1);
			}
			
			if (model.faceTextures != null)
			{
				float[][] u = model.faceTextureUCoordinates;
				float[][] v = model.faceTextureVCoordinates;
			
				for (int i = 0; i < model.faceCount; ++i)
				{
					objWriter.Append("vt " + u[i][0] + " " + v[i][0]);
					objWriter.Append("vt " + u[i][1] + " " + v[i][1]);
					objWriter.Append("vt " + u[i][2] + " " + v[i][2]);
				}
			}
			
			foreach (VertexNormal normal in model.vertexNormals)
			{
				objWriter.Append("vn " + normal.x + " " + normal.y + " " + normal.z);
			}
			
			for (int i = 0; i < model.faceCount; ++i)
			{
				int x = model.faceVertexIndices1[i] + 1;
				int y = model.faceVertexIndices2[i] + 1;
				int z = model.faceVertexIndices3[i] + 1;
			
				objWriter.Append("usemtl m" + i);
				if (model.faceTextures != null)
				{
					objWriter.Append("f " + x + "/" + (i * 3 + 1) + " " + y + "/" + (i * 3 + 2) + " " + z + "/" + (i * 3 + 3));
			
				}
				else
				{
					objWriter.Append("f " + x + " " + y + " " + z);
				}
				objWriter.Append("");
			}
			
			// Write material
			for (int i = 0; i < model.faceCount; ++i)
			{
				short textureId = -1;
			
				if (model.faceTextures != null)
				{
					textureId = model.faceTextures[i];
				}
			
				mtlWriter.Append("newmtl m" + i);
			
				if (textureId == -1)
				{
					int rgb = JagexColor.HSLtoRGB(model.faceColors[i], BRIGHTNESS);
					double r = ((rgb >> 16) & 0xff) / 255.0;
					double g = ((rgb >> 8) & 0xff) / 255.0;
					double b = (rgb & 0xff) / 255.0;
			
					mtlWriter.Append("Kd " + r + " " + g + " " + b);
				}
				else
				{
					TextureDefinition texture = textureManager.findTexture(textureId);
					Debug.Assert(texture != null);
			
					mtlWriter.Append("map_Kd sprite/" + texture.fileIds[0] + "-0.png");
				}
			
				int alpha = 0;
			
				if (model.faceAlphas != null)
				{
					alpha = model.faceAlphas[i] & 0xFF;
				}
			
				if (alpha != 0)
				{
					mtlWriter.Append("d " + (alpha / 255.0));
				}
			}
		}
	}

}