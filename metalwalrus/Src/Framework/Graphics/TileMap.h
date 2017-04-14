#ifndef TILEMAP_H
#define TILEMAP_H
#pragma once

#include <vector>
using namespace std;

#include "../Graphics/Camera.h"
#include "../Graphics/SpriteSheet.h"
#include "../Math/Vector2.h"
#include "../Physics/AABB.h"

namespace metalwalrus
{
	class Tile
	{
		unsigned tileID;
		unsigned sheetIndex;
		Vector2 position;
		bool solid;
		AABB boundingBox;

	public:
		Tile();
		Tile(Vector2 pos, unsigned width, unsigned height);
		Tile(unsigned tileID, unsigned sheetIndex, Vector2 pos, bool solid, 
			unsigned width, unsigned height);
		Tile(const Tile& other);

		Tile& operator=(const Tile& other);

		inline unsigned get_tileID() const { return tileID; }
		inline unsigned get_sheetIndex() const { return sheetIndex; }
		inline Vector2 get_position() const { return position; }
		inline bool is_solid() const { return solid; }
		inline AABB get_boundingBox() const { return boundingBox; }
	};
	
	class TileMap
	{
		typedef vector<vector<Tile>> tilerow;
		
		vector<SpriteSheet*> tileSheets;
		vector<tilerow> tiles;
		unsigned width;
		unsigned height;
		unsigned layerCount;
		Camera* camera;

		void initializeEmpty();
		
	public:
		TileMap(unsigned width, unsigned height, Camera *cam);
		TileMap(SpriteSheet *tileSheet, unsigned width, unsigned height, 
			Camera *cam);
		TileMap(const TileMap& other);
		
		TileMap& operator=(const TileMap& other);

		inline vector<SpriteSheet*>& get_sheets() { return tileSheets; }
		inline vector<tilerow>& get_tiles() { return tiles; }
		inline unsigned get_width() const { return width; }
		inline unsigned get_height() const { return height; }
		inline unsigned get_layerCount() const { return layerCount; }

		Tile& get(unsigned x, unsigned y, unsigned layer);
		void append(Tile t, unsigned x, unsigned y);
		void addLayer();
		void addTileSheet(SpriteSheet *sheet);
		void draw(SpriteBatch& batch, unsigned squaresDown, unsigned squaresAcross);
	};

	
}

#endif // TILEMAP_H