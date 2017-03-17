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
		std::vector<float> vertices;
		std::vector<int> indices;

	public:
		VertexData();
		~VertexData();

		void load();
	};
}
#endif