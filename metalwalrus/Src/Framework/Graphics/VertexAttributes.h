#ifndef VERTEXATTRIBUTES_H
#define VERTEXATTRIBUTES_H
#pragma once

#include <GL/glew.h>

namespace metalwalrus
{
	class VertexAttributes
	{
		GLuint glHandle = 0;
	public:
		VertexAttributes();
		~VertexAttributes();

		void load();
	};
}

#endif