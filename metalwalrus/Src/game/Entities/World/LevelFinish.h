#ifndef LEVELFINISH_H
#define LEVELFINISH_H
#pragma once

#include "WorldObject.h"

namespace metalwalrus
{
	class LevelFinish : public WorldObject
	{
	public:
		LevelFinish(Vector2 pos, picojson::value properties)
			: WorldObject(pos, 16, 16, "levelfinish", properties) { }

		void start() override;
	};
}

#endif // LEVELFINISH_H