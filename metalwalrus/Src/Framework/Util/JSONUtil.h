#ifndef JSONUTIL_H
#define JSONUTIL_H
#pragma once

#include "../Graphics/SpriteSheet.h"
#include "../Graphics/TileMap.h"

namespace metalwalrus
{
	namespace utilities
	{
		class JSONUtil
		{
			JSONUtil();

			static Color colorFromHexString(const std::string& hexString);
		public:
			static SpriteSheet *tiled_spritesheet(std::string filePath);
			static TileMap *tiled_tilemap(std::string filePath, Camera *cam);

			static picojson::value *jsonValueFromFile(std::string filePath);
		};
	}
}

#endif // JSONUTIL_H