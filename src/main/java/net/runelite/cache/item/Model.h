#pragma once

#include "Renderable.h"
#include "Graphics3D.h"
#include <vector>
#include <cmath>
#include <memory>
#include "../../../../../../../tangible_rectangular_vectors.h"

/*
 * Copyright (c) 2018, Adam <Adam@sigterm.info>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
namespace net::runelite::cache::item
{

	class Model : public Renderable
	{
	public:
		std::vector<bool> field1887 = std::vector<bool>(4700);
		std::vector<bool> field1885 = std::vector<bool>(4700);
		std::vector<int> modelViewportYs = std::vector<int>(4700);
		std::vector<int> modelViewportXs = std::vector<int>(4700);
		std::vector<int> modelViewportZs = std::vector<int>(4700);
		std::vector<int> yViewportBuffer = std::vector<int>(4700);
		std::vector<int> field1839 = std::vector<int>(4700);
		std::vector<int> field1869 = std::vector<int>(4700);
		std::vector<int> field1871 = std::vector<int>(1600);
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: int[][] field1868 = new int[1600][512];
		std::vector<std::vector<int>> field1868 = RectangularVectors::RectangularIntVector(1600, 512);
		std::vector<int> field1872 = std::vector<int>(12);
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: int[][] field1874 = new int[12][2000];
		std::vector<std::vector<int>> field1874 = RectangularVectors::RectangularIntVector(12, 2000);
		std::vector<int> field1857 = std::vector<int>(2000);
		std::vector<int> field1863 = std::vector<int>(2000);
		std::vector<int> field1877 = std::vector<int>(12);
		std::vector<int> field1831 = std::vector<int>(10);
		std::vector<int> field1837 = std::vector<int>(10);
		std::vector<int> xViewportBuffer = std::vector<int>(10);
		static std::vector<int> Model_sine;
		static std::vector<int> Model_cosine;
		static std::vector<int> field1890;
		int verticesCount = 0;
		std::vector<int> verticesX;
		std::vector<int> verticesY;
		std::vector<int> verticesZ;
		int indicesCount = 0;
		std::vector<int> indices1;
		std::vector<int> indices2;
		std::vector<int> indices3;
		std::vector<int> field1856;
		std::vector<int> field1854;
		std::vector<int> field1823;
		std::vector<signed char> field1838;
		std::vector<signed char> field1882;
		std::vector<signed char> field1840;
		std::vector<short> field1841;
		signed char field1842 = 0;
		int field1852 = 0;
		std::vector<int> field1844;
		std::vector<int> field1865;
		std::vector<int> field1846;
		bool isItemModel = false;
		int boundsType = 0;
		int bottomY = 0;
		int XYZMag = 0;
		int diameter = 0;
		int radius = 0;
		int extremeX = 0;
		int extremeY = 0;
		int extremeZ = 0;

		private:
			class StaticConstructor : public std::enable_shared_from_this<StaticConstructor>
			{
			public:
				StaticConstructor();
			};

		private:
			static Model::StaticConstructor staticConstructor;


	public:
		Model();

		virtual void calculateBoundsCylinder();

		void rotateAndProject(std::shared_ptr<Graphics3D> graphics, int rotation_1, int yRotation, int zRotation, int xRotation, int xOffset, int yOffset, int zOffset);


	private:
		void method0(std::shared_ptr<Graphics3D> graphics, bool var1, bool var3, int var4);

		void method2706(std::shared_ptr<Graphics3D> graphics, int var1);


		void method2707(std::shared_ptr<Graphics3D> graphics, int var1);

	protected:
		std::shared_ptr<Model> shared_from_this()
		{
			return std::static_pointer_cast<Model>(Renderable::shared_from_this());
		}
	};
}
