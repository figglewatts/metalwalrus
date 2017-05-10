#ifndef BOUNCINGROBOT_H
#define BOUNCINGROBOT_H
#pragma once

#include "../Enemy.h"

#include "../../../../Framework/State/PushDownStateMachine.h"

namespace metalwalrus
{
	class BouncingRobot : public Enemy
	{
	protected:
		float jumpVelocity; // velocity in y
		float leapVelocity; // velocity in x
		float timeOnGround;
		static Texture2D *bouncerTex;
		static SpriteSheet *bouncerSheet;
		AnimatedSprite *sprite;
		bool onGround;
		bool springExtended;
		Vector2 velocity;
		Vector2 oldPosition;

		PushDownStateMachine<BouncingRobot> machine;

	public:
		BouncingRobot(Vector2 pos, bool isHard, bool facingLeft)
			: Enemy(pos, 16, 16, Vector2::ZERO, isHard, facingLeft,
				isHard ? 4 : 2,
				isHard ? 5 : 2,
				isHard ? 400 : 200)
			, jumpVelocity(isHard ? 40 : 40)
			, leapVelocity(isHard ? 100 : 100)
			, timeOnGround(isHard ? 1.0 : 2.0)
			, onGround(true)
			, springExtended(false)
			, velocity(Vector2::ZERO) { }
		~BouncingRobot()
		{
			delete sprite;
		}

		void start() override;
		void update(double delta) override;
		void draw(SpriteBatch& batch) override;

		AnimatedSprite& get_animatedSprite() const { return *sprite; }
		bool& get_onGround() { return this->onGround; }
		bool& get_springExtended() { return this->springExtended; }
		float get_timeOnGround() const { return this->timeOnGround; }

		void jump();
	};

	class BouncerIdleState : public PushDownState<BouncingRobot>
	{
		float timer;
	public:
		BouncerIdleState(std::string name, PushDownStateMachine<BouncingRobot> *machine)
			: PushDownState(name, machine), timer(0) { }

		void enter(BouncingRobot& b) override;
		void update(double delta, BouncingRobot& b) override;
		void exit(BouncingRobot& b) override;
	};

	class BouncerBouncingState : public PushDownState<BouncingRobot>
	{
	public:
		BouncerBouncingState(std::string name, PushDownStateMachine<BouncingRobot> *machine)
			: PushDownState(name, machine) { }

		void enter(BouncingRobot& b) override;
		void update(double delta, BouncingRobot& b) override;
		void exit(BouncingRobot& b) override;
	};
}

#endif // BOUNCINGROBOT_H