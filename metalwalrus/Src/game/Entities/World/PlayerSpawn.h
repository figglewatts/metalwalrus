#ifndef PLAYERSPAWN_H
#define PLAYERSPAWN_H
#pragma once

#include "WorldObject.h"

namespace metalwalrus
{
	class PlayerSpawn : public WorldObject
	{	
		bool facingLeft;
	public:
		static const std::string staticClassname;

		PlayerSpawn(Vector2 position, picojson::value properties);
		~PlayerSpawn() { }

		void start() override;
		void update(double delta) override;
		void draw(SpriteBatch& batch) override;
	};
}

#endif // PLAYERSPAWN_H