#include "PlayerBullet.h"
#include "../../Scenes/GameScene.h"
#include "../Enemy/Enemy.h"

namespace metalwalrus
{
	PlayerBullet::PlayerBullet(Vector2 pos, bool facingLeft, Texture2D *bulletTex)
		: SolidObject(pos, 8, 6, Vector2::ZERO), facingLeft(facingLeft), bulletTex(bulletTex), timer(0) { }

	void PlayerBullet::start()
	{}

	void PlayerBullet::update(double delta)
	{
		timer += delta;
		if (timer > lifeTime)
		{
			this->parentScene->destroyObject(this);
			return;
		}

		Vector2 moveVec = Vector2((facingLeft ? -1 : 1) * bulletSpeed, 0);
		
		this->moveBy(moveVec);

		for (auto o : *GameScene::enemies)
		{
			Enemy *e = (Enemy*)o;
			AABB ebb = e->get_boundingBox();
			if (this->boundingBox.intersects(e->get_boundingBox()))
			{
				e->takeDamage(Player::shotDamage);
				this->parentScene->destroyObject(this);
				return;
			}
		}
	}

	void PlayerBullet::draw(SpriteBatch & batch)
	{
		batch.drawtex(*bulletTex, position.x, position.y);
	}
}
