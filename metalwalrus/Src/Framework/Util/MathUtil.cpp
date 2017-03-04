#include "MathUtil.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace metalwalrus
{
	namespace utilities
	{
		const static float RAD_TO_DEG = 180 / M_PI;
		const static float DEG_TO_RAD = M_PI / 180;
		
		static float radToDeg(float rads)
		{
			return rads * RAD_TO_DEG;
		}

		static float degToRad(float degs)
		{
			return degs * DEG_TO_RAD;
		}
	}
}