#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#pragma once

#include "../../../Framework/Game/SolidObject.h"
#include "../../Entities/Player/Player.h"

namespace metalwalrus
{
	class EnemyBullet : public SolidObject
	{
		float timer;
		const float lifeTime = 1.5;

		int damage;

		const Vector2 bulletVelocity;
		static Texture2D *bulletTex;
		static Player *p;
	public:
		EnemyBullet(Vector2 pos, Vector2 bulletVelocity, int damage);

		void start() override;
		void update(double delta) override;
		void draw(SpriteBatch& batch) override;
	};
}

#endif