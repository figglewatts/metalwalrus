#ifndef VERTEX_H
#define VERTEX_H
#pragma once

#include <GL/glut.h>
#include <vector>

namespace metalwalrus
{
	class VertexData
	{
		GLuint vertHandle = 0;
		GLuint indHandle = 0;
		std::vector<float> vertices;
		std::vector<int> indices;
		void bindVertices();
		void bindIndices();

	public:
		VertexData(float vertices[], unsigned vertNum, GLubyte indices[], unsigned indNum);
		~VertexData();

		void load();

		void bind();
		void unbind();

		void draw(int count);
	};
}
#endif