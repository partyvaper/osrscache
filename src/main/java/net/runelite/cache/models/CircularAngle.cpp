#include "CircularAngle.h"

namespace net::runelite::cache::models
{

const double CircularAngle::UNIT = M_PI / 1024.0;
const std::vector<int> CircularAngle::SINE = std::vector<int>(2048);
const std::vector<int> CircularAngle::COSINE = std::vector<int>(2048);

	CircularAngle::StaticConstructor::StaticConstructor()
	{
	for (int i = 0; i < 2048; ++i)
	{
		SINE[i] = static_cast<int>(65536.0 * std::sin(static_cast<double>(i) * UNIT));
		COSINE[i] = static_cast<int>(65536.0 * std::cos(static_cast<double>(i) * UNIT));
	}
	}

CircularAngle::StaticConstructor CircularAngle::staticConstructor;
}
