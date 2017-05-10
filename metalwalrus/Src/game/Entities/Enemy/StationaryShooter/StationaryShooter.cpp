#include "StationaryShooter.h"
#include "../EnemyBullet.h"

namespace metalwalrus
{
	Texture2D *StationaryShooter::shooterTex;
	SpriteSheet *StationaryShooter::shooterSheet;
	
	void StationaryShooter::shoot()
	{
		shootingUp = !shootingUp;

		Vector2 bulletVel = Vector2(facingLeft ? -bulletSpeed : bulletSpeed,
			shootingUp ? bulletSpeed : -bulletSpeed);
		parentScene->registerObject(new EnemyBullet(this->get_center(), bulletVel, this->damage));
	}

	void StationaryShooter::start()
	{
		if (shooterTex == nullptr)
			shooterTex = Texture2D::create("assets/sprite/stationary-shooter.png");
		if (shooterSheet == nullptr)
			shooterSheet = new SpriteSheet(shooterTex, 16, 16);

		int sheetAddition = this->hardEnemy ? 8 : 0;
		this->sprite = new AnimatedSprite(shooterSheet);
		this->sprite->addAnimation("idle", FrameAnimation(0, sheetAddition, 0));
		this->sprite->addAnimation("open", FrameAnimation(4, sheetAddition, 0.1));
		this->sprite->addAnimation("close", FrameAnimation(4, sheetAddition + 3, 0.1));
		this->sprite->addAnimation("shoot", FrameAnimation(0, sheetAddition + 3, 0));
		
		machine.transition(new ShooterIdleState("idle", &machine), *this);
	}

	void StationaryShooter::update(double delta)
	{
		this->sprite->update(delta);
		
		if (p == nullptr)
			p = (Player*)this->parentScene->getWithID(GameScene::playerID);

		Vector2 toPlayer = (p->get_center() - this->position);
		float distance = toPlayer.dist();

		if (distance > 150)
			return;

		machine.update(delta, *this);
	}

	void StationaryShooter::draw(SpriteBatch& batch)
	{
		TextureRegion *kf = this->sprite->get_keyframe();
		kf->set_flipX(this->facingLeft);
		batch.drawreg(*kf, this->position.x, this->position.y);
	}
}
