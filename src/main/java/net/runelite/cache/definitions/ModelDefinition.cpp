#include "ModelDefinition.h"

namespace net::runelite::cache::definitions
{
	using Arrays = java::util::Arrays;
	using Data = lombok::Data;
	using CircularAngle = net::runelite::cache::models::CircularAngle;
	using FaceNormal = net::runelite::cache::models::FaceNormal;
	using VertexNormal = net::runelite::cache::models::VertexNormal;
int ModelDefinition::animOffsetX = 0;
int ModelDefinition::animOffsetY = 0;
int ModelDefinition::animOffsetZ = 0;

	void ModelDefinition::computeNormals()
	{
		if (!this->vertexNormals.empty())
		{
			return;
		}

		this->vertexNormals = std::vector<std::shared_ptr<VertexNormal>>(this->vertexCount);

		int var1;
		for (var1 = 0; var1 < this->vertexCount; ++var1)
		{
			this->vertexNormals[var1] = std::make_shared<VertexNormal>();
		}

		for (var1 = 0; var1 < this->faceCount; ++var1)
		{
			int vertexA = this->faceIndices1[var1];
			int vertexB = this->faceIndices2[var1];
			int vertexC = this->faceIndices3[var1];

			int xA = this->vertexX[vertexB] - this->vertexX[vertexA];
			int yA = this->vertexY[vertexB] - this->vertexY[vertexA];
			int zA = this->vertexZ[vertexB] - this->vertexZ[vertexA];

			int xB = this->vertexX[vertexC] - this->vertexX[vertexA];
			int yB = this->vertexY[vertexC] - this->vertexY[vertexA];
			int zB = this->vertexZ[vertexC] - this->vertexZ[vertexA];

			// Compute cross product
			int var11 = yA * zB - yB * zA;
			int var12 = zA * xB - zB * xA;
			int var13 = xA * yB - xB * yA;

			while (var11 > 8192 || var12 > 8192 || var13 > 8192 || var11 < -8192 || var12 < -8192 || var13 < -8192)
			{
				var11 >>= 1;
				var12 >>= 1;
				var13 >>= 1;
			}

			int length = static_cast<int>(std::sqrt(static_cast<double>(var11 * var11 + var12 * var12 + var13 * var13)));
			if (length <= 0)
			{
				length = 1;
			}

			var11 = var11 * 256 / length;
			var12 = var12 * 256 / length;
			var13 = var13 * 256 / length;

			signed char var15;
			if (this->faceRenderTypes.empty())
			{
				var15 = 0;
			}
			else
			{
				var15 = this->faceRenderTypes[var1];
			}

			if (var15 == 0)
			{
				std::shared_ptr<VertexNormal> var16 = this->vertexNormals[vertexA];
				var16->x += var11;
				var16->y += var12;
				var16->z += var13;
				++var16->magnitude;

				var16 = this->vertexNormals[vertexB];
				var16->x += var11;
				var16->y += var12;
				var16->z += var13;
				++var16->magnitude;

				var16 = this->vertexNormals[vertexC];
				var16->x += var11;
				var16->y += var12;
				var16->z += var13;
				++var16->magnitude;
			}
			else if (var15 == 1)
			{
				if (this->faceNormals.empty())
				{
					this->faceNormals = std::vector<std::shared_ptr<FaceNormal>>(this->faceCount);
				}

				std::shared_ptr<FaceNormal> var17 = this->faceNormals[var1] = std::make_shared<FaceNormal>();
				var17->x = var11;
				var17->y = var12;
				var17->z = var13;
			}
		}
	}

	void ModelDefinition::computeTextureUVCoordinates()
	{
		this->faceTextureUCoordinates = std::vector<std::vector<float>>(faceCount);
		this->faceTextureVCoordinates = std::vector<std::vector<float>>(faceCount);

		for (int i = 0; i < faceCount; i++)
		{
			int textureCoordinate;
			if (textureCoords.empty())
			{
				textureCoordinate = -1;
			}
			else
			{
				textureCoordinate = textureCoords[i];
			}

			int textureIdx;
			if (faceTextures.empty())
			{
				textureIdx = -1;
			}
			else
			{
				textureIdx = faceTextures[i] & 0xFFFF;
			}

			if (textureIdx != -1)
			{
				std::vector<float> u(3);
				std::vector<float> v(3);

				if (textureCoordinate == -1)
				{
					u[0] = 0.0F;
					v[0] = 1.0F;

					u[1] = 1.0F;
					v[1] = 1.0F;

					u[2] = 0.0F;
					v[2] = 0.0F;
				}
				else
				{
					textureCoordinate &= 0xFF;

					signed char textureRenderType = 0;
					if (!textureRenderTypes.empty())
					{
						textureRenderType = textureRenderTypes[textureCoordinate];
					}

					if (textureRenderType == 0)
					{
						int faceVertexIdx1 = faceIndices1[i];
						int faceVertexIdx2 = faceIndices2[i];
						int faceVertexIdx3 = faceIndices3[i];

						short triangleVertexIdx1 = texIndices1[textureCoordinate];
						short triangleVertexIdx2 = texIndices2[textureCoordinate];
						short triangleVertexIdx3 = texIndices3[textureCoordinate];

						float triangleX = static_cast<float>(vertexX[triangleVertexIdx1]);
						float triangleY = static_cast<float>(vertexY[triangleVertexIdx1]);
						float triangleZ = static_cast<float>(vertexZ[triangleVertexIdx1]);

						float f_882_ = static_cast<float>(vertexX[triangleVertexIdx2]) - triangleX;
						float f_883_ = static_cast<float>(vertexY[triangleVertexIdx2]) - triangleY;
						float f_884_ = static_cast<float>(vertexZ[triangleVertexIdx2]) - triangleZ;
						float f_885_ = static_cast<float>(vertexX[triangleVertexIdx3]) - triangleX;
						float f_886_ = static_cast<float>(vertexY[triangleVertexIdx3]) - triangleY;
						float f_887_ = static_cast<float>(vertexZ[triangleVertexIdx3]) - triangleZ;
						float f_888_ = static_cast<float>(vertexX[faceVertexIdx1]) - triangleX;
						float f_889_ = static_cast<float>(vertexY[faceVertexIdx1]) - triangleY;
						float f_890_ = static_cast<float>(vertexZ[faceVertexIdx1]) - triangleZ;
						float f_891_ = static_cast<float>(vertexX[faceVertexIdx2]) - triangleX;
						float f_892_ = static_cast<float>(vertexY[faceVertexIdx2]) - triangleY;
						float f_893_ = static_cast<float>(vertexZ[faceVertexIdx2]) - triangleZ;
						float f_894_ = static_cast<float>(vertexX[faceVertexIdx3]) - triangleX;
						float f_895_ = static_cast<float>(vertexY[faceVertexIdx3]) - triangleY;
						float f_896_ = static_cast<float>(vertexZ[faceVertexIdx3]) - triangleZ;

						float f_897_ = f_883_ * f_887_ - f_884_ * f_886_;
						float f_898_ = f_884_ * f_885_ - f_882_ * f_887_;
						float f_899_ = f_882_ * f_886_ - f_883_ * f_885_;
						float f_900_ = f_886_ * f_899_ - f_887_ * f_898_;
						float f_901_ = f_887_ * f_897_ - f_885_ * f_899_;
						float f_902_ = f_885_ * f_898_ - f_886_ * f_897_;
						float f_903_ = 1.0F / (f_900_ * f_882_ + f_901_ * f_883_ + f_902_ * f_884_);

						u[0] = (f_900_ * f_888_ + f_901_ * f_889_ + f_902_ * f_890_) * f_903_;
						u[1] = (f_900_ * f_891_ + f_901_ * f_892_ + f_902_ * f_893_) * f_903_;
						u[2] = (f_900_ * f_894_ + f_901_ * f_895_ + f_902_ * f_896_) * f_903_;

						f_900_ = f_883_ * f_899_ - f_884_ * f_898_;
						f_901_ = f_884_ * f_897_ - f_882_ * f_899_;
						f_902_ = f_882_ * f_898_ - f_883_ * f_897_;
						f_903_ = 1.0F / (f_900_ * f_885_ + f_901_ * f_886_ + f_902_ * f_887_);

						v[0] = (f_900_ * f_888_ + f_901_ * f_889_ + f_902_ * f_890_) * f_903_;
						v[1] = (f_900_ * f_891_ + f_901_ * f_892_ + f_902_ * f_893_) * f_903_;
						v[2] = (f_900_ * f_894_ + f_901_ * f_895_ + f_902_ * f_896_) * f_903_;
					}
				}

				this->faceTextureUCoordinates[i] = u;
				this->faceTextureVCoordinates[i] = v;
			}
		}
	}

	void ModelDefinition::computeAnimationTables()
	{
		if (!this->packedVertexGroups.empty())
		{
			std::vector<int> groupCounts(256);
			int numGroups = 0;
			int var3, var4;

			for (var3 = 0; var3 < this->vertexCount; ++var3)
			{
				var4 = this->packedVertexGroups[var3];
				++groupCounts[var4];
				if (var4 > numGroups)
				{
					numGroups = var4;
				}
			}

			this->vertexGroups = std::vector<std::vector<int>>(numGroups + 1);

			for (var3 = 0; var3 <= numGroups; ++var3)
			{
				this->vertexGroups[var3] = std::vector<int>(groupCounts[var3]);
				groupCounts[var3] = 0;
			}

			for (var3 = 0; var3 < this->vertexCount; this->vertexGroups[var4][groupCounts[var4]++] = var3++)
			{
				var4 = this->packedVertexGroups[var3];
			}

			this->packedVertexGroups = std::vector<int>();
		}

		// triangleSkinValues is here
	}

	void ModelDefinition::rotate(int orientation)
	{
		int sin = CircularAngle::SINE[orientation];
		int cos = CircularAngle::COSINE[orientation];

		assert(vertexX.size() == vertexY.size());
		assert(vertexY.size() == vertexZ.size());

		for (int i = 0; i < vertexX.size(); ++i)
		{
			vertexX[i] = vertexX[i] * cos + vertexZ[i] * sin >> 16;
			vertexZ[i] = vertexZ[i] * cos - vertexX[i] * sin >> 16;
		}

		reset();
	}

	void ModelDefinition::resetAnim()
	{
		if (origVX.empty())
		{
			return;
		}

		std::copy_n(origVX.begin(), origVX.size(), vertexX.begin());
		std::copy_n(origVY.begin(), origVY.size(), vertexY.begin());
		std::copy_n(origVZ.begin(), origVZ.size(), vertexZ.begin());
	}

	void ModelDefinition::animate(int type, std::vector<int> &frameMap, int dx, int dy, int dz)
	{
		if (origVX.empty())
		{
			origVX = Arrays::copyOf(vertexX, vertexX.size());
			origVY = Arrays::copyOf(vertexY, vertexY.size());
			origVZ = Arrays::copyOf(vertexZ, vertexZ.size());
		}

		const std::vector<int> verticesX = vertexX;
		const std::vector<int> verticesY = vertexY;
		const std::vector<int> verticesZ = vertexZ;
		int var6 = frameMap.size();
		int var7;
		int var8;
		int var11;
		int var12;
		if (type == 0)
		{
			var7 = 0;
			animOffsetX = 0;
			animOffsetY = 0;
			animOffsetZ = 0;

			for (var8 = 0; var8 < var6; ++var8)
			{
				int var9 = frameMap[var8];
				if (var9 < this->vertexGroups.size())
				{
					std::vector<int> var10 = this->vertexGroups[var9];

					for (var11 = 0; var11 < var10.size(); ++var11)
					{
						var12 = var10[var11];
						animOffsetX += verticesX[var12];
						animOffsetY += verticesY[var12];
						animOffsetZ += verticesZ[var12];
						++var7;
					}
				}
			}

			if (var7 > 0)
			{
				animOffsetX = dx + animOffsetX / var7;
				animOffsetY = dy + animOffsetY / var7;
				animOffsetZ = dz + animOffsetZ / var7;
			}
			else
			{
				animOffsetX = dx;
				animOffsetY = dy;
				animOffsetZ = dz;
			}

		}
		else
		{
			std::vector<int> var18;
			int var19;
			if (type == 1)
			{
				for (var7 = 0; var7 < var6; ++var7)
				{
					var8 = frameMap[var7];
					if (var8 < this->vertexGroups.size())
					{
						var18 = this->vertexGroups[var8];

						for (var19 = 0; var19 < var18.size(); ++var19)
						{
							var11 = var18[var19];
							verticesX[var11] += dx;
							verticesY[var11] += dy;
							verticesZ[var11] += dz;
						}
					}
				}

			}
			else if (type == 2)
			{
				for (var7 = 0; var7 < var6; ++var7)
				{
					var8 = frameMap[var7];
					if (var8 < this->vertexGroups.size())
					{
						var18 = this->vertexGroups[var8];

						for (var19 = 0; var19 < var18.size(); ++var19)
						{
							var11 = var18[var19];
							verticesX[var11] -= animOffsetX;
							verticesY[var11] -= animOffsetY;
							verticesZ[var11] -= animOffsetZ;
							var12 = (dx & 255) * 8;
							int var13 = (dy & 255) * 8;
							int var14 = (dz & 255) * 8;
							int var15;
							int var16;
							int var17;
							if (var14 != 0)
							{
								var15 = CircularAngle::SINE[var14];
								var16 = CircularAngle::COSINE[var14];
								var17 = var15 * verticesY[var11] + var16 * verticesX[var11] >> 16;
								verticesY[var11] = var16 * verticesY[var11] - var15 * verticesX[var11] >> 16;
								verticesX[var11] = var17;
							}

							if (var12 != 0)
							{
								var15 = CircularAngle::SINE[var12];
								var16 = CircularAngle::COSINE[var12];
								var17 = var16 * verticesY[var11] - var15 * verticesZ[var11] >> 16;
								verticesZ[var11] = var15 * verticesY[var11] + var16 * verticesZ[var11] >> 16;
								verticesY[var11] = var17;
							}

							if (var13 != 0)
							{
								var15 = CircularAngle::SINE[var13];
								var16 = CircularAngle::COSINE[var13];
								var17 = var15 * verticesZ[var11] + var16 * verticesX[var11] >> 16;
								verticesZ[var11] = var16 * verticesZ[var11] - var15 * verticesX[var11] >> 16;
								verticesX[var11] = var17;
							}

							verticesX[var11] += animOffsetX;
							verticesY[var11] += animOffsetY;
							verticesZ[var11] += animOffsetZ;
						}
					}
				}

			}
			else if (type == 3)
			{
				for (var7 = 0; var7 < var6; ++var7)
				{
					var8 = frameMap[var7];
					if (var8 < this->vertexGroups.size())
					{
						var18 = this->vertexGroups[var8];

						for (var19 = 0; var19 < var18.size(); ++var19)
						{
							var11 = var18[var19];
							verticesX[var11] -= animOffsetX;
							verticesY[var11] -= animOffsetY;
							verticesZ[var11] -= animOffsetZ;
							verticesX[var11] = dx * verticesX[var11] / 128;
							verticesY[var11] = dy * verticesY[var11] / 128;
							verticesZ[var11] = dz * verticesZ[var11] / 128;
							verticesX[var11] += animOffsetX;
							verticesY[var11] += animOffsetY;
							verticesZ[var11] += animOffsetZ;
						}
					}
				}

			}
			else if (type == 5)
			{
				// alpha animation
			}
		}
	}

	void ModelDefinition::method1493()
	{
		int var1;
		for (var1 = 0; var1 < this->vertexCount; ++var1)
		{
			this->vertexZ[var1] = -this->vertexZ[var1];
		}

		for (var1 = 0; var1 < this->faceCount; ++var1)
		{
			int var2 = this->faceIndices1[var1];
			this->faceIndices1[var1] = this->faceIndices3[var1];
			this->faceIndices3[var1] = var2;
		}

		reset();
	}

	void ModelDefinition::rotate1()
	{
		for (int var1 = 0; var1 < this->vertexCount; ++var1)
		{
			int var2 = this->vertexX[var1];
			this->vertexX[var1] = this->vertexZ[var1];
			this->vertexZ[var1] = -var2;
		}

		reset();
	}

	void ModelDefinition::rotate2()
	{
		for (int var1 = 0; var1 < this->vertexCount; ++var1)
		{
			this->vertexX[var1] = -this->vertexX[var1];
			this->vertexZ[var1] = -this->vertexZ[var1];
		}

		reset();
	}

	void ModelDefinition::rotate3()
	{
		for (int var1 = 0; var1 < this->vertexCount; ++var1)
		{
			int var2 = this->vertexZ[var1];
			this->vertexZ[var1] = this->vertexX[var1];
			this->vertexX[var1] = -var2;
		}

		reset();
	}

	void ModelDefinition::reset()
	{
		vertexNormals = std::vector<std::shared_ptr<VertexNormal>>();
		faceNormals = std::vector<std::shared_ptr<FaceNormal>>();
		faceTextureUCoordinates = faceTextureVCoordinates = std::vector<std::vector<float>>();
	}

	void ModelDefinition::resize(int var1, int var2, int var3)
	{
		for (int var4 = 0; var4 < this->vertexCount; ++var4)
		{
			this->vertexX[var4] = this->vertexX[var4] * var1 / 128;
			this->vertexY[var4] = var2 * this->vertexY[var4] / 128;
			this->vertexZ[var4] = var3 * this->vertexZ[var4] / 128;
		}

		reset();
	}

	void ModelDefinition::recolor(short var1, short var2)
	{
		for (int var3 = 0; var3 < this->faceCount; ++var3)
		{
			if (this->faceColors[var3] == var1)
			{
				this->faceColors[var3] = var2;
			}
		}

	}

	void ModelDefinition::retexture(short var1, short var2)
	{
		if (!this->faceTextures.empty())
		{
			for (int var3 = 0; var3 < this->faceCount; ++var3)
			{
				if (this->faceTextures[var3] == var1)
				{
					this->faceTextures[var3] = var2;
				}
			}

		}
	}

	void ModelDefinition::move(int xOffset, int yOffset, int zOffset)
	{
		for (int i = 0; i < this->vertexCount; i++)
		{
			this->vertexX[i] += xOffset;
			this->vertexY[i] += yOffset;
			this->vertexZ[i] += zOffset;
		}
		this->reset();
	}

	void ModelDefinition::computeMaxPriority()
	{
		if (faceRenderPriorities.empty())
		{
			return;
		}

		for (int i = 0; i < faceCount; ++i)
		{
			if (faceRenderPriorities[i] > maxPriority)
			{
				maxPriority = faceRenderPriorities[i];
			}
		}
	}
}
