#include "GameScene.h"

#include "../../Framework/Util/JSONUtil.h"
#include "../../Framework/Input/InputHandler.h"
#include "../Entities/World/WorldObjectFactory.h"

namespace metalwalrus
{
	TileMap *GameScene::loadedMap = nullptr;
	int GameScene::playerID = -1;

	GameObject *player = nullptr;
	
	void GameScene::loadMapObjects()
	{
		TileLayer *objectLayer = loadedMap->get_layer("Entities");
		PropertyContainer *sheetProperties = nullptr;
		WorldObjectFactory woFactory;
		for (int y = 0; y < loadedMap->get_height(); y++)
		{
			for (int x = 0; x < loadedMap->get_width(); x++)
			{
				Tile *t = &objectLayer->get(x, y);

				if (t->get_tileID() == 0) continue;

				if (sheetProperties == nullptr) 
					sheetProperties = &loadedMap->get_sheetFromTileID(t->get_tileID()).properties;

				picojson::value tileProperties = sheetProperties->getTileProperties(t->get_sheetID() - 1);

				Vector2 tilePos = t->get_position();
				std::string classname = tileProperties.get("classname").get<std::string>();
				this->registerObject(woFactory.createObject(classname, tilePos, tileProperties));
			}
		}
	}

	GameScene::~GameScene()
	{
		delete loadedMap;
		delete camera;
		delete batch;
	}

	void GameScene::start()
	{
		// create main SpriteBatch
		batch = new SpriteBatch();

		// create camera
		camera = new Camera();

		loadedMap = utilities::JSONUtil::tiled_tilemap("assets/data/level/level1.json", camera);

		loadMapObjects();

		player = this->getWithID(playerID);
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
		loadedMap->draw(*batch, 16, 17);

		// draw objects
		for (int i = 0; i < objects.size(); i++)
			objects[i]->draw(*batch);

		batch->end();
	}
}
