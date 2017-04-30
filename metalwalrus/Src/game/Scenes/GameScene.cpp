#include "GameScene.h"

#include "../../Framework/Util/JSONUtil.h"
#include "../../Framework/Input/InputHandler.h"

namespace metalwalrus
{
	GameScene::~GameScene()
	{
		delete tileMap;
		delete camera;
		delete batch;
	}

	void GameScene::start()
	{
		// create main SpriteBatch
		batch = new SpriteBatch();

		// create camera
		camera = new Camera();

		tileMap = utilities::JSONUtil::tiled_tilemap("assets/data/level/level1.json", camera);

		player = new Player(Vector2(150, 230), 12, 20, Vector2(11, 0));
		player->updateCollisionEnvironment(tileMap);
		player->start();
		registerObject(player);
	}

	void GameScene::update(double delta)
	{
		for (int i = 0; i < objects.size(); i++)
			objects[i]->update(delta);

		Vector2 playerCenter = player->get_center();
		camera->centerOn(Vector2(playerCenter.x, playerCenter.y));
	}

	void GameScene::draw()
	{
		// set to world coords
		batch->setTransformMat(camera->getTransform());

		batch->begin();

		// draw world
		tileMap->draw(*batch, 16, 17);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->draw(*batch);

		batch->end();
	}
}
