#include "Vector2.h"

#include "Matrix3.h"

#include <math.h>

namespace metalwalrus
{
	const Vector2 Vector2::RIGHT = Vector2(1, 0);
	const Vector2 Vector2::UP = Vector2(0, 1);
	const Vector2 Vector2::ZERO = Vector2(0, 0);
	
	Vector2::Vector2()
	{
		this->x = 0;
		this->y = 0;
	}

	Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2 Vector2::operator+(const Vector2 & other) const
	{
		return Vector2(this->x + other.x, this->y + other.y);
	}

	Vector2 & Vector2::operator+=(const Vector2 & other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2 Vector2::operator-() const
	{
		return Vector2(-this->x, -this->y);
	}

	Vector2 Vector2::operator-(const Vector2 & other) const
	{
		return *this + (-other);
	}

	Vector2 & Vector2::operator-=(const Vector2 & other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2 Vector2::operator*(float scalar) const
	{
		return Vector2(this->x * scalar, this->y * scalar);
	}
	
	Vector2 Vector2::operator*(const Matrix3& other)
	{
		float newX = x * other[other.M00] + y * other[other.M01];
		float newY = x * other[other.M10] + y * other[other.M11];
		return Vector2(newX, newY);
	}
	
	Vector2 Vector2::operator*=(const Matrix3& other)
	{
		Vector2 result = *this * other;
		x = result.x;
		y = result.y;
		return *this;
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
	
	Vector2& Vector2::transform(Matrix3& mat)
	{
		Vector2 transVec = *this * mat;
		transVec.x += mat[mat.M02];
		transVec.y += mat[mat.M12];
		this->x = transVec.x;
		this->y = transVec.y;
		return *this;
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