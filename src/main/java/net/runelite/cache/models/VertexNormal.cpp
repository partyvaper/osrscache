#include "VertexNormal.h"

namespace net::runelite::cache::models
{

	std::shared_ptr<Vector3f> VertexNormal::normalize()
	{
		std::shared_ptr<Vector3f> v = std::make_shared<Vector3f>();

		int length = static_cast<int>(std::sqrt(static_cast<double>(x * x + y * y + z * z)));
		if (length == 0)
		{
			length = 1;
		}

		v->x = static_cast<float>(x) / length;
		v->y = static_cast<float>(y) / length;
		v->z = static_cast<float>(z) / length;

		assert(v->x >= -1.0f && v->x <= 1.0f);
		assert(v->y >= -1.0f && v->y <= 1.0f);
		assert(v->z >= -1.0f && v->z <= 1.0f);

		return v;
	}
}
