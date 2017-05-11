#include "SceneManager.h"

#include <algorithm>
#include "../Audio/Audio.h"

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
		for (int i = 0; i < scenes.size(); i++)
		{
			if (scenes[i]->get_updateable())
				scenes[i]->update(delta);
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
		Audio::engine->stopAllSounds();
	}
}
