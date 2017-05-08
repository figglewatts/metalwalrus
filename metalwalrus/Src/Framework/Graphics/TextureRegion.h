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
		float width, height;
		bool flipX;
		bool flipY;

	public:
		TextureRegion(Texture2D *tex, int x, int y, int w, int h);
		TextureRegion(const TextureRegion& other);

		~TextureRegion();

		TextureRegion operator=(const TextureRegion& other);

		void setRegion(Texture2D *tex);
		void setRegion(int x, int y, int w, int h);
		void setRegion(float u, float v, float u2, float v2);
		void scroll(int xAmount, int yAmount);
		void changePos(int x, int y);

		void draw();

		inline Texture2D *get_texture() const { return texture; }
		inline float get_u() const { return u; }
		inline float get_v() const { return v; }
		inline float get_u2() const { return u2; }
		inline float get_v2() const { return v2; }
		inline float get_width() const { return width; }
		inline float get_height() const { return height; }
		inline bool get_flipX() const { return flipX; }
		inline void set_flipX(bool fX) { flipX = fX; }
		inline bool get_flipY() const { return flipY; }
		inline void set_flipY(bool fY) { flipY = fY; }
	};

}
#endif