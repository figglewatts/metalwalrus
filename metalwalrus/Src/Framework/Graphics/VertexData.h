#ifndef VERTEX_H
#define VERTEX_H
#pragma once

#include <GL/glew.h>
#include <vector>

namespace metalwalrus
{
	class VertexData
	{
		GLuint vertHandle = 0;
		GLuint indHandle = 0;
		std::vector<GLfloat> vertices;
		std::vector<GLubyte> indices;
		void bindVertices();
		void bindIndices();

		VertexData(float vertices[], unsigned vertNum, GLubyte indices[], unsigned indNum);

	public:
		~VertexData();

		VertexData operator=(VertexData& other);

		VertexData(const VertexData& other); // copy constructor

		static VertexData *create(float vertices[], unsigned vertNum, GLubyte indices[], unsigned indNum);

		void load();

		void bind();
		void unbind();

		void draw(int count);
	};
}
#endif