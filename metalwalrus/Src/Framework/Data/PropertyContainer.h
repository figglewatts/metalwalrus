#ifndef PROPERTYCONTAINER_H
#define PROPERTYCONTAINER_H
#pragma once

#include <picojson.h>

namespace metalwalrus
{
	struct PropertyContainer
	{
		picojson::value properties;

		PropertyContainer() : properties() { }
		PropertyContainer(picojson::value properties) : properties(properties) { }

		bool hasProperty(const std::string& name) const
		{
			if (properties.is<picojson::null>())
				return false;
			
			return properties.contains(name);
		}

		template <typename T>
		T getProperty(const std::string& name)
		{	
			return properties.get(name).get<T>();
		}

		template <typename T>
		T getProperty(const std::string& name, unsigned tileID)
		{
			return properties.get(std::to_string(tileID)).get(name).get<T>();
		}

		picojson::value getTileProperties(unsigned tileID)
		{
			return properties.get(std::to_string(tileID));
		}
	};
}

#endif // PROPERTYCONTAINER_H