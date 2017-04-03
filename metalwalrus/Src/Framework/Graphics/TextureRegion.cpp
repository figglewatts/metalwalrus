#include "TextureRegion.h"

namespace metalwalrus
{
	TextureRegion::TextureRegion(Texture2D *tex, int x, int y, int w, int h)
	{
		this->texture = tex;
		this->setRegion(x, y, w, h);
	}

	TextureRegion::TextureRegion(const TextureRegion & other)
	{
		*this->texture = *other.texture;
		this->u = other.u;
		this->v = other.v;
		this->u2 = other.u2;
		this->v2 = other.v2;
		this->width = other.width;
		this->height = other.height;
		this->texture->load();
	}

	TextureRegion::~TextureRegion()
	{
		delete texture;
	}

	TextureRegion TextureRegion::operator=(const TextureRegion & other)
	{
		if (this != &other)
		{
			*this->texture = *other.texture;
			this->u = other.u;
			this->v = other.v;
			this->u2 = other.u2;
			this->v2 = other.v2;
			this->width = other.width;
			this->height = other.height;
			this->texture->load();
		}
		return *this;
	}

	void TextureRegion::setRegion(Texture2D *tex)
	{
		this->texture = tex;
		this->setRegion(0, 0, tex->get_width(), tex->get_height());
	}

	void TextureRegion::setRegion(int x, int y, int w, int h)
	{
		float invTexWidth = 1.0F / texture->get_width();
		float invTexHeight = 1.0F / texture->get_height();
		this->setRegion(x * invTexWidth, y * invTexHeight, (x + w) * invTexWidth, (y + h) * invTexHeight);
	}

	void TextureRegion::setRegion(float u, float v, float u2, float v2)
	{
		this->width = (u2 - u) * texture->get_width();
		this->height = (v2 - v) * texture->get_height();
		this->u = u;
		this->v = v;
		this->u2 = u2;
		this->v2 = v2;
	}

	void TextureRegion::scroll(int xAmount, int yAmount)
	{
		if (xAmount != 0)
		{
			this->u = u + ((float)xAmount / (float)texture->get_width());
			this->u2 = u + ((float)width / (float)texture->get_width());
		}
		if (yAmount != 0)
		{
			this->v = v + ((float)yAmount / (float)texture->get_height());
			this->v2 = v + ((float)height / (float)texture->get_height());
		}
	}

	void TextureRegion::changePos(int x, int y)
	{
		this->setRegion(x, y, width, height);
	}

	void TextureRegion::draw()
	{
		this->texture->draw(u, v, u2, v2);
	}
}