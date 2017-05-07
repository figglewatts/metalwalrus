#ifndef FLOATERENEMY_H
#define FLOATERENEMY_H
#pragma once

#include "Enemy.h"

#include "../../../Framework/Animation/AnimatedSprite.h"

namespace metalwalrus
{
	// gradually moves towards the player, damaging on touch
	class FloaterEnemy : public Enemy
	{
	protected:
		float speed; // speed to move towards the player
		static Texture2D *floaterTex;
		static SpriteSheet *floaterSheet;
		AnimatedSprite *sprite;

	public:
		FloaterEnemy(Vector2 pos)
			: Enemy(pos, 16, 16, Vector2::ZERO, 1, 2, 100), speed(0.4F) { }

		void start() override;
		void update(double delta) override;
		void draw(SpriteBatch& batch) override;
	};
}

#endif