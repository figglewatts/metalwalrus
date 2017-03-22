#include "FrameBuffer.h"

#include <GL/glew.h>

#include "../Util/Debug.h"

#include "../Settings.h"

namespace metalwalrus
{
	void FrameBuffer::load(unsigned width, unsigned height)
	{
		this->width = width;
		this->height = height;

		glGenTextures(1, &colorTexHandle);
		glBindTexture(GL_TEXTURE_2D, colorTexHandle);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, colorTexHandle);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);

		glGenFramebuffers(1, &frameBufferHandle);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
			colorTexHandle, 0);

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
			Debug::log("FrameBuffer not loaded!", Debug::LogType::ERR);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBuffer::FrameBuffer(unsigned width, unsigned height)
	{
		this->load(width, height);
	}

	FrameBuffer::FrameBuffer(const FrameBuffer & other)
    {
		this->load(other.width, other.height);
    }

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &frameBufferHandle);
		glDeleteTextures(1, &colorTexHandle);
	}

	FrameBuffer FrameBuffer::operator=(const FrameBuffer & other)
	{
        if (&other != this) 
        {
			this->load(other.width, other.height);
        }
        return *this;
	}

	void FrameBuffer::bind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);
	}

	void FrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}