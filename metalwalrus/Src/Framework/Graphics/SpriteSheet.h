#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#pragma once

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

		void scrollTexRegionToTile(int tileIndex);
	public:
		SpriteSheet(Texture2D *tex, unsigned spriteWidth, unsigned spriteHeight);
		SpriteSheet(const SpriteSheet& other);

		SpriteSheet& operator=(const SpriteSheet& other);

		void drawTile(SpriteBatch& batch, int x, int y, int tileIndex);
	};
}

#endif // SPRITESHEET_H