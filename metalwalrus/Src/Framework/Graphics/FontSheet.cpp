#include "FontSheet.h"

#include <string>

namespace metalwalrus
{
	void FontSheet::drawChar(SpriteBatch & batch, char c, int x, int y)
	{
		int sheetIndex = c - BASE_CHAR;
		drawTile(batch, x, y, sheetIndex);
	}

	FontSheet::FontSheet(Texture2D * tex, unsigned charWidth, unsigned charHeight, 
		int charSpacing, int lineSpacing)
		: SpriteSheet(tex, charWidth, charHeight)
	{
		this->charSpacing = charSpacing;
		this->lineSpacing = lineSpacing;
	}

	FontSheet::FontSheet(const FontSheet & other)
		: SpriteSheet(other)
	{
		this->charSpacing = other.charSpacing;
		this->lineSpacing = other.lineSpacing;
	}

	FontSheet & FontSheet::operator=(const FontSheet & other)
	{
		if (this != &other)
		{
			SpriteSheet::operator=(other);
			this->charSpacing = other.charSpacing;
			this->lineSpacing = other.lineSpacing;
		}
		return *this;
	}

	void FontSheet::drawText(SpriteBatch & batch, std::string text, int x, int y)
	{
		int numChars = text.length();
		int xPos = x;
		int yPos = y;
		for (int i = 0; i < numChars; i++)
		{
			if (text[i] == '\n')
			{
				yPos -= (spriteHeight + lineSpacing);
				xPos = x;
				continue;
			}

			if (text[i] < BASE_CHAR || text[i] > MAX_CHAR)
				continue;
			
			drawChar(batch, text[i], xPos, yPos);
			xPos += (spriteWidth + charSpacing);
		}
	}
}