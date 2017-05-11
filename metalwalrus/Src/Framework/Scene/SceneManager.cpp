#include "SceneManager.h"

#include <algorithm>

namespace metalwalrus
{
	std::vector<IScene*> SceneManager::scenes;
	
	void SceneManager::addScene(IScene *scene)
	{
		scenes.push_back(scene);
		scene->start();
	}

	void SceneManager::removeScene(IScene *scene)
	{
		scenes.erase(std::remove(scenes.begin(), scenes.end(), scene));
		delete scene;
	}

	void SceneManager::update(double delta)
	{
		for (auto scene : scenes)
		{
			if (scene->get_updateable())
				scene->update(delta);
		}
	}

	void SceneManager::draw()
	{
		for (auto scene : scenes)
		{
			scene->draw();
		}
	}

	void SceneManager::switchScene(IScene *scene)
	{
		clearScenes();
		addScene(scene);
	}

	void SceneManager::clearScenes()
	{
		for (auto s : scenes)
			delete s;
		scenes.clear();
	}
}