#ifndef FONTSHEET_H
#define FONTSHEET_H
#pragma once

#include "SpriteBatch.h"
#include "SpriteSheet.h"

namespace metalwalrus
{
	class FontSheet : public SpriteSheet
	{
		const static int BASE_CHAR = 32; // base ASCII value to print from
		const static int MAX_CHAR = 126; // max ASCII value to print to
		
		int charSpacing;
		int lineSpacing;

		void drawChar(SpriteBatch& batch, char c, int x, int y);
	public:
		FontSheet(Texture2D *tex, unsigned charWidth, unsigned charHeight,
			int charSpacing = 0, int lineSpacing = 0);
		FontSheet(const FontSheet& other);

		FontSheet& operator=(const FontSheet& other);

		void drawText(SpriteBatch& batch, std::string text, int x, int y);
	};
}

#endif // FONTSHEET_H