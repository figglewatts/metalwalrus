#include "LevelFinish.h"

#include "../../Scenes/GameScene.h"

namespace metalwalrus
{
	void LevelFinish::start()
	{
		GameScene::levelFinish.push_back(this);
	}

}