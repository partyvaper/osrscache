#include "HeightCalc.h"

namespace net::runelite::cache::region
{

const double HeightCalc::ANGULAR_RATIO = 360.0 / JAGEX_CIRCULAR_ANGLE;
const double HeightCalc::JAGEX_RADIAN = Math::toRadians(ANGULAR_RATIO);
const std::vector<int> HeightCalc::SIN = std::vector<int>(JAGEX_CIRCULAR_ANGLE);
const std::vector<int> HeightCalc::COS = std::vector<int>(JAGEX_CIRCULAR_ANGLE);

	HeightCalc::StaticConstructor::StaticConstructor()
	{
	for (int i = 0; i < JAGEX_CIRCULAR_ANGLE; i++)
	{
		SIN[i] = static_cast<int>(65536.0 * std::sin(static_cast<double>(i) * JAGEX_RADIAN));
		COS[i] = static_cast<int>(65536.0 * std::cos(static_cast<double>(i) * JAGEX_RADIAN));
	}
	}

HeightCalc::StaticConstructor HeightCalc::staticConstructor;

	int HeightCalc::calculate(int x, int y)
	{
		int n = interpolateNoise(x + 45365, y + 91923, 4) - 128 + (interpolateNoise(10294 + x, y + 37821, 2) - 128 >> 1) + (interpolateNoise(x, y, 1) - 128 >> 2);
		n = 35 + static_cast<int>(static_cast<double>(n) * 0.3);
		if (n < 10)
		{
			n = 10;
		}
		else if (n > 60)
		{
			n = 60;
		}

		return n;
	}

	int HeightCalc::interpolateNoise(int x, int y, int frequency)
	{
		int intX = x / frequency;
		int fracX = x & frequency - 1;
		int intY = y / frequency;
		int fracY = y & frequency - 1;
		int v1 = smoothedNoise1(intX, intY);
		int v2 = smoothedNoise1(intX + 1, intY);
		int v3 = smoothedNoise1(intX, intY + 1);
		int v4 = smoothedNoise1(1 + intX, 1 + intY);
		int i1 = interpolate(v1, v2, fracX, frequency);
		int i2 = interpolate(v3, v4, fracX, frequency);
		return interpolate(i1, i2, fracY, frequency);
	}

	int HeightCalc::smoothedNoise1(int x, int y)
	{
		int corners = noise(x - 1, y - 1) + noise(x + 1, y - 1) + noise(x - 1, 1 + y) + noise(x + 1, y + 1);
		int sides = noise(x - 1, y) + noise(1 + x, y) + noise(x, y - 1) + noise(x, 1 + y);
		int center = noise(x, y);
		return center / 4 + sides / 8 + corners / 16;
	}

	int HeightCalc::noise(int x, int y)
	{
		int n = x + y * 57;
		n ^= n << 13;
		return ((n * (n * n * 15731 + 789221) + 1376312589) & std::numeric_limits<int>::max()) >> 19 & 255;
	}

	int HeightCalc::interpolate(int a, int b, int x, int y)
	{
		int f = 65536 - COS[1024 * x / y] >> 1;
		return (f * b >> 16) + (a * (65536 - f) >> 16);
	}
}
