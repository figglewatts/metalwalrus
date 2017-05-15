#include "BouncingRobot.h"

namespace metalwalrus
{
	Texture2D *BouncingRobot::bouncerTex;
	SpriteSheet *BouncingRobot::bouncerSheet;
	
	void BouncingRobot::start()
	{
		if (bouncerTex == nullptr)
			bouncerTex = Texture2D::create("assets/sprite/bouncing-robot.png");
		if (bouncerSheet == nullptr)
			bouncerSheet = new SpriteSheet(bouncerTex, 16, 16);

		int sheetAddition = this->hardEnemy ? 8 : 0;
		this->sprite = new AnimatedSprite(bouncerSheet);
		this->sprite->addAnimation("idle", FrameAnimation(0, sheetAddition + 2, 0));
		this->sprite->addAnimation("compress", FrameAnimation(3, sheetAddition, 0.2F));
		this->sprite->addAnimation("inAir", FrameAnimation(2, sheetAddition + 3, 0.1F));

		this->machine.transition(new BouncerIdleState("idle", &machine), *this);
	}

	void BouncingRobot::update(double delta)
	{
		this->velocity.y -= GameScene::gravity;
		if (this->velocity.y < GameScene::terminalVelocity)
			this->velocity.y = GameScene::terminalVelocity;

		oldPosition = position;
		this->moveBy(Vector2(this->velocity.x * delta, 0));
		AABB bb;
		Tile t;
		if (GameScene::loadedMap->boundingBoxCollides(boundingBox, bb, t))
		{
			this->moveTo(oldPosition);
		}

		oldPosition = position;
		this->moveBy(Vector2(0, this->velocity.y * delta));
		if (GameScene::loadedMap->boundingBoxCollides(boundingBox, bb, t))
		{
			this->velocity.y = 0;
			this->moveTo(oldPosition);
			if (this->position.y > bb.get_top())
			{
				this->onGround = true;
				this->velocity.x = 0;
			}
		}
		else
		{
			this->onGround = false;
		}

		this->sprite->update(delta);

		if (p == nullptr)
			p = (Player*)this->parentScene->getWithID(GameScene::playerID);

		Vector2 toPlayer = (p->get_center() - this->position);
		float distance = toPlayer.dist();

		if (distance > 120)
			return;

		this->machine.update(delta, *this);
	}

	void BouncingRobot::draw(SpriteBatch& batch)
	{
		TextureRegion *kf = this->sprite->get_keyframe();
		kf->set_flipX(this->facingLeft);
		batch.drawreg(*kf, this->position.x, this->position.y);
	}

	void BouncingRobot::jump()
	{
		if (p == nullptr)
			p = (Player*)this->parentScene->getWithID(GameScene::playerID);

		Vector2 toPlayer = this->position - p->get_position();
		bool playerOnLeft = toPlayer.dot(Vector2::RIGHT) < 0;
		this->facingLeft = playerOnLeft;

		this->velocity.y = jumpVelocity * 10;
		this->velocity.x = playerOnLeft ? leapVelocity : -leapVelocity;
		this->onGround = false;
	}

}