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

	void SpriteSheet::calculateNumSprites()
	{
		int spritesAcross = texRegion.get_texture()->get_width() / this->spriteWidth;
		int spritesDown = texRegion.get_texture()->get_height() / this->spriteHeight;
		this->numSprites = spritesAcross * spritesDown;
	}

	SpriteSheet::SpriteSheet(Texture2D *tex, unsigned spriteWidth, unsigned spriteHeight)
		: texRegion(tex, 0, 0, spriteWidth, spriteHeight), properties(picojson::value())
	{
		this->spriteWidth = spriteWidth;
		this->spriteHeight = spriteHeight;
		this->calculateNumSprites();
	}

	SpriteSheet::SpriteSheet(Texture2D * tex, unsigned spriteWidth, unsigned spriteHeight, picojson::value spriteProperties)
		: SpriteSheet(tex, spriteWidth, spriteHeight)
	{
		this->properties.properties = spriteProperties;
	}

	SpriteSheet::SpriteSheet(const SpriteSheet & other)
		: texRegion(other.texRegion), properties(picojson::value())
	{
		this->spriteWidth = other.spriteWidth;
		this->spriteHeight = other.spriteHeight;
		this->numSprites = other.numSprites;
	}

	SpriteSheet & SpriteSheet::operator=(const SpriteSheet & other)
	{
		if (this != &other)
		{
			this->texRegion = other.texRegion;
			this->spriteWidth = other.spriteWidth;
			this->spriteHeight = other.spriteHeight;
			this->numSprites = other.numSprites;
		}
		return *this;
	}

	TextureRegion *SpriteSheet::get_sprite(int index)
	{
		scrollTexRegionToTile(index);
		return &texRegion;
	}

	void SpriteSheet::drawTile(SpriteBatch& batch, int x, int y, int tileIndex)
	{
		scrollTexRegionToTile(tileIndex);
		batch.drawreg(texRegion, x, y);
	}
}