#ifndef ENEMY_H
#define ENEMY_H
#pragma once

#include "../../../Framework/Game/SolidObject.h"

#include "../Player/Player.h"
#include "../../Scenes/GameScene.h"

namespace metalwalrus
{
	class Enemy : public SolidObject
	{
	protected:
		int health; // shots to kill
		int damage; // amount of damage player takes if they touch the enemy
		bool facingLeft;
		Player *p;

	public:
		Enemy(Vector2 position, unsigned width, unsigned height, Vector2 offset,
			int health, int damage)
			: SolidObject(position, width, height, offset, "enemy"), health(health), damage(damage), facingLeft(false)
			, p(nullptr) { }
		virtual ~Enemy() { }

		int get_health() const { return health; }
		int get_damage() const { return damage; }

		virtual void die() { };
		void takeDamage(int damageAmount)
		{
			health -= damageAmount;
			if (health <= 0) this->die();
		}

		void damagePlayer()
		{
			if (p == nullptr)
				p = ((Player*)this->parentScene->getWithID(GameScene::playerID));
			
			if (this->boundingBox.intersects(p->get_boundingBox()))
				p->takeDamage(this->damage, this);
		}
	};
}

#endif // ENEMY_H