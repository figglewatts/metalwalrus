#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H
#pragma once

#include <picojson.h>

#include "../../../Framework/Game/GameObject.h"

namespace metalwalrus
{
	class WorldObject : public GameObject
	{
	protected:
		std::string classname;
		picojson::value properties;

	public:
		WorldObject(Vector2 position, unsigned width, unsigned height, 
			const std::string& classname, const picojson::value& properties)
			: GameObject(position, width, height)
			, classname(classname), properties(properties) { }

		inline const std::string& get_classname() const { return classname; }
		inline const picojson::value& get_properties() const { return properties; }
	};
}

#endif // WORLDOBJECT_H