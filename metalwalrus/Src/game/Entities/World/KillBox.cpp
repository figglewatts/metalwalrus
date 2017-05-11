#include "KillBox.h"

#include "../../Scenes/GameScene.h"

namespace metalwalrus
{
	void KillBox::start()
	{
		GameScene::killBoxes.push_back(this);
	}
}
