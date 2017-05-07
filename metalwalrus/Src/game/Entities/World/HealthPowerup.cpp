#include "HealthPowerup.h"
#include "../../Scenes/GameScene.h"

namespace metalwalrus
{
	Vector2 oldPos;
	
	HealthPowerup::~HealthPowerup()
	{
		delete healthTex;
		delete healthSheet;
		delete healthBigSprite;
	}

	void HealthPowerup::start()
	{
		oldPos = position;

		healthTex = Texture2D::create("assets/sprite/health.png");
		healthSheet = new SpriteSheet(healthTex, 16, 16);
		healthBigSprite = new AnimatedSprite(healthSheet);
		healthBigSprite->addAnimation("main", FrameAnimation(2, 0, 0.3));
		healthBigSprite->play("main");
		healthSmallSprite = new TextureRegion(healthTex, 32, 0, 8, 8);

		p = (Player*)this->parentScene->getWithID(GameScene::playerID);
	}

	void HealthPowerup::update(double delta)
	{
		healthBigSprite->update(delta);
		
		velocity.y -= GameScene::gravity;
		if (velocity.y < GameScene::terminalVelocity) velocity.y = GameScene::terminalVelocity;

		oldPos = position;
		this->moveBy(velocity);
		AABB tbb;
		Tile t;
		if (GameScene::loadedMap->boundingBoxCollides(this->boundingBox, tbb, t))
		{
			this->moveTo(Vector2(position.x, tbb.get_top()));
		}

		if (boundingBox.intersects(p->get_boundingBox()))
		{
			p->add_health(isSmall ? this->smallHealing : this->largeHealing);
			this->parentScene->destroyObject(this);
		}
	}

	void HealthPowerup::draw(SpriteBatch & batch)
	{
		if (isSmall)
			batch.drawreg(*healthSmallSprite, position.x, position.y);
		else
			batch.drawreg(*healthBigSprite->get_keyframe(), position.x, position.y);
	}
}
