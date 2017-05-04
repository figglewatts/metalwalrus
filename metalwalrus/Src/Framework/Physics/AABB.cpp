#include "AABB.h"

#include <math.h>

namespace metalwalrus
{
	void AABB::updateOrigin()
	{
		this->origin = (min + max) / 2;
	}

	AABB::AABB()
	{
		this->min = Vector2();
		this->max = Vector2();
		this->origin = Vector2();
	}

	AABB::AABB(Vector2 min, Vector2 max)
	{
		this->min = min;
		this->max = max;
		this->updateOrigin();
	}

	AABB::AABB(const AABB & other)
	{
		this->min = other.min;
		this->max = other.max;
		this->origin = other.origin;
	}

	AABB & AABB::operator=(const AABB & other)
	{
		if (this != &other)
		{
			this->min = other.min;
			this->max = other.max;
			this->origin = other.origin;
		}
		return *this;
	}

	AABB AABB::operator+(Vector2 v)
	{
		return AABB(min + v, max + v);
	}

	AABB AABB::operator-(Vector2 v)
	{
		return AABB(min - v, max - v);
	}

	AABB & AABB::operator+=(Vector2 v)
	{
		this->min += v;
		this->max += v;
		this->origin += v;
		return *this;
	}

	AABB & AABB::operator-=(Vector2 v)
	{
		this->min -= v;
		this->max -= v;
		this->origin -= v;
		return *this;
	}

	bool AABB::intersects(AABB other)
	{
		if (this->max.x < other.min.x) return false; // we're left of it
		if (this->min.x > other.max.x) return false; // right of it
		if (this->max.y < other.min.y) return false; // under it
		if (this->min.y > other.max.y) return false; // on top of it
		return true;
	}

	float AABB::getXDepth(AABB other)
	{
		return fabsf(this->min.x - other.min.x);
	}

	float AABB::getYDepth(AABB other)
	{
		return fabsf(this->min.y - other.min.y);
	}
}