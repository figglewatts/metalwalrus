#ifndef LADDER_H
#define LADDER_H
#pragma once

#include "WorldObject.h"

namespace metalwalrus
{
	class Ladder : public WorldObject
	{
	public:
		static const std::string staticClassname;

		Ladder(Vector2 pos, picojson::value properties)
			: WorldObject(pos, 16, 15, "ladder", properties) { }

		void start() override;
	};
}

#endif // LADDER_H