#ifndef VERTEXDATA_H
#define VERTEXDATA_H
#pragma once

#include <GL/glew.h>
#include <vector>

#include "Vertex.h"
#include "../Math/Vector2.h"

namespace metalwalrus
{
	class VertexData
	{
		GLuint vertHandle = 0;
		GLuint indHandle = 0;
		std::vector<VertData2D> vertices;
		std::vector<GLuint> indices;
		void bindVertices();
		void bindIndices();

		VertexData(VertData2D vertices[], unsigned vertNum, GLuint indices[], unsigned indNum);

	public:
		~VertexData();

		VertexData operator=(VertexData& other);

		VertexData(const VertexData& other); // copy constructor

		static VertexData *create(VertData2D vertices[], unsigned vertNum, GLuint indices[], unsigned indNum);

		void load();

		void bind();
		void unbind();

		void draw(int count);

		
	};
}
#endif