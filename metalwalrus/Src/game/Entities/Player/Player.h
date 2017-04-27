#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "../../../Framework/Game/SolidObject.h"
#include "../../../Framework/Graphics/TileMap.h"
#include "../../../Framework/Animation/AnimatedSprite.h"
#include "../../../Framework/State/PushDownStateMachine.h"

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

		PlayerState currentState = PlayerState::IDLE;

		TileMap *currentTilemap; // used for collision

		Texture2D *walrusTex;
		SpriteSheet *walrusSheet;

		AnimatedSprite *walrusSprite;
		FrameAnimation idle;
		FrameAnimation run;
		FrameAnimation jump;
		FrameAnimation idleShoot;
		FrameAnimation runShoot;
		FrameAnimation jumpShoot;

		Vector2 oldPosition;

		PlayerInfo playerInfo;

		PushDownStateMachine<Player> playerStateMachine;

		Vector2 velocity;

		// FRAME TIMERS
		int jumpFrameTimer;
		int shootFrameTimer;

		bool doCollision(AABB boundingBox);

		void newHandleInput();
		void handleInput();
	public:
		Player(Vector2 position, float width, float height, Vector2 offset)
			: SolidObject(position, width, height, offset) { }
		~Player();

		void start() override;
		void update(double delta) override;
		void draw(SpriteBatch& batch) override;

		// methods used in modifying player state
		PlayerInfo& get_playerInfo() { return this->playerInfo; }
		AnimatedSprite* const get_animatedSprite() { return this->walrusSprite; }
		Vector2& get_velocity() { return this->velocity; }

		void updateCollisionEnvironment(TileMap *tileMap);

		// ----- PLAYER SETTINGS -----
		const static float walkSpeed;

		const static float jumpSpeed;
		const static int jumpFrames;
		const static int jumpAfterPlatformFrames;
		const static float jumpInAirTolerance;

		const static float gravity;
		const static float terminalVelocity;

		const static int framesBetweenShots;
		// ----- END SETTINGS -----
	};
}

#endif // PLAYER_H