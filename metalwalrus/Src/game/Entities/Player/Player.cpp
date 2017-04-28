#include "Player.h"

#include "../../../Framework/Graphics/Texture2D.h"
#include "../../../Framework/Input/InputHandler.h"

#include "States.h"

namespace metalwalrus
{
	const float Player::walkSpeed = 1.5;

	const float Player::jumpSpeed = 4;
	const int Player::jumpFrames = 11;
	const int Player::jumpAfterPlatformFrames = 7;
	const float Player::jumpInAirTolerance = 2;

	const float Player::gravity = 0.5;
	const float Player::terminalVelocity = -4;

	const int Player::framesBetweenShots = 30;
	const int Player::framesBetweenShotAnimation = 60;

	bool Player::doCollision(AABB boundingBox, AABB& tbb)
	{
		int leftTile = boundingBox.get_left()
			/ currentTilemap->get_sheets()[0]->get_spriteWidth();
		int rightTile = boundingBox.get_right()
			/ currentTilemap->get_sheets()[0]->get_spriteWidth();
		int topTile = boundingBox.get_top()
			/ currentTilemap->get_sheets()[0]->get_spriteHeight();
		int bottomTile = boundingBox.get_bottom()
			/ currentTilemap->get_sheets()[0]->get_spriteHeight();

		if (leftTile < 0) leftTile = 0;
		if (rightTile >= currentTilemap->get_width())
			rightTile = currentTilemap->get_width() - 1;
		if (bottomTile < 0) bottomTile = 0;
		if (topTile >= currentTilemap->get_height())
			topTile = currentTilemap->get_height() - 1;

		for (int i = leftTile; i <= rightTile; i++)
		{
			for (int j = bottomTile; j <= topTile; j++)
			{
				Tile t = currentTilemap->get(i, j, 1);
				if (t.is_solid())
				{
					tbb = t.get_boundingBox();
					return true;
				}
			}
		}
		return false;
	}

	void Player::newHandleInput()
	{
		if (!playerInfo.canMove) 
			return;
		
		if (InputHandler::checkButton("left", ButtonState::HELD))
		{
			velocity.x = -walkSpeed;
			playerInfo.facingLeft = true;
			playerInfo.moving = true;
		}

		// left and right movement
		if (InputHandler::checkButton("right", ButtonState::HELD))
		{
			velocity.x = walkSpeed;
			playerInfo.facingLeft = false;
			playerInfo.moving = true;
		}

		if (InputHandler::checkButton("left", ButtonState::IDLE)
			&& InputHandler::checkButton("right", ButtonState::IDLE))
		{
			velocity.x = 0;
			playerInfo.moving = false;
		}

		// shooting
		if (playerInfo.canShoot)
		{
			if (InputHandler::checkButton("space", ButtonState::DOWN))
			{
				playerInfo.shooting = true;

				// TODO: fire a bullet
			}
		}

		// jumping
		if (playerInfo.canJump)
		{
			if (InputHandler::checkButton("up", ButtonState::DOWN))
			{
				velocity.y = jumpSpeed;
				playerInfo.jumping = true;
				playerInfo.canJump = false;
				playerInfo.onGround = false;
				jumpFrameTimer = jumpFrames;
			}
		}
		if (playerInfo.jumping)
		{
			if (InputHandler::checkButton("up", ButtonState::HELD))
			{
				velocity.y = jumpSpeed;
				jumpFrameTimer--;
				if (jumpFrameTimer <= 0)
				{
					playerInfo.jumping = false;
				}
			}
		}
	}

	/*void Player::handleInput()
	{
		
		// left and right movement
		if (InputHandler::checkButton("right", ButtonState::HELD))
		{
			velocity.x = walkSpeed;
			playerInfo.facingLeft = false;
			if (playerInfo.onGround)
			{
				currentState = PlayerState::RUNNING;
				walrusSprite->play("run");
			}
			
		}
		else if (InputHandler::checkButton("right", ButtonState::IDLE)
			&& velocity.x >= 0)
		{
			velocity.x = 0;
			if (playerInfo.onGround)
			{
				currentState = PlayerState::IDLE;
				walrusSprite->play("idle");
			}
		}
		if (InputHandler::checkButton("left", ButtonState::HELD))
		{
			velocity.x = -walkSpeed;
			playerInfo.facingLeft = true;
			if (playerInfo.onGround)
			{
				currentState = PlayerState::RUNNING;
				walrusSprite->play("run");
			}
		}
		else if (InputHandler::checkButton("left", ButtonState::IDLE)
			&& velocity.x <= 0)
		{
			velocity.x = 0;
			if (playerInfo.onGround)
			{
				currentState = PlayerState::IDLE;
				walrusSprite->play("idle");
			}
		}

		// jumping
		if (playerInfo.canJump && InputHandler::checkButton("up", ButtonState::DOWN))
		{
			velocity.y = jumpSpeed;
			playerInfo.jumping = true;
			playerInfo.canJump = false;
			frameTimer = 0;
			currentState = PlayerState::IN_AIR;
		}
		if (playerInfo.jumping && InputHandler::checkButton("up", ButtonState::HELD))
		{
			if (frameTimer < jumpFrames)
				velocity.y = jumpSpeed;
			else
				playerInfo.jumping = false;
			frameTimer++;
		}
		if (InputHandler::checkButton("up", ButtonState::IDLE))
		{
			playerInfo.jumping = false;
		}

		if (InputHandler::checkButton("space", ButtonState::DOWN))
		{
			switch (currentState)
			{
				case PlayerState::IDLE:
				{
					walrusSprite->playForFrames("idleShoot", shootingAnimationFrames);
				} break;
				case PlayerState::RUNNING:
				{
					int runningFrame = 
						walrusSprite->get_currentAnim().get_currentFrameRelative();
					walrusSprite->playAtFrame("runShoot", runningFrame);
				} break;
				case PlayerState::IN_AIR:
				{
					walrusSprite->playForFrames("jumpShoot", shootingAnimationFrames);
				} break;
			}
		}
	}*/

	Player::~Player()
	{
		delete walrusTex;
		delete walrusSheet;
		delete walrusSprite;
	}

	void Player::start()
	{
		walrusTex = Texture2D::create("assets/sprite/walrus.png");
		walrusSheet = new SpriteSheet(walrusTex, 32, 32);
		walrusSprite = new AnimatedSprite(walrusSheet);
		idle = FrameAnimation(0, 0, 0);
		run = FrameAnimation(4, 1, 0.2);
		jump = FrameAnimation(0, 5, 0);
		idleShoot = FrameAnimation(0, 8, 0, "idle");
		runShoot = FrameAnimation(4, 9, 0.2, "run");
		jumpShoot = FrameAnimation(0, 13, 0, "jump");
		walrusSprite->addAnimation("idle", idle);
		walrusSprite->addAnimation("run", run);
		walrusSprite->addAnimation("jump", jump);
		walrusSprite->addAnimation("idleShoot", idleShoot);
		walrusSprite->addAnimation("runShoot", runShoot);
		walrusSprite->addAnimation("jumpShoot", jumpShoot);
		walrusSprite->play("idle");

		playerInfo.canJump = false;
		playerInfo.canMove = true;
		playerInfo.canShoot = true;
		playerInfo.facingLeft = false;
		playerInfo.jumping = false;
		playerInfo.moving = false;
		playerInfo.onGround = false;
		playerInfo.shooting = false;
		playerInfo.touchedGroundLastFrame = false;

		playerStateMachine.push(new IdleState("idle", &playerStateMachine), *this);
	}

	void Player::update(double delta)
	{
		newHandleInput();

		velocity.y -= gravity;

		if (velocity.y < terminalVelocity) velocity.y = terminalVelocity;

		oldPosition = position;
		AABB tbb;
		moveBy(Vector2(velocity.x, 0));
		if (doCollision(boundingBox, tbb))
		{
			moveTo(oldPosition);
		}

		oldPosition = position;
		moveBy(Vector2(0, velocity.y));
		if (doCollision(boundingBox, tbb))
		{
			moveTo(Vector2(oldPosition.x, velocity.y < 0 ? tbb.get_top() : (tbb.get_bottom() - boundingBox.get_height())));

			if (velocity.y < 0)
			{
				playerInfo.onGround = true;
				playerInfo.touchedGroundLastFrame = true;
			}

			velocity.y = 0;
			playerInfo.jumping = false;
		}
		else
		{
			if (!playerInfo.touchedGroundLastFrame)
				playerInfo.onGround = false;

			playerInfo.touchedGroundLastFrame = false;
		}
		

		walrusSprite->update(delta);

		playerStateMachine.update(delta, *this);

		/*
		velocity.y -= gravity;

		if (velocity.y < terminalVelocity) velocity.y = terminalVelocity;
		
		oldPosition = position;
		moveBy(Vector2(velocity.x, 0));
		if (doCollision(boundingBox))
		{
			moveTo(oldPosition);
		}

		oldPosition = position;
		moveBy(Vector2(0, velocity.y));
		if (doCollision(boundingBox))
		{
			if (velocity.y < 0)
			{
				playerInfo.onGround = true;
				playerInfo.canJump = true;
				currentState = PlayerState::IDLE;
			}
			playerInfo.jumping = false;
			frameTimer = 0;
			velocity.y = 0;
			moveTo(oldPosition);
		}
		else if (!playerInfo.jumping)
		{
			if (frameTimer > jumpAfterPlatformFrames)
			{
				playerInfo.canJump = false;
			}
			else
			{
				frameTimer++;
			}
			playerInfo.onGround = false;
			currentState = PlayerState::IN_AIR;
			walrusSprite->play("jump");
		}
		else
		{
			playerInfo.onGround = false;
			playerInfo.canJump = false;

			// jump tolerance calculation
			if (!playerInfo.canJump &&
				doCollision(boundingBox + Vector2(0, -jumpInAirTolerance)))
			{
				playerInfo.canJump = true;
				frameTimer = 0;
			}

			currentState = PlayerState::IN_AIR;
			walrusSprite->play("jump");
		}
		*/
	}

	void Player::draw(SpriteBatch& batch)
	{
		TextureRegion *walrusKeyframe = walrusSprite->get_keyframe();
		walrusKeyframe->set_flipX(playerInfo.facingLeft);
		
		batch.drawreg(*walrusKeyframe, position.x, position.y);
	}

	void Player::updateCollisionEnvironment(TileMap *tileMap)
	{
		this->currentTilemap = tileMap;
	}
}
