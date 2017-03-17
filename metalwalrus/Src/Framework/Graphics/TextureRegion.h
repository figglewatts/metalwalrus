#ifndef TEXTUREREGION_H
#define TEXTUREREGION_H
#pragma once

#include "Texture2D.h"

namespace metalwalrus
{
	class TextureRegion
	{
		Texture2D *texture;
		float u, v;
		float u2, v2;
		int width, height;

	public:
		TextureRegion(Texture2D *tex, int x, int y, int w, int h);

		void setRegion(Texture2D *tex);
		void setRegion(int x, int y, int w, int h);
		void setRegion(float u, float v, float u2, float v2);
		void scroll(int xAmount, int yAmount);

		void draw();

		inline Texture2D *get_texture() const { return texture; }
		inline float get_u() const { return u; }
		inline float get_v() const { return v; }
		inline float get_u2() const { return u2; }
		inline float get_v2() const { return v2; }
		inline float get_width() const { return width; }
		inline float get_height() const { return height; }
	};

}
#endif