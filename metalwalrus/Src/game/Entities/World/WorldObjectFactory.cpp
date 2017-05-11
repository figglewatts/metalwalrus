#include "WorldObjectFactory.h"
#include "PlayerSpawn.h"
#include "Ladder.h"
#include "EnemySpawn.h"
#include "KillBox.h"
#include "LevelFinish.h"

namespace metalwalrus
{
	WorldObject* WorldObjectFactory::createObject(const std::string& classname, 
		Vector2 pos, picojson::value properties)
	{
		if (classname == PlayerSpawn::staticClassname) 
			return new PlayerSpawn(pos, properties);
		else if (classname == Ladder::staticClassname)
			return new Ladder(pos, properties);
		else if (classname == EnemySpawn::staticClassname)
			return new EnemySpawn(pos, properties);
		else if (classname == "killbox")
			return new KillBox(pos, properties);
		else if (classname == "levelfinish")
			return new LevelFinish(pos, properties);
	}

}
