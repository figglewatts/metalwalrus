#ifndef WORLDOBJECTFACTORY_H
#define WORLDOBJECTFACTORY_H
#pragma once

#include "WorldObject.h"

namespace metalwalrus
{
	class WorldObjectFactory
	{
	public:
		WorldObject *createObject(const std::string& classname, 
			Vector2 pos, picojson::value properties);
	};
}

#endif // WORLDOBJECTFACTORY_H