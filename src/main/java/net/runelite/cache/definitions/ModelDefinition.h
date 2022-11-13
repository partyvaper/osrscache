#pragma once

#include "../models/CircularAngle.h"
#include "../models/FaceNormal.h"
#include "../models/VertexNormal.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <memory>

namespace net::runelite::cache::definitions
{

	using FaceNormal = net::runelite::cache::models::FaceNormal;
	using VertexNormal = net::runelite::cache::models::VertexNormal;

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @Data public class ModelDefinition
	class ModelDefinition : public std::enable_shared_from_this<ModelDefinition>
	{
	public:
		int id = 0;

		int vertexCount = 0;
		std::vector<int> vertexX;
		std::vector<int> vertexY;
		std::vector<int> vertexZ;
		std::vector<std::shared_ptr<VertexNormal>> vertexNormals;

		int faceCount = 0;
		std::vector<int> faceIndices1;
		std::vector<int> faceIndices2;
		std::vector<int> faceIndices3;
		std::vector<signed char> faceTransparencies;
		std::vector<short> faceColors;
		std::vector<signed char> faceRenderPriorities;
		std::vector<signed char> faceRenderTypes;
		std::vector<std::shared_ptr<FaceNormal>> faceNormals;

		int numTextureFaces = 0;
		std::vector<short> texIndices1;
		std::vector<short> texIndices2;
		std::vector<short> texIndices3;
		std::vector<std::vector<float>> faceTextureUCoordinates;
		std::vector<std::vector<float>> faceTextureVCoordinates;
		std::vector<short> texturePrimaryColors;
		std::vector<short> faceTextures;
		std::vector<signed char> textureCoords;
		std::vector<signed char> textureRenderTypes;

		std::vector<int> packedVertexGroups;
		std::vector<int> packedTransparencyVertexGroups;

		signed char priority = 0;

	private:
		std::vector<std::vector<int>> vertexGroups;
	public:
		std::vector<std::vector<int>> animayaGroups;
		std::vector<std::vector<int>> animayaScales;

	private:
		std::vector<int> origVX;
		std::vector<int> origVY;
		std::vector<int> origVZ;

	public:
		int maxPriority = 0;

		static int animOffsetX;
			static int animOffsetY;
			static int animOffsetZ;

		virtual void computeNormals();

		/**
		 * Computes the UV coordinates for every three-vertex face that has a
		 * texture.
		 */
		virtual void computeTextureUVCoordinates();

		virtual void computeAnimationTables();

		virtual void rotate(int orientation);

		virtual void resetAnim();

		virtual void animate(int type, std::vector<int> &frameMap, int dx, int dy, int dz);

		virtual void method1493();

		virtual void rotate1();

		virtual void rotate2();

		virtual void rotate3();

	private:
		void reset();

	public:
		virtual void resize(int var1, int var2, int var3);

		virtual void recolor(short var1, short var2);

		virtual void retexture(short var1, short var2);

		virtual void move(int xOffset, int yOffset, int zOffset);

		virtual void computeMaxPriority();
	};

}
