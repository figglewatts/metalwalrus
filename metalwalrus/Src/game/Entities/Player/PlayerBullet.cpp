#include "PlayerBullet.h"

namespace metalwalrus
{
	PlayerBullet::PlayerBullet(Vector2 pos, bool facingLeft, Texture2D *bulletTex)
		: SolidObject(pos, 8, 6, Vector2(4, 5)), facingLeft(facingLeft), bulletTex(bulletTex), timer(0) { }

	void PlayerBullet::start()
	{}

	void PlayerBullet::update(double delta)
	{
		timer += delta;
		if (timer > lifeTime)
			this->parentScene->destroyObject(this);
		
		this->position.x += (facingLeft ? -1 : 1) * bulletSpeed;
	}

	void PlayerBullet::draw(SpriteBatch & batch)
	{
		batch.drawtex(*bulletTex, position.x, position.y);
	}
}