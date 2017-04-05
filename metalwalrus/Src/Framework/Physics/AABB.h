#ifndef AABB_H
#define AABB_H
#pragma once

#include "../Math/Vector2.h"

namespace metalwalrus
{
	class AABB
	{
		Vector2 min;
		Vector2 max;
		Vector2 origin;

		void updateOrigin();
	public:
		AABB();
		AABB(Vector2 min, Vector2 max);
		AABB(const AABB& other);

		AABB& operator=(const AABB& other);
		AABB operator+(Vector2 v);
		AABB operator-(Vector2 v);
		AABB& operator+=(Vector2 v);
		AABB& operator-=(Vector2 v);

		inline Vector2 get_min() { return min; }
		inline Vector2 get_max() { return max; }
		inline Vector2 get_origin() { return origin; }

		bool intersects(AABB& other);
		float getXDepth(AABB& other);
		float getYDepth(AABB& other);
	};
}

#endif // AABB_H