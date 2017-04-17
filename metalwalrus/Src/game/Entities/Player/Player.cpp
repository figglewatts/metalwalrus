#include "Player.h"

#include "../../../Framework/Graphics/Texture2D.h"
#include "../../../Framework/Input/InputHandler.h"

namespace metalwalrus
{
	const float Player::walkSpeed = 1.5;
	
	const float Player::jumpSpeed = 4;
	const int Player::jumpFrames = 11;
	const int Player::jumpAfterPlatformFrames = 7;
	const float Player::jumpInAirTolerance = 2;

	const float Player::gravity = 0.5;
	const float Player::terminalVelocity = -4;

	const float Player::timeBetweenShots = 0.5;
	const int Player::shootingAnimationFrames = 4;
	
	bool Player::doCollision(AABB boundingBox)
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
						return true;
			}
		}
		return false;
	}

	void Player::handleInput()
	{
		
		// left and right movement
		if (InputHandler::checkButton("right", ButtonState::HELD))
		{
			velocity.x = walkSpeed;
			facingLeft = false;
			if (onGround)
			{
				currentState = PlayerState::RUNNING;
				walrusSprite->play("run");
			}
			
		}
		else if (InputHandler::checkButton("right", ButtonState::IDLE)
			&& velocity.x >= 0)
		{
			velocity.x = 0;
			if (onGround)
			{
				currentState = PlayerState::IDLE;
				walrusSprite->play("idle");
			}
		}
		if (InputHandler::checkButton("left", ButtonState::HELD))
		{
			velocity.x = -walkSpeed;
			facingLeft = true;
			if (onGround)
			{
				currentState = PlayerState::RUNNING;
				walrusSprite->play("run");
			}
		}
		else if (InputHandler::checkButton("left", ButtonState::IDLE)
			&& velocity.x <= 0)
		{
			velocity.x = 0;
			if (onGround)
			{
				currentState = PlayerState::IDLE;
				walrusSprite->play("idle");
			}
		}

		// jumping
		if (canJump && InputHandler::checkButton("up", ButtonState::DOWN))
		{
			velocity.y = jumpSpeed;
			jumping = true;
			canJump = false;
			frameTimer = 0;
			currentState = PlayerState::IN_AIR;
		}
		if (jumping && InputHandler::checkButton("up", ButtonState::HELD))
		{
			if (frameTimer < jumpFrames)
				velocity.y = jumpSpeed;
			else
				jumping = false;
			frameTimer++;
		}
		if (InputHandler::checkButton("up", ButtonState::IDLE))
		{
			jumping = false;
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
	}

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
	}

	void Player::update(double delta)
	{
		handleInput();

		walrusSprite->update(delta);

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
				onGround = true;
				canJump = true;
				currentState = PlayerState::IDLE;
			}
			jumping = false;
			frameTimer = 0;
			velocity.y = 0;
			moveTo(oldPosition);
		}
		else if (!jumping)
		{
			if (frameTimer > jumpAfterPlatformFrames)
			{
				canJump = false;
			}
			else
			{
				frameTimer++;
			}
			onGround = false;
			currentState = PlayerState::IN_AIR;
			walrusSprite->play("jump");
		}
		else
		{
			onGround = false;
			canJump = false;

			// jump tolerance calculation
			if (!canJump &&
				doCollision(boundingBox + Vector2(0, -jumpInAirTolerance)))
			{
				canJump = true;
				frameTimer = 0;
			}

			currentState = PlayerState::IN_AIR;
			walrusSprite->play("jump");
		}
		
	}

	void Player::draw(SpriteBatch& batch)
	{
		TextureRegion *walrusKeyframe = walrusSprite->get_keyframe();
		walrusKeyframe->set_flipX(facingLeft);
		
		batch.drawreg(*walrusKeyframe, position.x, position.y);
	}

	void Player::updateCollisionEnvironment(TileMap *tileMap)
	{
		this->currentTilemap = tileMap;
	}
}
