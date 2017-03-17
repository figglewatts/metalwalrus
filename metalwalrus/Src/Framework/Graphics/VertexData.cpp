#include "VertexData.h"

#include <GL/glew.h>

namespace metalwalrus
{
	VertexData::VertexData()
	{
	}


	VertexData::~VertexData()
	{
	}

	// tell OpenGL about the VertexBuffer
	void VertexData::load()
	{
		glGenBuffers(1, &glHandle);
		glBindBuffer(GL_ARRAY_BUFFER, glHandle);
		size_t size = sizeof(vertices[0]) * vertices.size();
		glBufferData(GL_ARRAY_BUFFER, size, &vertices[0], GL_STATIC_DRAW);
	}
}