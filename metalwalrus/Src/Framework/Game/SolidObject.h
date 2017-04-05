#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#pragma once

#include "GameObject.h"

#include "../Physics/AABB.h"

namespace metalwalrus
{
	class SolidObject : public GameObject
	{
		AABB boundingBox;
	public:
		SolidObject(Vector2 position, int width, int height,
			bool usePhysics);
		SolidObject(const SolidObject& other);

		SolidObject& operator=(const SolidObject& other);

		virtual void start() = 0;
		virtual void update(double delta) = 0;
		virtual void draw() = 0;
	};
}

#endif // PHYSICSOBJECT_H