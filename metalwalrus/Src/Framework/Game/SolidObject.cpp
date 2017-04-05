#include "SolidObject.h"

namespace metalwalrus
{
	SolidObject::SolidObject(Vector2 position, int width, int height,
		bool usePhysics)
		: GameObject(position, width, height)
	{ }

	SolidObject::SolidObject(const SolidObject & other)
		: GameObject(other)
	{ }

	SolidObject & SolidObject::operator=(const SolidObject & other)
	{
		GameObject::operator=(other);
		return *this;
	}
}