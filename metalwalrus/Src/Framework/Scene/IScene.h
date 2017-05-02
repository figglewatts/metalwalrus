#ifndef SCENE_H
#define SCENE_H
#pragma once

#include <vector>

namespace metalwalrus
{
	class GameObject; // forward declaration
	
	class IScene
	{
	protected:
		std::vector<GameObject*> objects;
	public:
		virtual ~IScene()
		{
			destroyAllObjects();
		}

		virtual void start() = 0;
		virtual void update(double delta) = 0;
		virtual void draw() = 0;

		void registerObject(GameObject *obj);
		void destroyObject(GameObject *obj);
		void destroyAllObjects();
		GameObject *getWithID(int id);
	};
}

#endif // SCENE_H