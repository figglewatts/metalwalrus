#ifndef GLCONTEXT_H
#define GLCONTEXT_H
#pragma once

#include "Color.h"

namespace metalwalrus
{
	class GLContext
	{
	public:
		GLContext();
		~GLContext();

		void clear(float r, float g, float b);
		void clear(Color c);
		
		void viewport(int x, int y, int w, int h);
	};
}

#endif