#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "../../Framework/Game/SolidObject.h"
#include "../../Framework/Graphics/TileMap.h"
#include "../../Framework/Animation/AnimatedSprite.h"

namespace metalwalrus
{
	class Player : public SolidObject
	{
		TileMap *currentTilemap; // used for collision

		Texture2D *walrusTex;
		SpriteSheet *walrusSheet;

		AnimatedSprite *walrusSprite;
		FrameAnimation idle;
		FrameAnimation run;
		FrameAnimation jump;

		Vector2 oldPosition;

		bool fullXSpeed = false;
		bool jumping = false;
		bool canJump = false;
		bool facingLeft = false;
		bool onGround = false;

		Vector2 velocity;
		int frameTimer = 0;

		// ----- PLAYER SETTINGS -----
		const static float walkSpeed;

		const static float jumpSpeed;
		const static int jumpFrames;
		const static int jumpAfterPlatformFrames;
		const static float jumpInAirTolerance;

		const static float gravity;
		const static float terminalVelocity;
		// ----- END SETTINGS -----

		bool doCollision(AABB boundingBox);

		void handleInput();
	public:
		Player(Vector2 position, float width, float height, Vector2 offset)
			: SolidObject(position, width, height, offset) { }
		~Player();

		void start() override;
		void update(double delta) override;
		void draw(SpriteBatch& batch) override;

		void updateCollisionEnvironment(TileMap *tileMap);
	};
}

#endif // PLAYER_H