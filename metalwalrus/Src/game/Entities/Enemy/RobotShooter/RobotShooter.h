#ifndef ROBOTSHOOTER_H
#define ROBOTSHOOTER_H
#pragma once
#include "../Enemy.h"

namespace metalwalrus
{
	class RobotShooter : public Enemy
	{
		static Texture2D *robotTex;
		static SpriteSheet *robotSheet;
		const static int SENSE_DISTANCE = 140;
		AnimatedSprite *sprite;
		
		float timeBetweenShots;
		float shotCooldown;
		float bulletSpeed;
		int numberOfShots;

		PushDownStateMachine<RobotShooter> machine;

	public:
		RobotShooter(Vector2 pos, bool isHard, bool facingLeft)
			: Enemy(pos, 15, 30, Vector2(6, 0), isHard, facingLeft,
				isHard ? 6 : 4,
				isHard ? 4 : 3,
				isHard ? 600 : 400)
			, timeBetweenShots(isHard ? 0.1 : 0.2)
			, shotCooldown(isHard ? 0.6 : 1)
			, bulletSpeed(isHard ? 100 : 100)
			, numberOfShots(isHard ? 3 : 3) { }
		~RobotShooter()
		{
			delete sprite;
		}

		void start() override;
		void update(double delta) override;
		void draw(SpriteBatch& batch) override;

		AnimatedSprite& get_animatedSprite() const { return *sprite; }
		float get_timeBetweenShots() const { return timeBetweenShots; }
		float get_shotCooldown() const { return shotCooldown; }
		bool get_playerSensed();
		int get_numberOfShots() const { return numberOfShots; }

		void shoot();
	};

	class RobotIdleState : public PushDownState<RobotShooter>
	{
	public:
		RobotIdleState(std::string name, PushDownStateMachine<RobotShooter> *machine)
			: PushDownState(name, machine) { }

		void enter(RobotShooter& r) override;
		void update(double delta, RobotShooter& r) override;
		void exit(RobotShooter& r) override;
	};

	class RobotShootingState : public PushDownState<RobotShooter>
	{
		float timeBetweenShotsTimer;
		float shotCooldownTimer;
		int shotCount;
	public:
		RobotShootingState(std::string name, PushDownStateMachine<RobotShooter> *machine)
			: PushDownState(name, machine), timeBetweenShotsTimer(0), shotCooldownTimer(0), shotCount(0) { }
		
		void enter(RobotShooter& r) override;
		void update(double delta, RobotShooter& r) override;
		void exit(RobotShooter& r) override;
	};
}

#endif // ROBOTSHOOTER_H