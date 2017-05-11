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
		int bulletSpeed = 10;
		static Texture2D *shooterTex;
		static SpriteSheet *shooterSheet;
		AnimatedSprite *sprite;
		bool shooting;
		bool shootingUp;
		bool open;

		PushDownStateMachine<StationaryShooter> machine;
	public:
		StationaryShooter(Vector2 pos, bool isHard, bool facingLeft)
			: Enemy(pos, 16, 16, Vector2::ZERO, isHard, facingLeft,
				isHard ? 4 : 2,
				isHard ? 4 : 2,
				isHard ? 200 : 100)
			, shotCooldownFrames(isHard ? 40 : 80)
			, shooting(false)
			, shootingUp(false)
			, sprite(nullptr)
			, open(false)
			, bulletSpeed(100) { }
		~StationaryShooter()
		{
			delete sprite;
		}

		void start() override;
		void update(double delta) override;
		void draw(SpriteBatch& batch) override;

		void shoot();

		AnimatedSprite& get_animatedSprite() const { return *sprite; }
		bool& get_shooting() { return shooting; }
		bool& get_shootingUp() { return shootingUp; }
		int get_shotCooldownFrames() const { return shotCooldownFrames; }
		bool& get_isOpen() { return open; }
	};

	class ShooterIdleState : public PushDownState<StationaryShooter>
	{
		int frameTimer;
	public:
		ShooterIdleState(std::string name, PushDownStateMachine<StationaryShooter> *machine)
			: PushDownState(name, machine), frameTimer(0) { }

		void enter(StationaryShooter& s) override;
		void update(double delta, StationaryShooter& s) override;
		void exit(StationaryShooter& s) override;
	};

	class ShooterShootState : public PushDownState<StationaryShooter>
	{
		int frameTimer;
	public:
		ShooterShootState(std::string name, PushDownStateMachine<StationaryShooter> *machine)
			: PushDownState(name, machine), frameTimer(0) { }
		
		void enter(StationaryShooter& s) override;
		void update(double delta, StationaryShooter& s) override;
		void exit(StationaryShooter& s) override;
	};
}

#endif // STATIONARYSHOOTER_H