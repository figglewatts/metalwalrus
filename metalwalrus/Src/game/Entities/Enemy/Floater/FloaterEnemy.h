#ifndef FLOATERENEMY_H
#define FLOATERENEMY_H
#pragma once

#include "../Enemy.h"

#include "../../../../Framework/Animation/AnimatedSprite.h"

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
		FloaterEnemy(Vector2 pos, bool isHard, bool facingLeft)
			: Enemy(pos, 16, 16, Vector2::ZERO, isHard, facingLeft,
				isHard ? 2 : 1, 
				isHard ? 6 : 3, 
				isHard ? 400 : 100)
			, speed(isHard ? 0.6F : 0.4F) { }
		~FloaterEnemy()
		{
			delete sprite;
		}

		void start() override;
		void update(double delta) override;
		void draw(SpriteBatch& batch) override;
	};
}

#endif // FLOATERENEMY_H