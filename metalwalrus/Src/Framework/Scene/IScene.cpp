#include "IScene.h"

#include <algorithm>

#include "../Game/GameObject.h"

namespace metalwalrus
{
	void IScene::registerObject(GameObject* obj)
	{
		objects.push_back(obj);
		obj->set_parentScene(this);
		obj->start();
	}

	void IScene::destroyObject(GameObject* obj)
	{
		objects.erase(std::remove(objects.begin(), objects.end(), obj));
		delete obj;
	}

	void IScene::destroyAllObjects()
	{
		for (auto o : objects)
			delete o;
		objects.clear();
	}

	GameObject *IScene::getWithID(int id)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->get_ID() == id)
				return objects[i];
		}
		return nullptr;
	}

	std::vector<GameObject*> IScene::getWithTag(const std::string & tag)
	{
		std::vector<GameObject*> returnVal;
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->get_tag() == tag)
				returnVal.push_back(objects[i]);
		}
		return returnVal;
	}
}