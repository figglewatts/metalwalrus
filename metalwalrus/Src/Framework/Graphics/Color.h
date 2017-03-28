/* 
 * File:   Color.h
 * Author: Sam Gibson (100115871) <sam.gibson@uea.ac.uk>
 *
 * Created on March 28, 2017, 8:58 AM
 */

#ifndef COLOR_H
#define COLOR_H
#pragma once

namespace metalwalrus
{
    class Color {
	float r = 1;
	float g = 1;
	float b = 1;
	float a = 1;    
    public:
	Color();
	Color(float r, float g, float b, float a = 1);
	Color(const Color& orig);

	Color operator=(const Color& orig);
	Color operator*(const Color& other);
	Color operator+(const Color& other);

	inline float get_r() const { return r; }
	inline float get_g() const { return g; }
	inline float get_b() const { return b; }
	inline float get_a() const { return a; }
	
	const static Color WHITE;
	const static Color BLACK;
	const static Color RED;
	const static Color GREEN;
	const static Color BLUE;
    };
}

#endif /* COLOR_H */

