#include "Player.h"

#include "../../../Framework/Graphics/Texture2D.h"
#include "../../../Framework/Input/InputHandler.h"

#include "States.h"
#include "PlayerBullet.h"
#include "../../Scenes/GameScene.h"

namespace metalwalrus
{
	const float Player::walkSpeed = 1.5;

	const float Player::climbSpeed = 1;

	const float Player::jumpSpeed = 4;
	const int Player::jumpFrames = 11;
	const int Player::jumpAfterPlatformFrames = 7;
	const float Player::jumpInAirTolerance = 2;

	const int Player::framesBetweenShots = 20;
	const int Player::framesBetweenShotAnimation = 40;

	const int Player::maxHealth = 28;
	const int Player::shotDamage = 1;

	const int Player::damageAnimationFrames = 20;
	const float Player::damageVelocity = 1;
	const int Player::damageImmunityFrames = 50;

	const int Player::framesAfterDeath = 30;

	Ladder *Player::checkCanClimb()
	{
		for (Ladder *l : GameScene::ladders)
		{
			if (this->boundingBox.intersects(l->get_boundingBox()))
				return l;
		}
		return nullptr;
	}

	void Player::shoot()
	{
		parentScene->registerObject(new PlayerBullet(position + Vector2(playerInfo.facingLeft ? 0 : 26, 13), 
			playerInfo.facingLeft, bulletTex));
	}

	void Player::handleInput()
	{
		if (!playerInfo.canMove) 
			return;

		// climbing
		if (Ladder *l = checkCanClimb())
		{
			if (InputHandler::checkButton("up", ButtonState::DOWN))
			{
				playerInfo.climbing = true;
				playerInfo.canJump = false;
				this->moveTo(Vector2(l->get_position().x - 8, this->position.y));
				this->velocity.x = 0;
			}
		}
		else
		{
			playerInfo.climbing = false;
		}

		if (playerInfo.climbing)
		{
			if (InputHandler::checkButton("up", ButtonState::HELD))
			{
				velocity.y = climbSpeed;
				playerInfo.moving = true;
			}
			else if (InputHandler::checkButton("down", ButtonState::HELD))
			{
				velocity.y = -climbSpeed;
				playerInfo.moving = true;
			}
			else if (InputHandler::checkButton("up", ButtonState::IDLE)
				&& InputHandler::checkButton("down", ButtonState::IDLE))
			{
				velocity.y = 0;
				playerInfo.moving = false;
			}

			if (InputHandler::checkButton("left", ButtonState::DOWN))
			{
				playerInfo.facingLeft = true;
			}
			else if (InputHandler::checkButton("right", ButtonState::DOWN))
			{
				playerInfo.facingLeft = false;
			}
		}

		// shooting
		if (playerInfo.canShoot)
		{
			if (InputHandler::checkButton("shoot", ButtonState::DOWN))
			{
				playerInfo.shooting = true;
				playerInfo.canShoot = false;

				this->shoot();
			}
		}
		
		if (playerInfo.climbing)
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
		if (jumpFrameTimer > 0)
		{
			if (InputHandler::checkButton("up", ButtonState::UP))
			{
				jumpFrameTimer = 0;
			}
			if (InputHandler::checkButton("up", ButtonState::HELD))
			{
				velocity.y = jumpSpeed;
				jumpFrameTimer--;
			}
		}
		else
		{
			playerInfo.jumping = false;
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
		damaged = FrameAnimation(0, 6, 0);
		climbing = FrameAnimation(2, 16, 0.2);
		climbingShoot = FrameAnimation(0, 18, 0);
		climbingFinish = FrameAnimation(0, 19, 0);
		dead = FrameAnimation(0, 20, 0);
		walrusSprite->addAnimation("idle", idle);
		walrusSprite->addAnimation("run", run);
		walrusSprite->addAnimation("jump", jump);
		walrusSprite->addAnimation("idleShoot", idleShoot);
		walrusSprite->addAnimation("runShoot", runShoot);
		walrusSprite->addAnimation("jumpShoot", jumpShoot);
		walrusSprite->addAnimation("damaged", damaged);
		walrusSprite->addAnimation("climbing", climbing);
		walrusSprite->addAnimation("climbingShoot", climbingShoot);
		walrusSprite->addAnimation("climbingFinish", climbingFinish);
		walrusSprite->addAnimation("dead", dead);
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
		playerInfo.damaged = false;
		playerInfo.damagedFromLeft = false;
		playerInfo.canTakeDamage = true;
		playerInfo.alive = true;
		playerInfo.climbing = false;
		playerInfo.canClimb = false;

		this->health = this->maxHealth;
		this->score = 0;

		playerStateMachine.push(new IdleState("idle", &playerStateMachine), *this);

		bulletTex = Texture2D::create("assets/sprite/bullet.png");
	}

	void Player::update(double delta)
	{
		if (!playerInfo.alive)
		{
			deathFrameTimer--;
			if (deathFrameTimer <= 0)
			{
				((GameScene*)this->parentScene)->loadLevel(GameScene::currentLevel);
			}
			return;
		}
		
		if (damageImmunityFrameTimer <= 0)
		{
			playerInfo.canTakeDamage = true;
		}
		else
		{
			damageImmunityFrameTimer--;
		}
		
		handleInput();

		if (!playerInfo.climbing)
			velocity.y -= GameScene::gravity;

		if (velocity.y < GameScene::terminalVelocity) velocity.y = GameScene::terminalVelocity;

		oldPosition = position;
		AABB tbb;
		moveBy(Vector2(velocity.x, 0));
		if (GameScene::loadedMap->boundingBoxCollides(boundingBox, tbb))
		{
			moveTo(oldPosition);
		}

		oldPosition = position;
		moveBy(Vector2(0, velocity.y));
		if (GameScene::loadedMap->boundingBoxCollides(boundingBox, tbb))
		{
			moveTo(Vector2(position.x, velocity.y < 0 ? tbb.get_top() : (tbb.get_bottom() - boundingBox.get_height())));

			if (velocity.y < 0)
			{
				playerInfo.onGround = true;
				playerInfo.touchedGroundLastFrame = true;
			}

			velocity.y = 0;
			playerInfo.jumping = false;
			jumpFrameTimer = 0;
		}
		else
		{
			if (!playerInfo.touchedGroundLastFrame)
			{
				playerInfo.onGround = false;
			}
			playerInfo.canJump = false;
			playerInfo.touchedGroundLastFrame = false;
		}

		walrusSprite->update(delta);

		playerStateMachine.update(delta, *this);
	}

	void Player::draw(SpriteBatch& batch)
	{
		TextureRegion *walrusKeyframe = walrusSprite->get_keyframe();
		walrusKeyframe->set_flipX(playerInfo.facingLeft);
		
		batch.drawreg(*walrusKeyframe, position.x, position.y);
	}

	void Player::takeDamage(int damageAmount, GameObject* damager)
	{
		if (!playerInfo.canTakeDamage || !playerInfo.alive)
			return;

		playerInfo.damaged = true;
		playerInfo.canTakeDamage = false;

		damageImmunityFrameTimer = Player::damageAnimationFrames + Player::damageImmunityFrames;

		Vector2 toPlayer = damager->get_position() - this->position;
		playerInfo.damagedFromLeft = toPlayer.dot(Vector2::RIGHT) < 0;
		
		this->health -= damageAmount;

		if (this->health <= 0)
		{
			playerInfo.alive = false;
			walrusSprite->play("dead");
			deathFrameTimer = framesAfterDeath;
		}
	}
}
