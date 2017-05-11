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
		bool updateable;
	public:
		virtual ~IScene()
		{
			destroyAllObjects();
		}

		virtual void start() = 0;
		virtual void update(double delta) = 0;
		virtual void draw() = 0;

		bool get_updateable() const { return updateable; }

		void registerObject(GameObject *obj);
		void destroyObject(GameObject *obj);
		void destroyAllObjects();
		GameObject *getWithID(int id);
		std::vector<GameObject*> getWithTag(const std::string& tag);
	};
}

#endif // SCENE_H