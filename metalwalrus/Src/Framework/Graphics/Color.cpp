/* 
 * File:   Color.cpp
 * Author: Sam Gibson (100115871) <sam.gibson@uea.ac.uk>
 * 
 * Created on March 28, 2017, 8:58 AM
 */

#include "Color.h"

#include <cmath>

namespace metalwalrus
{
	Color::Color()
	{
		this->r = 1;
		this->g = 1;
		this->b = 1;
		this->a = 1;
	}
	
	Color::Color(float r, float g, float b, float a)
	{
		float absR = std::abs(r);
		float absG = std::abs(g);
		float absB = std::abs(b);
		float absA = std::abs(a);
		this->r = absR > 1 ? 1 : absR;
		this->g = absG > 1 ? 1 : absG;
		this->b = absB > 1 ? 1 : absB;
		this->a = absA > 1 ? 1 : absA;
	}

	Color::Color(const Color& orig) 
	{ 
		this->r = orig.r;
		this->g = orig.g;
		this->b = orig.b;
		this->a = orig.a;
	}

	Color Color::operator=(const Color& orig)
	{
		if (this != &orig)
		{
			this->r = orig.r;
			this->g = orig.g;
			this->b = orig.b;
			this->a = orig.a;
		}
		return *this;
	}
	
	// multiplicative color combination
	Color Color::operator*(const Color& other)
	{
		return Color(this->r * other.r,
				this->g * other.g,
				this->b * other.b,
				this->a * other.a);
	}
	
	// additive color combination
	Color Color::operator+(const Color& other)
	{
		return Color(this->r + other.r,
				this->g + other.g,
				this->b + other.b,
				this->a + other.a);
	}
	
	const Color Color::WHITE = Color(1, 1, 1);
	const Color Color::BLACK = Color(0, 0, 0);
	const Color Color::RED = Color(1, 0, 0);
	const Color Color::GREEN = Color(0, 1, 0);
	const Color Color::BLUE = Color(0, 0, 1);
}