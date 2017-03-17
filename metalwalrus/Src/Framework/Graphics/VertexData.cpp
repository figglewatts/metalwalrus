#include "VertexData.h"

#include <GL/glew.h>

namespace metalwalrus
{
	VertexData::VertexData(float vertices[], unsigned vertNum, GLubyte indices[], unsigned indNum)
	{
		this->vertices.assign(vertices, vertices + (vertNum * 2));
		this->indices.assign(indices, indices + indNum);
		this->load();
	}

	VertexData::~VertexData()
	{
		glDeleteBuffers(1, &vertHandle);
		glDeleteBuffers(1, &indHandle);
	}

	VertexData VertexData::operator=(VertexData & other)
	{
		if (this != &other)
		{
			this->vertices = other.vertices;
			this->indices = other.indices;
			this->load();
		}
		return *this;
	}

	VertexData::VertexData(const VertexData & other)
	{
		this->vertices = other.vertices;
		this->indices = other.indices;
		this->load();
	}

	VertexData *VertexData::create(float vertices[], unsigned vertNum, GLubyte indices[], unsigned indNum)
	{
		return new VertexData(vertices, vertNum, indices, indNum);
	}

	// tell OpenGL about the VertexBuffer
	void VertexData::load()
	{
		if (vertHandle != 0 || indHandle != 0)
		{
			throw std::runtime_error("Vertex buffer already loaded!");
			return;
		}
		
		glGenBuffers(1, &vertHandle);
		bindVertices();
		size_t vertSize = sizeof(vertices[0]) * vertices.size();
		glBufferData(GL_ARRAY_BUFFER, vertSize, vertices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &indHandle);
		bindIndices();
		size_t indSize = sizeof(indices[0]) * indices.size();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize, indices.data(), GL_STATIC_DRAW);
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
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_INDEX_ARRAY);
		
		this->bind();

		// set position in the vertex array
		glVertexPointer(2, GL_FLOAT, 0, 0);

		glDrawElements(GL_QUADS, count * 4, GL_UNSIGNED_BYTE, 0);

		this->unbind();

		glDisableClientState(GL_INDEX_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}