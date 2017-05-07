#include "WorldObjectFactory.h"
#include "PlayerSpawn.h"
#include "Ladder.h"

namespace metalwalrus
{
	WorldObject* WorldObjectFactory::createObject(const std::string& classname, 
		Vector2 pos, picojson::value properties)
	{
		if (classname == PlayerSpawn::staticClassname) 
			return new PlayerSpawn(pos, properties);
		else if (classname == Ladder::staticClassname)
			return new Ladder(pos, properties);
	}

}
