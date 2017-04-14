#include "SolidObject.h"

namespace metalwalrus
{
	void SolidObject::recomputeBoundingBox()
	{
		this->boundingBox += (this->position - this->boundingBox.get_min());
		boundingBox += boundingBoxOffset;
	}

	SolidObject::SolidObject(Vector2 position, float width, float height,
		Vector2 offset)
		: GameObject(position, width, height)
	{
		this->boundingBoxOffset = offset;
		this->boundingBox = AABB(position + offset, 
			Vector2(position.x + width + offset.x, 
				position.y + height + offset.y));
	}

	SolidObject::SolidObject(const SolidObject & other)
		: GameObject(other)
	{
		this->boundingBox = other.boundingBox;
		this->boundingBoxOffset = other.boundingBoxOffset;
	}

	SolidObject & SolidObject::operator=(const SolidObject & other)
	{
		GameObject::operator=(other);
		if (this != &other)
		{
			this->boundingBox = other.boundingBox;
			this->boundingBoxOffset = other.boundingBoxOffset;
		}
		return *this;
	}

	void SolidObject::moveTo(Vector2 v)
	{
		GameObject::moveTo(v);
		recomputeBoundingBox();
	}

	void SolidObject::moveBy(Vector2 v)
	{
		GameObject::moveBy(v);
		recomputeBoundingBox();
	}
}