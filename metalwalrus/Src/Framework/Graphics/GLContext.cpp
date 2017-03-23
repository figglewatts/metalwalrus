#include "GLContext.h"

#include <GL/glew.h>

#include "../Settings.h"

namespace metalwalrus
{
	GLContext::GLContext()
	{}


	GLContext::~GLContext()
	{}

	void GLContext::clear(float r, float g, float b)
	{
		glClearColor(r, g, b, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GLContext::viewport(int x, int y, int w, int h)
	{
		glViewport(x, y, w, h);
		Settings::VIEWPORT_X = x;
		Settings::VIEWPORT_Y = y;
		Settings::VIEWPORT_WIDTH = w;
		Settings::VIEWPORT_HEIGHT = h;
	}
}