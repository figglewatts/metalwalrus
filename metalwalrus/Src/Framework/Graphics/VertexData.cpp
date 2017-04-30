#include "VertexData.h"

#include <stdexcept>
#include "../Util/GLError.h"

namespace metalwalrus
{
	VertexData::VertexData(VertData2D vertices[], unsigned vertNum, GLuint indices[], unsigned indNum)
	{
		this->vertices = new std::vector<VertData2D>();
		this->indices = new std::vector<GLuint>();
		this->vertices->assign(vertices, vertices + vertNum);
		this->indices->assign(indices, indices + indNum);
		this->load();
	}
	
	VertexData::VertexData(std::vector<VertData2D>* vertices, std::vector<GLuint>* indices)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->load();
	}

	VertexData::~VertexData()
	{
		glDeleteBuffers(1, &vertHandle);
		glDeleteBuffers(1, &indHandle);
		//delete vertices;
		//delete indices;
	}

	VertexData VertexData::operator=(VertexData & other)
	{
		if (this != &other)
		{
			*this->vertices = *other.vertices;
			*this->indices = *other.indices;
			this->load();
		}
		return *this;
	}

	VertexData::VertexData(const VertexData & other)
	{
		this->vertices = new std::vector<VertData2D>();
		this->indices = new std::vector<GLuint>();
		*this->vertices = *other.vertices;
		*this->indices = *other.indices;
		this->load();
	}

	VertexData *VertexData::create(VertData2D vertices[], unsigned vertNum, GLuint indices[], unsigned indNum)
	{
		return new VertexData(vertices, vertNum, indices, indNum);
	}
	
	VertexData *VertexData::create(std::vector<VertData2D>* vertices, std::vector<GLuint>* indices)
	{
		return new VertexData(vertices, indices);
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
		size_t vertSize = sizeof(VertData2D) * vertices->capacity();
		glBufferData(GL_ARRAY_BUFFER, vertSize, vertices->data(), GL_DYNAMIC_DRAW);

		// Create IBO
		glGenBuffers(1, &indHandle);
		bindIndices();
		size_t indSize = sizeof(GLuint) * indices->capacity();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize, indices->data(), GL_DYNAMIC_DRAW);

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

		glDrawElements(GL_QUADS, count * 4, GL_UNSIGNED_INT, 0);
		
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		
		this->unbind();
	}
	
	void VertexData::updateContents()
	{
		bindVertices();
		size_t vertSize = sizeof(VertData2D) * vertices->capacity();
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertSize, vertices->data());
		
		bindIndices();
		size_t indSize = sizeof(GLuint) * indices->capacity();
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indSize, indices->data());
		unbind();
	}
}
