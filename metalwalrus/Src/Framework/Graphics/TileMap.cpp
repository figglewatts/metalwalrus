#include "TileMap.h"

namespace metalwalrus
{
	void TileMap::initializeEmpty()
	{
		this->addLayer("0");
	}

	TileMap::TileMap(unsigned width, unsigned height, Camera * cam)
	{
		this->width = width;
		this->height = height;
		this->camera = cam;
		this->initializeEmpty();
	}

	TileMap::TileMap(SpriteSheet *tileSheet, unsigned width, unsigned height,
		Camera* cam)
	{
		this->tileSheets.push_back(tileSheet);
		this->width = width;
		this->height = height;
		this->camera = cam;
		this->initializeEmpty();
	}

	TileMap::TileMap(const TileMap& other)
	{
		this->layers = other.layers;
		this->tileSheets = other.tileSheets;
		this->width = other.width;
		this->height = other.height;
		this->camera = other.camera;
		this->initialTileIDs = other.initialTileIDs;
		this->cumulativeTileID = other.cumulativeTileID;
	}

	TileMap & TileMap::operator=(const TileMap& other)
	{
		if (this != &other)
		{
			this->layers = other.layers;
			this->tileSheets = other.tileSheets;
			this->width = other.width;
			this->height = other.height;
			this->camera = other.camera;
			this->initialTileIDs = other.initialTileIDs;
			this->cumulativeTileID = other.cumulativeTileID;
		}
		return *this;
	}

	Tile & TileMap::get(unsigned x, unsigned y, std::string name)
	{
		return get_layer(name)->get(x, y);
	}

	Tile & TileMap::get(unsigned x, unsigned y, unsigned layer)
	{
		return get_layer(layer)->get(x, y);
	}

	void TileMap::addLayer(std::string name)
	{
		layers.push_back(TileLayer(name, this->width, this->height, this));
	}

	void TileMap::addTileSheet(SpriteSheet *sheet)
	{
		this->tileSheets.push_back(sheet);
		this->initialTileIDs[sheet] = cumulativeTileID;
		cumulativeTileID += sheet->get_numSprites();
	}

	void TileMap::draw(SpriteBatch& batch, unsigned squaresDown, unsigned squaresAcross)
	{
		Vector2 cameraPos = camera->getPosition();
		unsigned tileWidth = tileSheets[0]->get_spriteWidth();
		unsigned tileHeight = tileSheets[0]->get_spriteHeight();
		Vector2 firstSquare = Vector2(
			(cameraPos.x) / tileWidth,
			(cameraPos.y) / tileHeight);

		for (auto layer : layers)
		{
			if (layer.properties.hasProperty("objectLayer") && layer.properties.getProperty<bool>("objectLayer")) 
				continue;
			
			for (unsigned y = 0; y < squaresDown; y++)
			{
				for (unsigned x = 0; x < squaresAcross; x++)
				{
					unsigned tileXIndex = firstSquare.x + x;
					unsigned tileYIndex = firstSquare.y + y;

					if (tileXIndex >= width || tileYIndex >= height
						|| tileXIndex < 0 || tileYIndex < 0) continue;

					Tile t = layer.get(tileXIndex, tileYIndex);

					if (t.get_tileID() == 0) continue;

					tileSheets[t.get_sheetIndex()]->drawTile(batch,
						tileXIndex * tileWidth, tileYIndex * tileHeight,
						t.get_sheetID() - 1); // -1 due to 0 being blank tile
				}
			}
		}
	}

	TileLayer* TileMap::get_layer(std::string name)
	{
		for (int i = 0; i < layers.size(); i++)
		{
			if (layers[i].get_name() == name)
				return &layers[i];
		}
		throw std::runtime_error("Layer did not exist!");
	}

	TileLayer* TileMap::get_layer(unsigned layer)
	{
		return &layers[layer];
	}

	SpriteSheet & TileMap::get_sheetFromTileID(unsigned tileID)
	{
		return *tileSheets[get_sheetIndexFromTileID(tileID)];
	}

	int TileMap::get_sheetIndexFromTileID(unsigned tileID)
	{
		for (int i = 0; i < tileSheets.size(); i++)
		{
			if (tileID < initialTileIDs[tileSheets[i]] + tileSheets[i]->get_numSprites())
				return i;
		}
		throw std::runtime_error("Could not get tilesheet from tileID");
	}

	bool TileMap::boundingBoxCollides(AABB boundingBox, AABB& tbb, Tile& tile)
	{
		int leftTile = boundingBox.get_left()
			/ this->get_sheets()[0]->get_spriteWidth();
		int rightTile = boundingBox.get_right()
			/ this->get_sheets()[0]->get_spriteWidth();
		int topTile = boundingBox.get_top()
			/ this->get_sheets()[0]->get_spriteHeight();
		int bottomTile = boundingBox.get_bottom()
			/ this->get_sheets()[0]->get_spriteHeight();

		if (leftTile < 0) leftTile = 0;
		if (rightTile >= this->get_width())
			rightTile = this->get_width() - 1;
		if (bottomTile < 0) bottomTile = 0;
		if (topTile >= this->get_height())
			topTile = this->get_height() - 1;

		for (int i = leftTile; i <= rightTile; i++)
		{
			for (int j = bottomTile; j <= topTile; j++)
			{
				Tile t = this->get(i, j, 0);
				if (t.is_solid())
				{
					tbb = t.get_boundingBox();
					tile = t;
					return true;
				}
			}
		}
		return false;
	}


	// -------------- TILE METHODS -----------------------

	Tile::Tile(TileMap* map)
	{
		this->tileID = 0;
		this->sheetID = 0;
		this->sheetIndex = 0;
		this->position = Vector2();
		this->solid = false;
		this->oneWay = false;
		this->boundingBox = AABB();
		this->tileMap = map;
	}

	Tile::Tile(Vector2 pos, unsigned width, unsigned height, TileMap* map)
		: Tile(0, pos, false, false, width, height, map)
	{ }

	Tile::Tile(unsigned tileID, Vector2 pos, bool solid, bool oneWay,
		unsigned width, unsigned height, TileMap* map)
	{
		this->tileID = tileID;
		this->sheetIndex = map->get_sheetIndexFromTileID(tileID);
		this->sheetID = this->tileID -  map->get_sheetInitialTileID(map->get_sheets()[this->sheetIndex]);
		this->position = pos;
		this->solid = solid;
		this->oneWay = oneWay;
		this->boundingBox = AABB(position, Vector2(pos.x + width, pos.y + height));
		this->tileMap = map;
	}

	Tile::Tile(const Tile& other)
	{
		this->tileID = other.tileID;
		this->sheetIndex = other.sheetIndex;
		this->sheetID = other.sheetID;
		this->position = other.position;
		this->solid = other.solid;
		this->oneWay = other.oneWay;
		this->boundingBox = other.boundingBox;
		this->tileMap = other.tileMap;
	}

	Tile & Tile::operator=(const Tile& other)
	{
		if (this != &other)
		{
			this->tileID = other.tileID;
			this->sheetIndex = other.sheetIndex;
			this->sheetID = other.sheetID;
			this->position = other.position;
			this->solid = other.solid;
			this->oneWay = other.oneWay;
			this->boundingBox = other.boundingBox;
			this->tileMap = other.tileMap;
		}
		return *this;
	}

	// ------------------ TILELAYER METHODS -------------------

	TileLayer::TileLayer(std::string name, unsigned width, unsigned height, TileMap *map)
		: properties(picojson::value())
	{
		tilelayer layer;
		for (unsigned y = 0; y < height; y++)
		{
			tilerow row;
			for (unsigned x = 0; x < width; x++)
			{
				row.push_back(Tile(map));
			}
			layer.push_back(row);
		}
		this->layer = layer;

		this->name = name;
		this->tileMap = map;
	}

	TileLayer::TileLayer(const TileLayer & other)
		: properties(picojson::value())
	{
		this->layer = other.layer;
		this->name = other.name;
		this->tileMap = other.tileMap;
		this->properties = other.properties;
	}

	TileLayer & TileLayer::operator=(const TileLayer & other)
	{
		if (this != &other)
		{
			this->layer = other.layer;
			this->name = other.name;
			this->tileMap = other.tileMap;
			this->properties = other.properties;
		}
		return *this;
	}

	Tile & TileLayer::get(unsigned x, unsigned y)
	{
		return this->layer[y][x];
	}
}