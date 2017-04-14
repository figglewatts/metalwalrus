#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once

#include "../Math/Vector2.h"
#include "../Graphics/SpriteBatch.h"

namespace metalwalrus
{
	class GameObject
	{
	protected:
		Vector2 position;
		float width, height;
	public:
		GameObject(Vector2 position, float width, float height);
		GameObject(const GameObject& other);
		virtual ~GameObject() { };

		GameObject& operator=(const GameObject& other);

		virtual void start() = 0;
		virtual void update(double delta) = 0;
		virtual void draw(SpriteBatch& batch) = 0;

		inline virtual Vector2 get_position() final { return position; }

		virtual void moveBy(Vector2 v);
		virtual void moveTo(Vector2 v);
		virtual Vector2 get_center() final;
	};
}

#endif // GAMEOBJECT_H