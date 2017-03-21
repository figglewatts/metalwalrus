#include "FrameBuffer.h"

#include <GL/glew.h>

namespace metalwalrus
{
	void FrameBuffer::load(unsigned width, unsigned height)
	{
		glGenFramebuffers(1, &frameBufferHandle);
		bufferTex = Texture2D::create(0, width, height);
	}

	FrameBuffer::FrameBuffer(unsigned width, unsigned height)
	{
		this->width = width;
		this->height = height;
		this->load(width, height);
	}

	FrameBuffer::FrameBuffer(const FrameBuffer & other)
        {
            this->bufferTex = new Texture2D(*other.bufferTex);
            this->height = other.height;
            this->width = other.width;
            this->load(this->width, this->height);
        }


	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &frameBufferHandle);
	}

	FrameBuffer FrameBuffer::operator=(const FrameBuffer & other)
	{
            if (&other != this) 
            {
                this->bufferTex = new Texture2D(*other.bufferTex);
                this->height = other.height;
                this->width = other.width;
                this->load(this->width, this->height);
            }
            return *this;
	}

	void FrameBuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);
	}

	void FrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}