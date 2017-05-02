#include "PlayerSpawn.h"
#include "../Player/Player.h"
#include "../../Scenes/GameScene.h"

namespace metalwalrus
{
	const std::string PlayerSpawn::staticClassname = "player_spawn";

	PlayerSpawn::PlayerSpawn(Vector2 position, picojson::value properties)
		: WorldObject(position, "player_spawn", properties)
	{
		this->facingLeft = properties.get("facingLeft").get<bool>();
	}

	void PlayerSpawn::start()
	{
		Player *p = new Player(this->position, 12, 20, Vector2(11, 0));
		p->updateCollisionEnvironment(GameScene::loadedMap);
		this->parentScene->registerObject(p);
		GameScene::playerID = p->get_ID();
	}
	void PlayerSpawn::update(double delta)
	{}
	void PlayerSpawn::draw(SpriteBatch & batch)
	{}
}
