#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "../../../Framework/Game/SolidObject.h"
#include "../../../Framework/Graphics/TileMap.h"
#include "../../../Framework/Animation/AnimatedSprite.h"
#include "../../../Framework/State/PushDownStateMachine.h"
#include "../World/Ladder.h"

namespace metalwalrus
{
	struct PlayerInfo
	{
		bool jumping;
		bool canJump;
		bool facingLeft;
		bool onGround;
		bool moving;
		bool shooting;
		bool canShoot;
		bool canMove;
		bool touchedGroundLastFrame;
		bool damaged;
		bool damagedFromLeft;
		bool canTakeDamage;
		bool alive;
		bool climbing;
		bool canClimb;
		bool facingLeftBeforeDamage;
	};
	
	class Player : public SolidObject
	{
		enum class PlayerState
		{
			IDLE,
			RUNNING,
			IN_AIR,
			DAMAGED
		};

		int health;
		int score;

		PlayerState currentState = PlayerState::IDLE;

		Texture2D *walrusTex;
		SpriteSheet *walrusSheet;

		Texture2D *bulletTex;

		AnimatedSprite *walrusSprite;
		FrameAnimation idle;
		FrameAnimation run;
		FrameAnimation jump;
		FrameAnimation idleShoot;
		FrameAnimation runShoot;
		FrameAnimation jumpShoot;
		FrameAnimation damaged;
		FrameAnimation climbing;
		FrameAnimation climbingShoot;
		FrameAnimation climbingFinish;
		FrameAnimation dead;

		Vector2 oldPosition;

		PlayerInfo playerInfo;

		PushDownStateMachine<Player> playerStateMachine;

		Vector2 velocity;

		// FRAME TIMERS
		int jumpFrameTimer;
		int shootFrameTimer;
		int damageImmunityFrameTimer;
		int deathFrameTimer;

		void shoot();
		void die();
		void handleInput();
		Ladder *checkCanClimb();
	public:
		Player(Vector2 position, float width, float height, Vector2 offset)
			: SolidObject(position, width, height, offset) { }
		~Player();

		void start() override;
		void update(double delta) override;
		void draw(SpriteBatch& batch) override;

		void takeDamage(int damageAmount, GameObject* damager);

		// methods used in modifying player state
		PlayerInfo& get_playerInfo() { return this->playerInfo; }
		AnimatedSprite* const get_animatedSprite() { return this->walrusSprite; }
		Vector2& get_velocity() { return this->velocity; }
		int get_health() const { return this->health; }
		void add_health(int health)
		{
			this->health += health;
			if (this->health > this->maxHealth) this->health = this->maxHealth;
		}
		int get_score() const { return this->score; }
		void add_score(int score) { this->score += score; }

		// ----- PLAYER SETTINGS -----
		const static float walkSpeed;

		const static float climbSpeed;

		const static float jumpSpeed;
		const static int jumpFrames;
		const static int jumpAfterPlatformFrames;
		const static float jumpInAirTolerance;

		const static int framesBetweenShots;
		const static int framesBetweenShotAnimation;

		const static int maxHealth;
		const static int shotDamage;

		const static int damageAnimationFrames;
		const static float damageVelocity;
		const static int damageImmunityFrames;

		const static int framesAfterDeath;
		// ----- END SETTINGS -----
	};
}

#endif // PLAYER_H