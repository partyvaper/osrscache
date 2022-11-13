#include "Position.h"

namespace net::runelite::cache::region
{

	Position::Position(int x, int y, int z) : x(x), y(y), z(z)
	{
	}

	std::wstring Position::toString()
	{
		return L"Position{" + L"x=" + std::to_wstring(x) + L", y=" + std::to_wstring(y) + L", z=" + std::to_wstring(z) + StringHelper::toString(L'}');
	}

	int Position::hashCode()
	{
		int hash = 7;
		hash = 67 * hash + this->x;
		hash = 67 * hash + this->y;
		hash = 67 * hash + this->z;
		return hash;
	}

	bool Position::equals(std::any obj)
	{
		if (shared_from_this() == obj)
		{
			return true;
		}
		if (!obj.has_value())
		{
			return false;
		}
		if (getClass() != obj.type())
		{
			return false;
		}
		constexpr std::shared_ptr<Position> other = std::any_cast<std::shared_ptr<Position>>(obj);
		if (this->x != other->x)
		{
			return false;
		}
		if (this->y != other->y)
		{
			return false;
		}
		if (this->z != other->z)
		{
			return false;
		}
		return true;
	}

	int Position::getX()
	{
		return x;
	}

	int Position::getY()
	{
		return y;
	}

	int Position::getZ()
	{
		return z;
	}
}
