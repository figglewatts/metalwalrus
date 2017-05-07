#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H
#pragma once

#include <picojson.h>

#include "../../../Framework/Game/SolidObject.h"

namespace metalwalrus
{
	class WorldObject : public SolidObject
	{
	protected:
		std::string classname;
		picojson::value properties;

	public:
		WorldObject(Vector2 position, unsigned width, unsigned height,
			const std::string& classname, const picojson::value& properties)
			: SolidObject(position, width, height)
			, classname(classname), properties(properties) { }
		virtual ~WorldObject() = 0;

		inline const std::string& get_classname() const { return classname; }
		inline const picojson::value& get_properties() const { return properties; }
	};

	inline WorldObject::~WorldObject() { }
}

#endif // WORLDOBJECT_H