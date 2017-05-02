#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#pragma once

#include <picojson.h>

#include "SpriteBatch.h"
#include "TextureRegion.h"
#include "../Data/PropertyContainer.h"

namespace metalwalrus
{
	class SpriteSheet
	{
	protected:	
		TextureRegion texRegion;
		unsigned spriteWidth = 0;
		unsigned spriteHeight = 0;
		unsigned numSprites = 0;

		void scrollTexRegionToTile(int tileIndex);
		void calculateNumSprites();
	public:
		PropertyContainer properties;

		SpriteSheet(Texture2D *tex, unsigned spriteWidth, unsigned spriteHeight);
		SpriteSheet(Texture2D *tex, unsigned spriteWidth, unsigned spriteHeight,
			picojson::value spriteProperties);
		SpriteSheet(const SpriteSheet& other);

		SpriteSheet& operator=(const SpriteSheet& other);

		inline unsigned get_spriteWidth() const { return spriteWidth; }
		inline unsigned get_spriteHeight() const { return spriteHeight; }
		inline unsigned get_numSprites() const { return numSprites; }

		TextureRegion *get_sprite(int index);

		void drawTile(SpriteBatch& batch, int x, int y, int tileIndex);
	};
}

#endif // SPRITESHEET_H