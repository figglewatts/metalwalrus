#include "JSONUtil.h"

#include <picojson.h>
#include <iostream>
#include <fstream>
#include <regex>

#include "Debug.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/SpriteSheet.h"

namespace metalwalrus
{
	namespace utilities
	{
		SpriteSheet *JSONUtil::tiled_spritesheet(std::string filePath)
		{
			picojson::value *json = jsonValueFromFile(filePath);
			unsigned spriteWidth = (unsigned)json->get("tilewidth").get<double>();
			unsigned spriteHeight = (unsigned)json->get("tileheight").get<double>();
			std::string texPath = json->get("image").get<std::string>();
			texPath.erase(0, 6);
			texPath.insert(0, "assets/");
			picojson::value properties = json->get("tileproperties");
			Texture2D *sheetTex = Texture2D::create(texPath);
			SpriteSheet *ss = new SpriteSheet(sheetTex, spriteWidth, spriteHeight, properties);

			delete json;
			return ss;
		}

		TileMap *JSONUtil::tiled_tilemap(std::string filePath, Camera *cam)
		{
			picojson::value *json = jsonValueFromFile(filePath);

			unsigned width = (unsigned)json->get("width").get<double>();
			unsigned height = (unsigned)json->get("height").get<double>();

			TileMap *tm = new TileMap(width, height, cam);

			picojson::array tilesets = json->get("tilesets").get<picojson::array>();
			for (auto it = tilesets.begin(); it != tilesets.end(); it++)
			{
				std::string pathToTileset = it->get("source").get<std::string>();
				pathToTileset.erase(0, 3);
				pathToTileset.insert(0, "assets/data/");
				SpriteSheet *ss = tiled_spritesheet(pathToTileset);
				tm->addTileSheet(ss);
			}
			
			unsigned tileWidth = tm->get_sheets()[0]->get_spriteWidth();
			unsigned tileHeight = tm->get_sheets()[0]->get_spriteHeight();

			picojson::array layers = json->get("layers").get<picojson::array>();
			for (auto it = layers.begin(); it != layers.end(); it++)
			{
				int layerNum = tm->get_layerCount();
				tm->addLayer();
				picojson::array tiles = it->get("data").get<picojson::array>();
				unsigned i = 0;
				for (auto tile = tiles.begin(); tile != tiles.end(); tile++)
				{
					unsigned x = i % width;
					unsigned y = (height - 1) - (i / width);
					unsigned tileID = tile->get<double>();
					bool solid = tileID == 0 ? false 
						: tm->get_sheets()[0]
							->getSpriteProperty<bool>(std::string("solid"), 
								to_string(tileID - 1));
					tm->get(x, y ,layerNum) = 
						Tile(tileID, 0, Vector2(x * tileWidth, y * tileWidth),
							solid, tileWidth, tileHeight);
					
					i++;
				}
			}

			return tm;
		}

		picojson::value *JSONUtil::jsonValueFromFile(std::string filePath)
		{
			std::ifstream jsonFile;
			jsonFile.open(filePath);
			picojson::value *v = new picojson::value();
			jsonFile >> *v;
			if (jsonFile.fail())
			{
				Debug::log(picojson::get_last_error().c_str(), Debug::LogType::ERR);
				return nullptr;
			}
			jsonFile.close();

			return v;
		}
	}
}