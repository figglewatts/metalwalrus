#ifndef MATRIX3_H
#define MATRIX3_H
#pragma once

#include "Vector2.h"

#include <vector>

namespace metalwalrus
{
	class Matrix3
	{
	public:
		const static int M00 = 0;
		const static int M01 = 3;
		const static int M02 = 6;
		const static int M10 = 1;
		const static int M11 = 4;
		const static int M12 = 7;
		const static int M20 = 2;
		const static int M21 = 5;
		const static int M22 = 8;

		const static int MATRIX_VALS = 9;

		const static Matrix3 IDENTITY;

		std::vector<float> val;

		Matrix3();
		Matrix3(float values[MATRIX_VALS]);
		Matrix3(const Matrix3& other);

		Matrix3 operator=(const Matrix3& other);

		float operator[](unsigned i) const;
		float& operator[](unsigned i);
		Matrix3 operator+(const Matrix3& other) const;
		Matrix3 operator-() const;
		Matrix3 operator-(const Matrix3& other) const;
		Matrix3 operator*(const Matrix3& other) const;
		Matrix3 operator*(const float scalar) const;
		friend Matrix3 operator*(const float scalar, const Matrix3& other);

		void set(float values[MATRIX_VALS]);
		Matrix3 *identity();
		float det() const;
		Matrix3 inv() const;
		Matrix3 trans() const;
		Matrix3 cofactor() const;
		Matrix3 adj() const;
		Matrix3 rotate(float degrees);
		Matrix3 rotateRad(float radians);
		Matrix3 scale(float x, float y);
		Matrix3 scale(Vector2 scale);
		Matrix3 translation(float x, float y);
		Matrix3 translation(Vector2 translation);
	};

}
#endif