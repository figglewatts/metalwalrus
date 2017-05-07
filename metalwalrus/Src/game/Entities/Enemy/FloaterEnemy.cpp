#include "FloaterEnemy.h"

#include "../../Scenes/GameScene.h"

#include <GLFW/glfw3.h>

namespace metalwalrus
{
	void FloaterEnemy::start()
	{
		
	}

	void FloaterEnemy::update(double delta)
	{
		GameObject *player = this->parentScene->getWithID(GameScene::playerID);
		Vector2 toPlayer = (player->get_center() - this->position);
		float distance = toPlayer.dist();

		if (distance > 200)
			return;

		if (distance > 8)
		{
			toPlayer = toPlayer.normalize() * this->speed;
			this->moveBy(toPlayer);
		}

		this->sprite->update(delta);

		
	}

	void FloaterEnemy::draw(SpriteBatch& batch)
	{
		TextureRegion *kf = this->sprite->get_keyframe();
		kf->set_flipX(this->facingLeft);
		batch.drawreg(*kf, this->position.x, this->position.y);
	}

}