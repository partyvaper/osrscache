#pragma once

#include "Vector3f.h"
#include <cmath>
#include <cassert>
#include <memory>

namespace net::runelite::cache::models
{

	class VertexNormal : public std::enable_shared_from_this<VertexNormal>
	{
	public:
		int x = 0;
		int y = 0;
		int z = 0;
		int magnitude = 0;

		virtual std::shared_ptr<Vector3f> normalize();
	};

}
