#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#pragma once

#include <GL/glew.h>

#include "Texture2D.h"

namespace metalwalrus
{
	class FrameBuffer
	{
		GLuint frameBufferHandle = 0;
		//Texture2D *bufferTex;
		GLuint colorTexHandle = 0;
		GLuint rbo = 0;
		GLuint width, height;

		void load(unsigned width, unsigned height);
	public:
		FrameBuffer(unsigned width, unsigned height);
		FrameBuffer(const FrameBuffer& other);

		~FrameBuffer();

		FrameBuffer operator=(const FrameBuffer& other);

		void bind();
		void unbind();

		GLuint get_color() const { return colorTexHandle; }

		//inline Texture2D *get_BufferTex() const { return bufferTex; }
		//inline unsigned get_width() const { return bufferTex->get_width(); }
		//inline unsigned get_height() const { return bufferTex->get_height(); }
	};
}
#endif