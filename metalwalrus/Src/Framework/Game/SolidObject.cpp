#include "SolidObject.h"

namespace metalwalrus
{
	void SolidObject::recomputeBoundingBox()
	{
		this->boundingBox += (this->position - this->boundingBox.get_min());
		boundingBox += boundingBoxOffset;
	}

	SolidObject::SolidObject(Vector2 position, float width, float height,
		Vector2 offset, std::string tag)
		: GameObject(position, width, height, tag)
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

	void SolidObject::drawDebug()
	{
		glLineWidth(2);
		glColor3f(1, 0, 1);
		glBegin(GL_LINES);
		glVertex2f(this->boundingBox.get_min().x, this->boundingBox.get_min().y);
		glVertex2f(this->boundingBox.get_max().x, this->boundingBox.get_min().y);
		glVertex2f(this->boundingBox.get_max().x, this->boundingBox.get_min().y);
		glVertex2f(this->boundingBox.get_max().x, this->boundingBox.get_max().y);
		glVertex2f(this->boundingBox.get_max().x, this->boundingBox.get_max().y);
		glVertex2f(this->boundingBox.get_min().x, this->boundingBox.get_max().y);
		glVertex2f(this->boundingBox.get_min().x, this->boundingBox.get_max().y);
		glVertex2f(this->boundingBox.get_min().x, this->boundingBox.get_min().y);
		glEnd();
		glColor3f(1, 1, 1);
	}

	void SolidObject::moveBy(Vector2 v)
	{
		GameObject::moveBy(v);
		recomputeBoundingBox();
	}
}