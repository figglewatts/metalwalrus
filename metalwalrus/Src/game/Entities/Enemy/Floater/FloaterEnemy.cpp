#include "FloaterEnemy.h"

#include "../../../Scenes/GameScene.h"

#include <GLFW/glfw3.h>

namespace metalwalrus
{
	Texture2D *FloaterEnemy::floaterTex;
	SpriteSheet *FloaterEnemy::floaterSheet;
	
	void FloaterEnemy::start()
	{
		if (floaterTex == nullptr)
			floaterTex = Texture2D::create("assets/sprite/floater.png");
		if (floaterSheet == nullptr)
			floaterSheet = new SpriteSheet(floaterTex, 16, 16);

		this->sprite = new AnimatedSprite(floaterSheet);
		this->sprite->addAnimation("main", FrameAnimation(6, this->hardEnemy ? 8 : 0, 0.2F));
		this->sprite->play("main");
	}

	void FloaterEnemy::update(double delta)
	{
		this->sprite->update(delta);
		
		GameObject *player = this->parentScene->getWithID(GameScene::playerID);
		Vector2 toPlayer = (player->get_center() - this->position);
		float distance = toPlayer.dist();

		if (distance > 100)
			return;

		if (distance > 8)
		{
			toPlayer = toPlayer.normalize() * this->speed;
			this->moveBy(toPlayer);
		}
	}

	void FloaterEnemy::draw(SpriteBatch& batch)
	{
		TextureRegion *kf = this->sprite->get_keyframe();
		kf->set_flipX(this->facingLeft);
		batch.drawreg(*kf, this->position.x, this->position.y);
	}

}