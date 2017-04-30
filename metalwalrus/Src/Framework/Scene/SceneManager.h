#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#pragma once

#include <vector>

#include "IScene.h"

namespace metalwalrus
{
	class SceneManager
	{
		static std::vector<IScene*> scenes;

		SceneManager();
	public:
		static void addScene(IScene* scene);
		static void removeScene(IScene* scene);
		static void update(double delta);
		static void draw();
		static void switchScene(IScene* scene);
		static void clearScenes();
	};
}

#endif