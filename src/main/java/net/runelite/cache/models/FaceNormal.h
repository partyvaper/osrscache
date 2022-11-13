#pragma once

#include <memory>

namespace net::runelite::cache::models
{

	class FaceNormal : public std::enable_shared_from_this<FaceNormal>
	{
	public:
		int x = 0;
		int y = 0;
		int z = 0;
	};

}
