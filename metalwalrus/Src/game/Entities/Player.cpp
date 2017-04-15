#include "Player.h"

#include "../../Framework/Graphics/Texture2D.h"
#include "../../Framework/Input/InputHandler.h"

namespace metalwalrus
{
	const float Player::walkSpeed = 1.5;
	
	const float Player::jumpSpeed = 4;
	const int Player::jumpFrames = 11;
	const int Player::jumpAfterPlatformFrames = 7;
	const float Player::jumpInAirTolerance = 2;

	const float Player::gravity = 0.5;
	const float Player::terminalVelocity = -4;
	
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
			velocity.x = walkSpeed;
		else if (InputHandler::checkButton("right", ButtonState::UP))
			velocity.x = 0;
		if (InputHandler::checkButton("left", ButtonState::HELD))
			velocity.x = -walkSpeed;
		else if (InputHandler::checkButton("left", ButtonState::UP))
			velocity.x = 0;

		// jumping
		if (onGround && InputHandler::checkButton("up", ButtonState::DOWN))
		{
			velocity.y = jumpSpeed;
			jumping = true;
			onGround = false;
			frameTimer = 0;
		}
		if (jumping && InputHandler::checkButton("up", ButtonState::HELD))
		{
			if (frameTimer < jumpFrames)
				velocity.y = jumpSpeed;
			else
				jumping = false;
			frameTimer++;
		}
		if (InputHandler::checkButton("up", ButtonState::UP))
		{
			frameTimer = 0;
			jumping = false;
		}
	}

	void Player::start()
	{
		playerTex = Texture2D::create("assets/player.png");
	}

	void Player::update(double delta)
	{
		handleInput();

		velocity.y -= gravity;

		if (velocity.y < terminalVelocity) velocity.y = terminalVelocity;
		
		oldPosition = position;
		moveBy(Vector2(velocity.x, 0));
		if (doCollision(boundingBox))
		{
			moveTo(oldPosition);
		}

		// jump tolerance calculation
		if (!jumping && !onGround &&
			doCollision(boundingBox + Vector2(0, -jumpInAirTolerance)))
		{
			onGround = true;
			frameTimer = 0;
		}

		oldPosition = position;
		moveBy(Vector2(0, velocity.y));
		if (doCollision(boundingBox))
		{
			velocity.y = 0;
			jumping = false;
			onGround = true;
			frameTimer = 0;
			moveTo(oldPosition);
		}
		else if (!jumping)
		{
			if (frameTimer > jumpAfterPlatformFrames)
			{
				onGround = false;
			}
			else
			{
				frameTimer++;
			}
		}
	}

	void Player::draw(SpriteBatch& batch)
	{
		batch.drawtex(*playerTex, position.x, position.y);
	}

	void Player::updateCollisionEnvironment(TileMap *tileMap)
	{
		this->currentTilemap = tileMap;
	}
}
