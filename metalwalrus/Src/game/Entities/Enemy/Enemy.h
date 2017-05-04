#ifndef ENEMY_H
#define ENEMY_H
#pragma once

#include "../../../Framework/Game/SolidObject.h"

namespace metalwalrus
{
	class Enemy : public SolidObject
	{
	protected:
		int health; // shots to kill
		int damage; // amount of damage player takes if they touch the enemy
		bool facingLeft;

	public:
		Enemy(Vector2 position, unsigned width, unsigned height, Vector2 offset,
			int health, int damage)
			: SolidObject(position, width, height, offset, "enemy"), health(health), damage(damage), facingLeft(false) { }
		virtual ~Enemy() { }

		int get_health() const { return health; }
		int get_damage() const { return damage; }

		virtual void die() { };
		void takeDamage(int damageAmount)
		{
			health -= damageAmount;
			if (health <= 0) this->die();
		}
	};
}

#endif // ENEMY_H