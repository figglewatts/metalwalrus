#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once

#include "../Math/Vector2.h"

namespace metalwalrus
{
	class GameObject
	{
	protected:
		Vector2 position;
		int width, height;
	public:
		GameObject(Vector2 position, int width, int height);
		GameObject(const GameObject& other);
		virtual ~GameObject() { };

		GameObject& operator=(const GameObject& other);

		virtual void start() = 0;
		virtual void update(double delta) = 0;
		virtual void draw() = 0;

		inline virtual Vector2 get_position() final { return position; }
	};
}

#endif // GAMEOBJECT_H