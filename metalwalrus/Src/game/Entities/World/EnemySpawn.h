#ifndef ENEMYSPAWN_H
#define ENEMYSPAWN_H
#pragma once
#include "WorldObject.h"

namespace metalwalrus
{
	class EnemySpawn : public WorldObject
	{
		static Texture2D *smallEnemyTex;
		
		std::string enemyType;
	public:
		static std::string staticClassname;

		EnemySpawn(Vector2 position, picojson::value properties);

		void start() override;
	};
}

#endif // ENEMYSPAWN_H