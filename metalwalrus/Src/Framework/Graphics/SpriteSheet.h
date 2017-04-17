#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#pragma once

#include <picojson.h>

#include "SpriteBatch.h"
#include "TextureRegion.h"

namespace metalwalrus
{
	class SpriteSheet
	{
	protected:	
		TextureRegion texRegion;
		unsigned spriteWidth = 0;
		unsigned spriteHeight = 0;
		picojson::value spriteProperties;

		void scrollTexRegionToTile(int tileIndex);
	public:
		SpriteSheet(Texture2D *tex, unsigned spriteWidth, unsigned spriteHeight);
		SpriteSheet(Texture2D *tex, unsigned spriteWidth, unsigned spriteHeight,
			picojson::value spriteProperties);
		SpriteSheet(const SpriteSheet& other);

		SpriteSheet& operator=(const SpriteSheet& other);

		inline unsigned get_spriteWidth() const { return spriteWidth; }
		inline unsigned get_spriteHeight() const { return spriteHeight; }

		TextureRegion *get_sprite(int index);

		void drawTile(SpriteBatch& batch, int x, int y, int tileIndex);

		template <typename T>
		T getSpriteProperty(std::string& name, std::string& tileIndex)
		{
			return spriteProperties.get(tileIndex).get(name).get<T>();
			
		}
	};
}

#endif // SPRITESHEET_H