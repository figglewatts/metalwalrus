#include "Texture2D.h"
#include "../Util/IOUtil.h"
#include "../Util/Debug.h"

namespace metalwalrus
{
	Texture2D::Texture2D(GLuint width, GLuint height, GLint format, GLenum type, GLint minFilter, GLint magFilter, GLint sWrap, GLint tWrap)
	{
		this->data = new std::vector<unsigned char>();
		this->width = width;
		this->height = height;
		this->format = format;
		this->type = type;
		this->minFilter = minFilter;
		this->magFilter = magFilter;
		this->sWrap = sWrap;
		this->tWrap = tWrap;
	}

	Texture2D::Texture2D(std::vector<unsigned char> *data, GLuint width, GLuint height,
		GLint format, GLenum type,
		GLint minFilter, GLint magFilter,
		GLint sWrap, GLint tWrap)
	{
		this->data = data;
		this->width = width;
		this->height = height;
		this->format = format;
		this->type = type;
		this->minFilter = minFilter;
		this->magFilter = magFilter;
		this->sWrap = sWrap;
		this->tWrap = tWrap;
		
		this->load();
	}
	
	Texture2D::Texture2D(std::string filePath,
		GLint format, GLenum type,
		GLint minFilter, GLint magFilter,
		GLint sWrap, GLint tWrap)
	{
		// TODO(sam): Integrate with eventual implementation of resource manager
		this->data = utilities::IOUtil::loadTexture(filePath, this->width, this->height);
		this->format = format;
		this->type = type;
		this->minFilter = minFilter;
		this->magFilter = magFilter;
		this->sWrap = sWrap;
		this->tWrap = tWrap;

		this->load();
	}

	Texture2D::~Texture2D()
	{
		delete data;
		glDeleteTextures(1, &this->glHandle);
	}

	void Texture2D::load()
	{
		if (glHandle != 0)
		{
			throw std::runtime_error("Cannot load texture, already loaded!");
			return;
		}
		
		glGenTextures(1, &glHandle);
		bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data->data());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);

	}

	Texture2D Texture2D::operator=(Texture2D & other)
	{
		if (this != &other)
		{
			this->width = other.width;
			this->height = other.height;
			this->format = other.format;
			*this->data = *other.data;
			this->type = other.type;
			this->minFilter = other.minFilter;
			this->magFilter = other.magFilter;
			this->sWrap = other.sWrap;
			this->tWrap = other.tWrap;
			this->glHandle = other.glHandle;
			load();
		}
		return *this;
	}
	
	bool Texture2D::operator==(const Texture2D& other)
	{
		return this->width == other.width
				&& this->height == other.height
				&& this->format == other.format
				&& *this->data == *other.data
				&& this->type == other.type
				&& this->minFilter == other.minFilter
				&& this->magFilter == other.magFilter
				&& this->sWrap == other.sWrap
				&& this->tWrap == other.tWrap
				&& this->glHandle == other.glHandle;
	}
	
	bool Texture2D::operator!=(const Texture2D& other)
	{
		return !(*this == other);
	}

	Texture2D::Texture2D(const Texture2D & other)
	{
		width = other.width;
		height = other.height;
		format = other.format;
		data = other.data;
		type = other.type;
		minFilter = other.minFilter;
		magFilter = other.magFilter;
		sWrap = other.sWrap;
		tWrap = other.tWrap;
		glHandle = other.glHandle;
		load();
	}

	Texture2D * Texture2D::create(GLuint width, GLuint height)
	{
		return new Texture2D(width, height);
	}

	Texture2D *Texture2D::create(std::string filePath)
	{
		return new Texture2D(filePath);
	}

	Texture2D * Texture2D::create(std::vector<unsigned char>* data, GLuint width, GLuint height)
	{
		return new Texture2D(data, width, height);
	}

	void Texture2D::draw(float u, float v, float u2, float v2)
	{
		glEnable(GL_TEXTURE_2D);
		this->bind();

		glPushMatrix();

		glBegin(GL_QUADS);
			glTexCoord2f(u, v2);	glVertex2f(0, 0);
			glTexCoord2f(u, v);		glVertex2f(0, 50);
			glTexCoord2f(u2, v);	glVertex2f(50, 50);
			glTexCoord2f(u2, v2);	glVertex2f(50, 0);
		glEnd();

		glPopMatrix();

		this->unbind();
	}

	void Texture2D::bind()
	{
		if (this->glHandle == 0)
		{
			Debug::log("Could not bind texture, has not been generated!", Debug::LogType::ERR);
			return;
		}
		glBindTexture(GL_TEXTURE_2D, this->glHandle);
	}

	void Texture2D::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}