#include "WorldObjectFactory.h"
#include "PlayerSpawn.h"

namespace metalwalrus
{
	WorldObject* WorldObjectFactory::createObject(const std::string& classname, 
		Vector2 pos, picojson::value properties)
	{
		if (classname == PlayerSpawn::staticClassname) 
			return new PlayerSpawn(pos, properties);
	}

}
