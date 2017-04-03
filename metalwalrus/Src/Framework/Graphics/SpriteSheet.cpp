#include "SpriteSheet.h"

namespace metalwalrus
{
	void SpriteSheet::scrollTexRegionToTile(int tileIndex)
	{
		if (spriteWidth == 0 || spriteHeight == 0)
			throw new std::runtime_error("Sprite width or height can't be zero");

		int tileY = tileIndex / (texRegion.get_texture()->get_width() / (float)spriteWidth);
		int tileX = tileIndex % (texRegion.get_texture()->get_width() / spriteWidth);
		texRegion.changePos(tileX * spriteWidth, tileY * spriteHeight);
	}

	SpriteSheet::SpriteSheet(Texture2D *tex, unsigned spriteWidth, unsigned spriteHeight)
		: texRegion(tex, 0, 0, spriteWidth, spriteHeight)
	{
		this->spriteWidth = spriteWidth;
		this->spriteHeight = spriteHeight;
	}

	SpriteSheet::SpriteSheet(const SpriteSheet & other)
		: texRegion(other.texRegion)
	{
		this->spriteWidth = other.spriteWidth;
		this->spriteHeight = other.spriteHeight;
	}

	SpriteSheet & SpriteSheet::operator=(const SpriteSheet & other)
	{
		if (this != &other)
		{
			this->texRegion = other.texRegion;
			this->spriteWidth = other.spriteWidth;
			this->spriteHeight = other.spriteHeight;
		}
		return *this;
	}

	void SpriteSheet::drawTile(SpriteBatch& batch, int x, int y, int tileIndex)
	{
		scrollTexRegionToTile(tileIndex);
		batch.drawreg(texRegion, x, y);
	}
}