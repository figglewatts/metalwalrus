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
		bool xOverlap = (this->min.x < other.max.x) && (this->max.x > other.min.x);
		bool yOverlap = (this->max.y < other.min.y) && (this->min.y > other.max.y);
		return xOverlap && yOverlap;
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