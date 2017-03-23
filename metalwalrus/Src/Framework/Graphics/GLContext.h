#ifndef GLCONTEXT_H
#define GLCONTEXT_H
#pragma once

namespace metalwalrus
{
	class GLContext
	{
	public:
		GLContext();
		~GLContext();

		void clear(float r, float g, float b);

		void viewport(int x, int y, int w, int h);
	};
}

#endif