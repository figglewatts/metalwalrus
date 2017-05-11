#ifndef KILLBOX_H
#define KILLBOX_H
#pragma once

#include "WorldObject.h"

namespace metalwalrus
{
	class KillBox : public WorldObject
	{
	public:
		KillBox(Vector2 pos, picojson::value properties)
			: WorldObject(pos, 16, 16, "killbox", properties) { }

		void start() override;
	};
}

#endif