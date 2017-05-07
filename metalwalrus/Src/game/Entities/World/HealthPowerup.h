#ifndef HEALTHPOWERUP_H
#define HEALTHPOWERUP_H
#pragma once

#include "WorldObject.h"
#include "../../../Framework/Graphics/TileMap.h"
#include "../../../Framework/Animation/AnimatedSprite.h"
#include "../Player/Player.h"

namespace metalwalrus
{
	class HealthPowerup : public WorldObject
	{
		bool isSmall;
		Vector2 velocity;

		const int smallHealing = 3;
		const int largeHealing = 6;

		Texture2D *healthTex;
		SpriteSheet *healthSheet;
		AnimatedSprite *healthBigSprite;
		TextureRegion *healthSmallSprite;

		Player *p;
	public:
		HealthPowerup(Vector2 pos, bool isSmall, picojson::value properties)
			: WorldObject(pos, isSmall ? 8 : 16, isSmall ? 8 : 16, "health_powerup", properties)
			, isSmall(isSmall), velocity(Vector2::ZERO) { }
		~HealthPowerup();

		void start() override;
		void update(double delta) override;
		void draw(SpriteBatch& batch) override;
	};
}

#endif // HEALTHPOWERUP_H