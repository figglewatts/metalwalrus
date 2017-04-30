#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#pragma once

#include "Texture2D.h"

namespace metalwalrus
{
	class FrameBuffer
	{
		GLuint frameBufferHandle = 0;
		GLuint colorTexHandle = 0;
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

		inline GLuint get_width() const { return width; }
		inline GLuint get_height() const { return height; }
		inline GLuint get_handle() const { return frameBufferHandle; }
	};
}
#endif