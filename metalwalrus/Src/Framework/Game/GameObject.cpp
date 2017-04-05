#include "GameObject.h"

namespace metalwalrus
{
	GameObject::GameObject(Vector2 position, int width, int height)
	{
		this->position = position;
		this->width = width;
		this->height = height;
	}

	GameObject::GameObject(const GameObject & other)
	{
		this->position = other.position;
		this->width = other.width;
		this->height = other.height;
	}

	GameObject & GameObject::operator=(const GameObject & other)
	{
		if (this != &other)
		{
			this->position = other.position;
			this->width = other.width;
			this->height = other.height;
		}
		return *this;
	}
}