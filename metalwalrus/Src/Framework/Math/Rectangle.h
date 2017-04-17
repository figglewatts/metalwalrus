#ifndef RECTANGLE_H
#define RECTANGLE_H
#pragma once

#include "Vector2.h"

namespace metalwalrus
{
	class Rectangle
	{
		Vector2 position;
		Vector2 dimensions;
	public:
		Rectangle()
			: position(0, 0), dimensions(0, 0) { }
		Rectangle(float x, float y, float width, float height)
			: position(x, y), dimensions(width, height) { }
		Rectangle(Vector2 pos, Vector2 dim)
			: position(pos), dimensions(dim) { }
		Rectangle(const Rectangle& other)
			: position(other.position), dimensions(other.dimensions) { }

		Rectangle& operator=(const Rectangle& other) 
		{
			if (this != &other)
			{
				this->position = other.position;
				this->dimensions = other.dimensions;
			}
			return *this;
		}

		inline Vector2 get_position() const { return position; }
		inline float get_width() const { return dimensions.x; }
		inline float get_height() const { return dimensions.y; }
		inline Vector2 get_maxPosition() const { return position + dimensions; }
	};
}

#endif // RECTANGLE_H