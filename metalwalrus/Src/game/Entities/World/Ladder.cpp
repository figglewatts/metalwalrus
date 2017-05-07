#include "Ladder.h"
#include "../../Scenes/GameScene.h"

namespace metalwalrus
{
	std::string const Ladder::staticClassname = "ladder";

	void Ladder::start()
	{
		GameScene::ladders.push_back(this);
	}
}
