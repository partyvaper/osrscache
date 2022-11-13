#pragma once

#include <vector>
#include <cmath>
#include <limits>
#include <memory>

/**
 * Copyright (c) 2015 Kyle Friz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
namespace net::runelite::cache::region
{

	/**
	 * @author Kyle Friz
	 * @since Feb 20, 2016
	 */
	class HeightCalc : public std::enable_shared_from_this<HeightCalc>
	{
	private:
		static constexpr int JAGEX_CIRCULAR_ANGLE = 2048;
		static const double ANGULAR_RATIO;
		static const double JAGEX_RADIAN;

		static const std::vector<int> SIN;
		static const std::vector<int> COS;

		private:
			class StaticConstructor : public std::enable_shared_from_this<StaticConstructor>
			{
			public:
				StaticConstructor();
			};

		private:
			static HeightCalc::StaticConstructor staticConstructor;


	public:
		static int calculate(int x, int y);

		static int interpolateNoise(int x, int y, int frequency);

		static int smoothedNoise1(int x, int y);

		static int noise(int x, int y);

		static int interpolate(int a, int b, int x, int y);

	};

}
