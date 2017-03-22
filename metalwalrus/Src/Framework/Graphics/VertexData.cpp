#include "VertexData.h"

#include <GL/glew.h>

#include <stdexcept>

namespace metalwalrus
{
	VertexData::VertexData(VertData2D vertices[], unsigned vertNum, GLubyte indices[], unsigned indNum)
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

	VertexData *VertexData::create(VertData2D vertices[], unsigned vertNum, GLubyte indices[], unsigned indNum)
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
		
		// Create VBO
		glGenBuffers(1, &vertHandle);
		bindVertices();
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(VertData2D), vertices.data(), GL_STATIC_DRAW);

		// Create IBO
		glGenBuffers(1, &indHandle);
		bindIndices();
		size_t indSize = sizeof(indices[0]) * indices.size();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize, indices.data(), GL_STATIC_DRAW);

		unbind();
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
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		bindVertices();

		//Set texture coordinate data
		glTexCoordPointer(2, GL_FLOAT, sizeof(VertData2D), (GLvoid*)offsetof(VertData2D, texCoord));

		//Set vertex data
		glVertexPointer(2, GL_FLOAT, sizeof(VertData2D), (GLvoid*)offsetof(VertData2D, pos));

		bindIndices();

		glDrawElements(GL_QUADS, count * 4, GL_UNSIGNED_BYTE, 0);

		
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		
		/*
		this->bind();

		// set position in the vertex array
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, 0);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);


		glDrawElements(GL_QUADS, count * 4, GL_UNSIGNED_BYTE, 0);

		this->unbind();

		glDisableClientState(GL_INDEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);*/
	}
}