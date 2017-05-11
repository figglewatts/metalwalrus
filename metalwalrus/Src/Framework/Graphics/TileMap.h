#ifndef TILEMAP_H
#define TILEMAP_H
#pragma once

#include <vector>
#include <map>
using namespace std;

#include "../Graphics/Camera.h"
#include "../Graphics/SpriteSheet.h"
#include "../Math/Vector2.h"
#include "../Physics/AABB.h"

namespace metalwalrus
{
	class TileMap; // forward declaration
	
	class Tile
	{
		unsigned tileID;
		unsigned sheetID;
		unsigned sheetIndex;
		Vector2 position;
		bool solid;
		bool oneWay;
		AABB boundingBox;
		TileMap *tileMap;

	public:
		Tile() { }
		Tile(TileMap* map);
		Tile(Vector2 pos, unsigned width, unsigned height, TileMap *map);
		Tile(unsigned tileID, Vector2 pos, bool solid, bool oneWay,
			unsigned width, unsigned height, TileMap *map);
		Tile(const Tile& other);

		Tile& operator=(const Tile& other);

		inline unsigned get_tileID() const { return tileID; }
		inline unsigned get_sheetID() const { return sheetID; }
		inline unsigned get_sheetIndex() const { return sheetIndex; }
		inline Vector2 get_position() const { return position; }
		inline bool is_solid() const { return solid; }
		inline bool is_oneWay() const { return oneWay; }
		inline AABB get_boundingBox() const { return boundingBox; }
	};

	typedef vector<Tile> tilerow;
	typedef vector<tilerow> tilelayer;

	class TileLayer
	{
		tilelayer layer;
		std::string name;
		TileMap *tileMap;
	public:
		PropertyContainer properties;

		TileLayer(std::string name, unsigned width, unsigned height, TileMap *map);
		TileLayer(const TileLayer& other);

		TileLayer& operator=(const TileLayer& other);

		Tile& get(unsigned x, unsigned y);
		std::string get_name() const { return name; }
		void set_name(std::string name) { this->name = name; }
	};

	class TileMap
	{
		vector<SpriteSheet*> tileSheets;
		map<SpriteSheet*, unsigned> initialTileIDs;
		int cumulativeTileID = 0;

		vector<TileLayer> layers;
		
		unsigned width;
		unsigned height;
		Camera* camera;
		PropertyContainer properties;

		void initializeEmpty();
	public:
		TileMap(unsigned width, unsigned height, Camera *cam);
		TileMap(SpriteSheet *tileSheet, unsigned width, unsigned height, 
			Camera *cam);
		TileMap(const TileMap& other);
		
		TileMap& operator=(const TileMap& other);

		inline vector<SpriteSheet*>& get_sheets() { return tileSheets; }
		inline vector<TileLayer>& get_layers() { return layers; }
		inline unsigned get_width() const { return width; }
		inline unsigned get_height() const { return height; }
		inline unsigned get_layerCount() const { return layers.size(); }
		unsigned get_sheetInitialTileID(SpriteSheet* sheet) { return initialTileIDs[sheet]; }

		Tile& get(unsigned x, unsigned y, std::string layer);
		Tile& get(unsigned x, unsigned y, unsigned layer);
		void addLayer(std::string name);
		void addTileSheet(SpriteSheet *sheet);
		void draw(SpriteBatch& batch, unsigned squaresDown, unsigned squaresAcross);
		TileLayer* get_layer(std::string name);
		TileLayer* get_layer(unsigned layer);
		SpriteSheet& get_sheetFromTileID(unsigned tileID);
		int get_sheetIndexFromTileID(unsigned tileID);
		PropertyContainer& get_properties() { return properties; }

		bool boundingBoxCollides(AABB boundingBox, AABB& tbb, Tile& t);
	};

	
}

#endif // TILEMAP_H