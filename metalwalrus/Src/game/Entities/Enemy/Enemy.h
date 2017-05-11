#ifndef ENEMY_H
#define ENEMY_H
#pragma once

#include "../../../Framework/Game/SolidObject.h"

#include "../Player/Player.h"
#include "../../Scenes/GameScene.h"
#include "../World/HealthPowerup.h"

#include <ctime>
#include <cstdlib>

namespace metalwalrus
{
	class Enemy : public SolidObject
	{
	protected:
		int health; // shots to kill
		int damage; // amount of damage player takes if they touch the enemy
		int score; // score on kill
		bool facingLeft;
		bool hardEnemy;
		Player *p;

		int healthSpawnChance; // chance of health spawn on kill (out of 100)
		int healthBigChance; // chance of big health spawn on health spawn

	public:
		Enemy(Vector2 position, unsigned width, unsigned height, Vector2 offset,
			bool isHard, bool facingLeft, int health, int damage, int score);
		virtual ~Enemy() { }

		int get_health() const { return health; }
		int get_damage() const { return damage; }

		virtual void die();
		void takeDamage(int damageAmount);

		void damagePlayer();
	};
}

#endif // ENEMY_H