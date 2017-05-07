#include "EnemySpawn.h"
#include "../Enemy/FloaterEnemy.h"

namespace metalwalrus
{
	std::string EnemySpawn::staticClassname = "enemy_spawn";
	
	EnemySpawn::EnemySpawn(Vector2 position, picojson::value properties)
		: WorldObject(position, 16, 16, "enemy_spawn", properties)
	{
		this->enemyType = properties.get("enemyType").get<std::string>();
	}
	
	void EnemySpawn::start()
	{
		if (enemyType == "floater")
			this->parentScene->registerObject(new FloaterEnemy(this->position));
	}
}
