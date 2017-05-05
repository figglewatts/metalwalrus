#include "GameScene.h"

#include "../../Framework/Util/JSONUtil.h"
#include "../../Framework/Input/InputHandler.h"
#include "../Entities/World/WorldObjectFactory.h"

#include "../Entities/Enemy/FloaterEnemy.h"
#include "../../Framework/Util/Debug.h"

namespace metalwalrus
{
	TileMap *GameScene::loadedMap = nullptr;
	int GameScene::playerID = -1;
	vector<GameObject*> *GameScene::enemies;

	GameObject *player = nullptr;

	FloaterEnemy *e;
	Texture2D *eTex;
	SpriteSheet *eSheet;
	AnimatedSprite *eSprite;
	
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

		delete eTex;
		delete eSheet;
		delete eSprite;

		delete enemies;
	}

	void GameScene::start()
	{
		// create main SpriteBatch
		batch = new SpriteBatch();

		// create camera
		camera = new Camera();

		enemies = new std::vector<GameObject*>();

		loadedMap = utilities::JSONUtil::tiled_tilemap("assets/data/level/level1.json", camera);

		loadMapObjects();

		player = this->getWithID(playerID);

		eTex = Texture2D::create("assets/sprite/smallEnemies.png");
		eSheet = new SpriteSheet(eTex, 16, 16);
		eSprite = new AnimatedSprite(eSheet);
		FrameAnimation eAnim = FrameAnimation(6, 0, 0.2F);
		eSprite->addAnimation("main", eAnim);
		eSprite->play("main");
		e = new FloaterEnemy(Vector2(100, 100), eSprite);
		this->registerObject(e);
		this->registerObject(new FloaterEnemy(Vector2(200, 200), eSprite));
		this->registerObject(new FloaterEnemy(Vector2(300, 300), eSprite));
	}

	void GameScene::update(double delta)
	{
		*enemies = this->getWithTag("enemy");

		for (GameObject* e : *enemies)
			((Enemy*)e)->damagePlayer();

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

		if (Debug::debugMode)
		{
			for (int i = 0; i < objects.size(); i++)
				objects[i]->drawDebug();
		}

		batch->end();

		
	}
}
