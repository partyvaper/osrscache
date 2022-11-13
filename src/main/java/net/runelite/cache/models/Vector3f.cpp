#include "Vector3f.h"

namespace net::runelite::cache::models
{

	Vector3f::Vector3f()
	{
	}

	Vector3f::Vector3f(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3f::Vector3f(std::shared_ptr<Vector3f> other)
	{
		this->x = other->x;
		this->y = other->y;
		this->z = other->z;
	}

	std::wstring Vector3f::toString()
	{
		return L"Vector3f{" + L"x=" + std::to_wstring(x) + L", y=" + std::to_wstring(y) + L", z=" + std::to_wstring(z) + StringHelper::toString(L'}');
	}

	int Vector3f::hashCode()
	{
		int hash = 7;
		hash = 23 * hash + Float::floatToIntBits(this->x);
		hash = 23 * hash + Float::floatToIntBits(this->y);
		hash = 23 * hash + Float::floatToIntBits(this->z);
		return hash;
	}

	bool Vector3f::equals(std::any obj)
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
		constexpr std::shared_ptr<Vector3f> other = std::any_cast<std::shared_ptr<Vector3f>>(obj);
		if (Float::floatToIntBits(this->x) != Float::floatToIntBits(other->x))
		{
			return false;
		}
		if (Float::floatToIntBits(this->y) != Float::floatToIntBits(other->y))
		{
			return false;
		}
		if (Float::floatToIntBits(this->z) != Float::floatToIntBits(other->z))
		{
			return false;
		}
		return true;
	}

	float Vector3f::getX()
	{
		return x;
	}

	void Vector3f::setX(float x)
	{
		this->x = x;
	}

	float Vector3f::getY()
	{
		return y;
	}

	void Vector3f::setY(float y)
	{
		this->y = y;
	}

	float Vector3f::getZ()
	{
		return z;
	}

	void Vector3f::setZ(float z)
	{
		this->z = z;
	}
}
