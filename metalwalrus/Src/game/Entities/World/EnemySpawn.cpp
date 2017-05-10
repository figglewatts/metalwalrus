#include "EnemySpawn.h"
#include "../Enemy/Floater/FloaterEnemy.h"
#include "../Enemy/StationaryShooter/StationaryShooter.h"
#include "../Enemy/BouncingRobot/BouncingRobot.h"
#include "../Enemy/RobotShooter/RobotShooter.h"

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
			this->parentScene->registerObject(new FloaterEnemy(this->position, this->hardEnemy, this->facingLeft));
		else if (enemyType == "shooter")
			this->parentScene->registerObject(new StationaryShooter(this->position, this->hardEnemy, this->facingLeft));
		else if (enemyType == "bouncing")
			this->parentScene->registerObject(new BouncingRobot(this->position, this->hardEnemy, this->facingLeft));
		else if (enemyType == "robot")
			this->parentScene->registerObject(new RobotShooter(this->position, this->hardEnemy, this->facingLeft));
	}
}
