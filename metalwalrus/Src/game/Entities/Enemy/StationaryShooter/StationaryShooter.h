#ifndef STATIONARYSHOOTER_H
#define STATIONARYSHOOTER_H
#pragma once

#include "../Enemy.h"
#include "../Src/Framework/Animation/FrameAnimation.h"

namespace metalwalrus
{
	class StationaryShooter : public Enemy
	{
	protected:
		int shotCooldownFrames;
		bool shootingUp;
		static Texture2D *shooterTex;
		static SpriteSheet *shooterSheet;
		AnimatedSprite *sprite;
		int shotFrameTimer;
		bool shooting;


		void shoot();
	public:
		StationaryShooter(Vector2 pos, bool isHard)
			: Enemy(pos, 16, 16, Vector2::ZERO, isHard,
				isHard ? 4 : 2,
				isHard ? 2 : 1,
				isHard ? 200 : 100)
			, shotCooldownFrames(isHard ? 20 : 40) { }

		void start() override;
		void update(double delta) override;
		void draw(SpriteBatch& batch) override;


	};
}

#endif // STATIONARYSHOOTER_H