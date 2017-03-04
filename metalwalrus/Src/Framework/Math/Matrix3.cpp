#include "Matrix3.h"

#include <stdexcept>

namespace metalwalrus
{
	const Matrix3 Matrix3::IDENTITY = Matrix3();
	
	Matrix3::Matrix3()
	{
		this->identity();
	}

	Matrix3::Matrix3(float values[MATRIX_VALS])
	{
		this->val.assign(values, values+MATRIX_VALS);
	}

	float Matrix3::operator[](unsigned i) const
	{
		if (i >= MATRIX_VALS)
			throw std::runtime_error("Cannot access matrix element past length!");
		return val[i];
	}

	Matrix3 Matrix3::operator+(const Matrix3 & other) const
	{
		float newVals[MATRIX_VALS];
		newVals[M00] = val[M00] + other[M00];
		newVals[M01] = val[M01] + other[M01];
		newVals[M02] = val[M02] + other[M02];
		newVals[M10] = val[M10] + other[M10];
		newVals[M11] = val[M11] + other[M11];
		newVals[M12] = val[M12] + other[M12];
		newVals[M20] = val[M20] + other[M20];
		newVals[M21] = val[M21] + other[M21];
		newVals[M22] = val[M22] + other[M22];
		return Matrix3(newVals);
	}

	Matrix3 Matrix3::operator-() const
	{
		float newVals[MATRIX_VALS];
		newVals[M00] = -val[M00];
		newVals[M01] = -val[M01];
		newVals[M02] = -val[M02];
		newVals[M10] = -val[M10];
		newVals[M11] = -val[M11];
		newVals[M12] = -val[M12];
		newVals[M20] = -val[M20];
		newVals[M21] = -val[M21];
		newVals[M22] = -val[M22];
		return Matrix3(newVals);
	}

	Matrix3 Matrix3::operator-(const Matrix3 & other) const
	{
		return *this + -other;
	}

	Matrix3 Matrix3::operator*(const Matrix3 & other) const
	{
		float newVals[MATRIX_VALS];
		newVals[M00] = val[M00] * other[M00] + val[M01] * other[M10] + val[M02] * other[M20];
		newVals[M01] = val[M00] * other[M01] + val[M01] * other[M11] + val[M02] * other[M21];
		newVals[M02] = val[M00] * other[M02] + val[M01] * other[M12] + val[M02] * other[M22];
		newVals[M10] = val[M10] * other[M00] + val[M11] * other[M10] + val[M12] * other[M20];
		newVals[M11] = val[M10] * other[M01] + val[M11] * other[M11] + val[M12] * other[M21];
		newVals[M12] = val[M10] * other[M02] + val[M11] * other[M12] + val[M12] * other[M22];
		newVals[M20] = val[M20] * other[M00] + val[M21] * other[M10] + val[M22] * other[M20];
		newVals[M21] = val[M20] * other[M01] + val[M21] * other[M11] + val[M22] * other[M21];
		newVals[M22] = val[M20] * other[M02] + val[M21] * other[M12] + val[M22] * other[M22];
		return Matrix3(newVals);
	}

	Matrix3 Matrix3::operator*(const float scalar) const
	{
		float newVals[MATRIX_VALS];
		newVals[M00] = val[M00] * scalar;
		newVals[M01] = val[M01] * scalar;
		newVals[M02] = val[M02] * scalar;
		newVals[M10] = val[M10] * scalar;
		newVals[M11] = val[M11] * scalar;
		newVals[M12] = val[M12] * scalar;
		newVals[M20] = val[M20] * scalar;
		newVals[M21] = val[M21] * scalar;
		newVals[M22] = val[M22] * scalar;
		return Matrix3(newVals);
	}

	Matrix3 *Matrix3::identity()
	{
		float newVals[MATRIX_VALS] = {};
		newVals[M00] = 1;
		newVals[M11] = 1;
		newVals[M22] = 1;
		val.assign(newVals, newVals+MATRIX_VALS);
		return this;
	}

	float Matrix3::det() const
	{
		return val[M00] * (val[M11] * val[M22] - val[M21] * val[M12])
			- val[M01] * (val[M10] * val[M22] - val[M12] * val[M20])
			+ val[M02] * (val[M10] * val[M21] - val[M11] * val[M20]);
	}

	Matrix3 Matrix3::inv() const
	{
		float det = this->det();
		if (det == 0)
			throw std::runtime_error("Cannot invert a singular matrix!");

		return (1 / det) * this->adj();
	}

	Matrix3 Matrix3::trans() const
	{
		float newVals[MATRIX_VALS];
		newVals[M00] = val[M00];
		newVals[M01] = val[M10];
		newVals[M02] = val[M20];
		newVals[M10] = val[M01];
		newVals[M11] = val[M11];
		newVals[M12] = val[M21];
		newVals[M20] = val[M02];
		newVals[M21] = val[M12];
		newVals[M22] = val[M22];
		return Matrix3(newVals);
	}

	Matrix3 Matrix3::cofactor() const
	{
		float cofactors[MATRIX_VALS];
		cofactors[M00] = val[M11] * val[M22] - val[M12] * val[M21];
		cofactors[M01] = val[M10] * val[M22] - val[M12] * val[M20];
		cofactors[M02] = val[M10] * val[M21] - val[M11] * val[M20];
		cofactors[M10] = val[M01] * val[M22] - val[M02] * val[M21];
		cofactors[M11] = val[M00] * val[M22] - val[M02] * val[M20];
		cofactors[M12] = val[M00] * val[M21] - val[M01] * val[M20];
		cofactors[M20] = val[M01] * val[M12] - val[M02] * val[M11];
		cofactors[M21] = val[M00] * val[M12] - val[M02] * val[M10];
		cofactors[M22] = val[M00] * val[M11] - val[M01] * val[M10];
		return Matrix3(cofactors);
	}

	Matrix3 Matrix3::adj() const
	{
		return this->cofactor().trans();
	}

	Matrix3 Matrix3::rotate(float degrees) const
	{
		return Matrix3();
	}

	Matrix3 operator*(const float scalar, const Matrix3& other)
	{
		return other * scalar;
	}


}