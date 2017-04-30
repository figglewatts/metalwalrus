#include "IScene.h"

#include <algorithm>

#include "../Game/GameObject.h"

namespace metalwalrus
{
	void IScene::registerObject(GameObject* obj)
	{
		objects.push_back(obj);
		obj->set_parentScene(this);
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
}