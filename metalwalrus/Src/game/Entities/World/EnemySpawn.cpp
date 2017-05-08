#include "EnemySpawn.h"
#include "../Enemy/Floater/FloaterEnemy.h"
#include "../Enemy/StationaryShooter/StationaryShooter.h"

namespace metalwalrus
{
	std::string EnemySpawn::staticClassname = "enemy_spawn";
	
	EnemySpawn::EnemySpawn(Vector2 position, picojson::value properties)
		: WorldObject(position, 16, 16, "enemy_spawn", properties)
	{
		this->enemyType = properties.get("enemyType").get<std::string>();
		this->facingLeft = properties.get("facingLeft").get<bool>();
		this->hardEnemy = properties.get("hardEnemy").get<bool>();
	}
	
	void EnemySpawn::start()
	{
		if (enemyType == "floater")
			this->parentScene->registerObject(new FloaterEnemy(this->position, this->hardEnemy));
		else if (enemyType == "shooter")
			this->parentScene->registerObject(new StationaryShooter(this->position, this->hardEnemy));
	}
}
