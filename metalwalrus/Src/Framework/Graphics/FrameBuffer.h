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
		Texture2D *bufferTex;
		unsigned width, height;

		void load(unsigned width, unsigned height);
	public:
		FrameBuffer(unsigned width, unsigned height);
		FrameBuffer(const FrameBuffer& other);

		~FrameBuffer();

		FrameBuffer operator=(const FrameBuffer& other);


		void bind();
		void unbind();
	};
}
#endif