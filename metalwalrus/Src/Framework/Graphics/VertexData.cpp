#include "VertexData.h"

#include <GL/glew.h>

namespace metalwalrus
{
	VertexData::VertexData(float vertices[], unsigned vertNum, GLubyte indices[], unsigned indNum)
	{
		this->vertices.assign(vertices, vertices + vertNum);
		this->indices.assign(indices, indices + indNum);
		this->load();
	}

	VertexData::~VertexData()
	{
		glDeleteBuffers(1, &vertHandle);
		glDeleteBuffers(1, &indHandle);
	}

	// tell OpenGL about the VertexBuffer
	void VertexData::load()
	{
		glGenBuffers(1, &vertHandle);
		bindVertices();
		size_t vertSize = sizeof(vertices[0]) * vertices.size();
		glBufferData(GL_ARRAY_BUFFER, vertSize, &vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &indHandle);
		bindIndices();
		size_t indSize = sizeof(indices[0]) * indices.size();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize, &indices[0], GL_STATIC_DRAW);
	}

	void VertexData::bind()
	{
		this->bindVertices();
		this->bindIndices();
	}

	void VertexData::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void VertexData::bindVertices()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertHandle);
	}

	void VertexData::bindIndices()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indHandle);
	}

	void VertexData::draw(int count)
	{
		this->bind();

		// set position in the vertex array
		glVertexPointer(2, GL_FLOAT, 0, 0);

		glDrawElements(GL_QUADS, count, GL_UNSIGNED_BYTE, 0);

		this->unbind();
	}
}