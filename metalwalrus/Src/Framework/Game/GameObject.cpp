#include "GameObject.h"

namespace metalwalrus
{
	int GameObject::numGameObjects;
	
	void GameObject::generateID()
	{
		this->id = numGameObjects;
		numGameObjects++;
	}

	GameObject::GameObject(Vector2 position, float width, float height)
	{
		this->position = position;
		this->width = width;
		this->height = height;
		this->generateID();
	}

	GameObject::GameObject(const GameObject & other)
	{
		this->position = other.position;
		this->width = other.width;
		this->height = other.height;
		this->generateID();
	}

	GameObject & GameObject::operator=(const GameObject & other)
	{
		if (this != &other)
		{
			this->position = other.position;
			this->width = other.width;
			this->height = other.height;
			this->generateID();
		}
		return *this;
	}

	void GameObject::moveBy(Vector2 v)
	{
		this->position += v;
	}

	void GameObject::moveTo(Vector2 v)
	{
		this->position = v;
	}

	Vector2 GameObject::get_center()
	{
		return Vector2(position.x + (width / 2), position.y + (height / 2));
	}
}