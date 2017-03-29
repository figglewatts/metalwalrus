#ifndef VECTOR2_H
#define VECTOR2_H
#pragma once

namespace metalwalrus 
{
    class Matrix3; // forward declaration
    
    class Vector2 
    {
    public:
	float x;
	float y;

	const static Vector2 RIGHT;
	const static Vector2 UP;
	const static Vector2 ZERO;

	Vector2();
	Vector2(float x, float y);

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-() const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(float scalar) const;
	friend Vector2 operator*(float scalar, const Vector2& other);
	Vector2 operator*(const Matrix3& other);
	Vector2 operator*=(const Matrix3& other);
	Vector2 operator/(float scalar) const;
	friend Vector2 operator/(float scalar, const Vector2& other);

	float dot(const Vector2& other) const;

	Vector2 normalize() const;

	float dist() const;
	float sqrdist() const;
	Vector2& transform(Matrix3& mat);
    };

    Vector2 operator*(float scalar, const Vector2& other);
    Vector2 operator/(float scalar, const Vector2& other);
}
#endif