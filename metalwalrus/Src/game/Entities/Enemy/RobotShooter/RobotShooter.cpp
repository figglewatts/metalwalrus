#include "RobotShooter.h"
#include "../EnemyBullet.h"

namespace metalwalrus
{
	Texture2D *RobotShooter::robotTex;
	SpriteSheet *RobotShooter::robotSheet;
	
	void RobotShooter::start()
	{
		if (robotTex == nullptr)
			robotTex = Texture2D::create("assets/sprite/robot-shooter.png");
		if (robotSheet == nullptr)
			robotSheet = new SpriteSheet(robotTex, 32, 32);

		int sheetAddition = this->hardEnemy ? 8 : 0;
		sprite = new AnimatedSprite(robotSheet);
		sprite->addAnimation("idle", FrameAnimation(4, sheetAddition + 1, 0.2F));
		sprite->addAnimation("shoot", FrameAnimation(0, sheetAddition, 0));

		machine.transition(new RobotIdleState("idle", &machine), *this);
	}

	void RobotShooter::update(double delta)
	{
		machine.update(delta, *this);

		sprite->update(delta);
	}

	void RobotShooter::draw(SpriteBatch& batch)
	{
		TextureRegion *kf = this->sprite->get_keyframe();
		kf->set_flipX(this->facingLeft);
		batch.drawreg(*kf, this->position.x, this->position.y);
	}

	bool RobotShooter::get_playerSensed()
	{
		if (p == nullptr)
			p = (Player*)this->parentScene->getWithID(GameScene::playerID);
		
		Vector2 toPlayer = (p->get_center() - this->position);
		float distance = toPlayer.dist();

		if (distance > SENSE_DISTANCE)
			return false;

		bool playerOnLeft = toPlayer.dot(Vector2::RIGHT) < 0;
		if ((!facingLeft && playerOnLeft)
			|| (facingLeft && !playerOnLeft))
			return false;

		if (p->get_position().y < this->get_boundingBox().get_bottom() - 50
			|| p->get_position().y > this->get_boundingBox().get_top() + 50)
			return false;

		return true;
	}

	void RobotShooter::shoot()
	{
		Vector2 bulletVel = Vector2(facingLeft ? -bulletSpeed : bulletSpeed, 0);
		this->parentScene->registerObject(new EnemyBullet(this->get_center(), bulletVel, this->damage));
	}
}
