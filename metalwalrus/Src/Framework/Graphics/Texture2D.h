#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#pragma once

#include <vector>
#include <GL/glew.h>

namespace metalwalrus
{
	class Texture2D
	{
		GLuint width;
		GLuint height;
		GLint format;
		std::vector<unsigned char> *data;
		GLenum type;
		GLint minFilter;
		GLint magFilter;
		GLint sWrap;
		GLint tWrap;
		GLuint glHandle = 0;

		Texture2D(std::vector<unsigned char> *data, GLuint width, GLuint height,
			GLint format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE,
			GLint minFilter = GL_NEAREST, GLint magFilter = GL_NEAREST,
			GLint sWrap = GL_CLAMP, GLint tWrap = GL_CLAMP);
		Texture2D(char *filePath,
			GLint format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE,
			GLint minFilter = GL_NEAREST, GLint magFilter = GL_NEAREST,
			GLint sWrap = GL_CLAMP, GLint tWrap = GL_CLAMP);

	public:
		Texture2D operator=(Texture2D& other);

		Texture2D(const Texture2D& other); // copy constructor

		static Texture2D *create(char *filePath);

		void draw(float u = 0, float v = 0, float u2 = 1, float v2 = 1);
		void load();
		void bind();
		void unbind();

		~Texture2D();

		inline GLsizei get_width() const { return width; }
		inline GLsizei get_height() const { return height; }
		inline GLint get_format() const { return format; }
		inline std::vector<unsigned char>* get_data() const { return data; }
		inline GLenum get_type() const { return type; }
		inline GLint get_minFilter() const { return minFilter; }
		inline GLint get_magFilter() const { return magFilter; }
		inline GLint get_sWrap() const { return sWrap; }
		inline GLint get_tWrap() const { return tWrap; }
	};
}
#endif