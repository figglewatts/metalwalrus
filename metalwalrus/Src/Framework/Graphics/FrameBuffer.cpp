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

		//bufferTex = Texture2D::create(width, height);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);

		glGenFramebuffersEXT(1, &frameBufferHandle);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frameBufferHandle);

		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, 
			colorTexHandle, 0);

		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
			Debug::log("FrameBuffer not loaded!", Debug::LogType::ERR);

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}

	FrameBuffer::FrameBuffer(unsigned width, unsigned height)
	{
		this->load(width, height);
	}

	FrameBuffer::FrameBuffer(const FrameBuffer & other)
    {
        //this->bufferTex = new Texture2D(*other.bufferTex);
        //this->load(other.get_width(), other.get_height());
    }

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffersEXT(1, &frameBufferHandle);
		glDeleteTextures(1, &colorTexHandle);
		
		//delete bufferTex;
	}

	/*FrameBuffer FrameBuffer::operator=(const FrameBuffer & other)
	{
        if (&other != this) 
        {
            this->bufferTex = new Texture2D(*other.bufferTex);
            this->load(other.get_width(), other.get_height());
        }
        return *this;
	}*/

	void FrameBuffer::bind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frameBufferHandle);
		glViewport(0, 0, this->width, this->height);
		//gluOrtho2D(0, this->width, 0, this->height);
	}

	void FrameBuffer::unbind()
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		glViewport(0, 0, Settings::WIDTH, Settings::HEIGHT);
		//gluOrtho2D(0, Settings::WIDTH, 0, Settings::HEIGHT);
	}
}