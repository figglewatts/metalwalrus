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

		inline Vector2 get_min() const { return min; }
		inline Vector2 get_max() const { return max; }
		inline Vector2 get_origin() const { return origin; }

		inline float get_left() const { return min.x; }
		inline float get_right() const { return max.x; }
		inline float get_top() const { return max.y; }
		inline float get_bottom() const { return min.y; }
		inline float get_width() const { return max.x - min.x; }
		inline float get_height() const { return max.y - min.y; }

		bool intersects(AABB other);
		float getXDepth(AABB other);
		float getYDepth(AABB other);
	};
}

#endif // AABB_H