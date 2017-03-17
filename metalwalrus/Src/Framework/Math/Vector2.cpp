#include "Vector2.h"

#include <math.h>

namespace metalwalrus
{
	const Vector2 Vector2::RIGHT = Vector2(1, 0);
	const Vector2 Vector2::UP = Vector2(0, 1);
	const Vector2 Vector2::ZERO = Vector2(0, 0);
	
	Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2 Vector2::operator+(const Vector2 & other) const
	{
		return Vector2(this->x + other.x, this->y + other.y);
	}

	Vector2 Vector2::operator-() const
	{
		return Vector2(-this->x, -this->y);
	}

	Vector2 Vector2::operator-(const Vector2 & other) const
	{
		return *this + (-other);
	}

	Vector2 Vector2::operator*(float scalar) const
	{
		return Vector2(this->x * scalar, this->y * scalar);
	}

	Vector2 Vector2::operator/(float scalar) const
	{
		return Vector2(this->x / scalar, this->y / scalar);
	}

	float Vector2::dot(const Vector2 & other) const
	{
		return (this->x * other.x) + (this->y * other.y);
	}

	Vector2 Vector2::normalize() const
	{
		return *this / this->dist();
	}

	float Vector2::dist() const
	{
		return sqrtf(this->sqrdist());
	}

	float Vector2::sqrdist() const
	{
		return (this->x * this->x) + (this->y * this->y);
	}

	Vector2 operator*(float scalar, const Vector2 & other)
	{
		return other * scalar;
	}

	Vector2 operator/(float scalar, const Vector2 & other)
	{
		return other / scalar;
	}
}