#include "TileMap.h"

namespace metalwalrus
{
	void TileMap::initializeEmpty()
	{
		layerCount++;
		for (unsigned y = 0; y < height; y++)
		{
			tilerow row;
			for (unsigned x = 0; x < width; x++)
			{
				vector<Tile> tileLayers;
				tileLayers.push_back(Tile());
				row.push_back(tileLayers);
			}
			tiles.push_back(row);
		}
	}

	TileMap::TileMap(unsigned width, unsigned height, Camera * cam)
	{
		this->width = width;
		this->height = height;
		this->camera = cam;
		this->layerCount = 0;
		this->initializeEmpty();
	}

	TileMap::TileMap(SpriteSheet *tileSheet, unsigned width, unsigned height,
		Camera* cam)
	{
		this->tileSheets.push_back(tileSheet);
		this->width = width;
		this->height = height;
		this->camera = cam;
		this->layerCount = 0;
		this->initializeEmpty();
	}

	TileMap::TileMap(const TileMap& other)
	{
		this->tiles = other.tiles;
		this->tileSheets = other.tileSheets;
		this->width = other.width;
		this->height = other.height;
		this->camera = other.camera;
		this->layerCount = other.layerCount;
	}

	TileMap & TileMap::operator=(const TileMap& other)
	{
		if (this != &other)
		{
			this->tiles = other.tiles;
			this->tileSheets = other.tileSheets;
			this->width = other.width;
			this->height = other.height;
			this->camera = other.camera;
			this->layerCount = other.layerCount;
		}
		return *this;
	}

	Tile & TileMap::get(unsigned x, unsigned y, unsigned layer)
	{
		return tiles[y][x][layer];
	}

	void TileMap::append(Tile t, unsigned x, unsigned y)
	{
		tiles[y][x].push_back(t);
	}

	void TileMap::addLayer()
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				append(Tile(), x, y);
			}
		}
		layerCount++;
	}

	void TileMap::addTileSheet(SpriteSheet *sheet)
	{
		this->tileSheets.push_back(sheet);
	}

	void TileMap::draw(SpriteBatch& batch, unsigned squaresDown, unsigned squaresAcross)
	{
		Vector2 cameraPos = camera->getPosition();
		unsigned tileWidth = tileSheets[0]->get_spriteWidth();
		unsigned tileHeight = tileSheets[0]->get_spriteHeight();
		Vector2 firstSquare = Vector2(
			(cameraPos.x) / tileWidth,
			(cameraPos.y) / tileHeight);
		for (unsigned y = 0; y < squaresDown; y++)
		{
			for (unsigned x = 0; x < squaresAcross; x++)
			{
				for (unsigned l = 0; l < layerCount; l++)
				{
					unsigned tileXIndex = firstSquare.x + x;
					unsigned tileYIndex = firstSquare.y + y;

					if (tileXIndex >= width || tileYIndex >= height
						|| tileXIndex < 0 || tileYIndex < 0) continue;

					Tile t = tiles[tileYIndex][tileXIndex][l];

					if (t.get_tileID() == 0) continue;

					tileSheets[t.get_sheetIndex()]->drawTile(batch, 
						tileXIndex * tileWidth, tileYIndex * tileHeight,
						t.get_tileID()-1); // -1 due to 0 being blank tile
				}
			}
		}
	}


	// -------------- TILE METHODS -----------------------

	Tile::Tile()
	{
		this->tileID = 0;
		this->sheetIndex = 0;
		this->position = Vector2();
		this->solid = false;
		this->boundingBox = AABB();
	}

	Tile::Tile(Vector2 pos, unsigned width, unsigned height)
		: Tile(0, 0, pos, false, width, height)
	{ }

	Tile::Tile(unsigned tileID, unsigned sheetIndex, Vector2 pos, bool solid, 
		unsigned width, unsigned height)
	{
		this->tileID = tileID;
		this->sheetIndex = sheetIndex;
		this->position = pos;
		this->solid = solid;
		this->boundingBox = AABB(position, Vector2(pos.x + width, pos.y + height));
	}

	Tile::Tile(const Tile& other)
	{
		this->tileID = other.tileID;
		this->sheetIndex = other.sheetIndex;
		this->position = other.position;
		this->solid = other.solid;
		this->boundingBox = other.boundingBox;
	}

	Tile & Tile::operator=(const Tile& other)
	{
		if (this != &other)
		{
			this->tileID = other.tileID;
			this->sheetIndex = other.sheetIndex;
			this->position = other.position;
			this->solid = other.solid;
			this->boundingBox = other.boundingBox;
		}
		return *this;
	}
}