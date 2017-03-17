#ifndef MATHUTIL_H
#define MATHUTIL_H
#pragma once

namespace metalwalrus
{
	namespace utilities
	{
		class MathUtil
		{
			MathUtil();
		public:	
			static float radToDeg(float rads);
			static float degToRad(float degs);
		};
	}
}
#endif