#include "FloaterEnemy.h"

#include "../../Scenes/GameScene.h"

namespace metalwalrus
{
	void FloaterEnemy::start()
	{
		
	}

	void FloaterEnemy::update(double delta)
	{
		GameObject *player = this->parentScene->getWithID(GameScene::playerID);
		Vector2 toPlayer = (this->position - player->get_center());
		float distance = toPlayer.dist();

		if (distance > 200)
			return;

		if (distance > 8)
		{
			toPlayer = toPlayer.normalize() * this->speed;
			this->position -= toPlayer;
		}

		this->sprite->update(delta);
	}

	void FloaterEnemy::draw(SpriteBatch& batch)
	{
		TextureRegion *kf = this->sprite->get_keyframe();
		kf->set_flipX(this->facingLeft);
		batch.drawreg(*kf, this->position.x, this->position.y);
	}

	void FloaterEnemy::die()
	{
		this->parentScene->destroyObject(this);
	}

}