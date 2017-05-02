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
		PlayerSpawn(Vector2 position, picojson::value properties)
			: WorldObject(position, "player_spawn")
	};
}

#endif // PLAYERSPAWN_H