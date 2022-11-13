#pragma once

#include <string>
#include <any>
#include <memory>
#include "../../../../../../../tangible_string_helper.h"

namespace net::runelite::cache::models
{

	class Vector3f : public std::enable_shared_from_this<Vector3f>
	{
	public:
		float x = 0.0F;
		float y = 0.0F;
		float z = 0.0F;

		Vector3f();

		Vector3f(float x, float y, float z);

		Vector3f(std::shared_ptr<Vector3f> other);

		virtual std::wstring toString();

		virtual int hashCode();

		virtual bool equals(std::any obj);

		virtual float getX();

		virtual void setX(float x);

		virtual float getY();

		virtual void setY(float y);

		virtual float getZ();

		virtual void setZ(float z);
	};

}
