#include "EnemyBullet.h"

#include "../../Scenes/GameScene.h"

namespace metalwalrus
{
	Texture2D *EnemyBullet::bulletTex;
	
	EnemyBullet::EnemyBullet(Vector2 pos, Vector2 bulletVelocity, int damage)
		: SolidObject(pos, 8, 6, Vector2::ZERO), bulletVelocity(bulletVelocity), timer(0), damage(damage), p(nullptr)
	{
	}
	
	void EnemyBullet::start()
	{
		if (bulletTex == nullptr)
			bulletTex = Texture2D::create("assets/sprite/bullet-enemy.png");
	}

	void EnemyBullet::update(double delta)
	{
		if (!p)
		{
			p = (Player*)this->parentScene->getWithID(GameScene::playerID);
		}
		
		timer += delta;
		if (timer > lifeTime)
		{
			this->parentScene->destroyObject(this);
			return;
		}

		this->moveBy(bulletVelocity * delta);

		if (this->boundingBox.intersects(p->get_boundingBox()))
		{
			p->takeDamage(damage, this);
			this->parentScene->destroyObject(this);
		}
	}

	void EnemyBullet::draw(SpriteBatch& batch)
	{
		batch.drawtex(*bulletTex, position.x, position.y);
	}
}