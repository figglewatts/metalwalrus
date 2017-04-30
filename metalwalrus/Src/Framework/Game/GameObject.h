#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once

#include "../Math/Vector2.h"
#include "../Graphics/SpriteBatch.h"
#include "../Scene/IScene.h"

namespace metalwalrus
{
	class GameObject
	{
	private:
		static int numGameObjects;
		void generateID();
	protected:
		Vector2 position;
		float width, height;
		int id;
		IScene *parentScene;
	public:
		GameObject(Vector2 position, float width, float height);
		GameObject(const GameObject& other);
		virtual ~GameObject()
		{
			numGameObjects--;
		}

		GameObject& operator=(const GameObject& other);

		virtual void start() = 0;
		virtual void update(double delta) = 0;
		virtual void draw(SpriteBatch& batch) = 0;

		inline virtual Vector2 get_position() final { return position; }
		inline virtual int get_ID() final { return id; }
		inline void set_parentScene(IScene* scene) { parentScene = scene; }

		virtual void moveBy(Vector2 v);
		virtual void moveTo(Vector2 v);
		virtual Vector2 get_center() final;
	};
}

#endif // GAMEOBJECT_H