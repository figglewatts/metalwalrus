#include "StationaryShooter.h"

namespace metalwalrus
{
	Texture2D *StationaryShooter::shooterTex;
	SpriteSheet *StationaryShooter::shooterSheet;
	
	void StationaryShooter::shoot()
	{
		shooting = true;

		// TODO: create bullet
		sprite->playReverse("open", [&]{ shooting = false; });
	}

	void StationaryShooter::start()
	{
		if (shooterTex == nullptr)
			shooterTex = Texture2D::create("assets/sprite/stationary-shooter.png");
		if (shooterSheet == nullptr)
			shooterSheet = new SpriteSheet(shooterTex, 16, 16);

		int sheetAddition = this->hardEnemy ? 4 : 0;
		this->sprite = new AnimatedSprite(shooterSheet);
		this->sprite->addAnimation("idle", FrameAnimation(0, sheetAddition, 0));
		this->sprite->addAnimation("open", FrameAnimation(4, sheetAddition, 0.1));
		this->sprite->addAnimation("shoot", FrameAnimation(0, sheetAddition + 3, 0));
		this->sprite->play("idle");

		this->shootingUp = false;
		this->shotFrameTimer = this->shotCooldownFrames;
		this->shooting = false;
	}

	void StationaryShooter::update(double delta)
	{
		this->sprite->update(delta);
		
		if (p == nullptr)
			p = (Player*)this->parentScene->getWithID(GameScene::playerID);

		Vector2 toPlayer = (p->get_center() - this->position);
		float distance = toPlayer.dist();

		if (distance > 150 || shooting)
			return;

		shotFrameTimer--;
		if (shotFrameTimer <= 0)
			sprite->play("open", [this] { this->shoot(); });
	}

	void StationaryShooter::draw(SpriteBatch& batch)
	{
		TextureRegion *kf = this->sprite->get_keyframe();
		kf->set_flipX(this->facingLeft);
		batch.drawreg(*kf, this->position.x, this->position.y);
	}
}