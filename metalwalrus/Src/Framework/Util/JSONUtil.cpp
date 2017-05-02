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
			int layerNum = 0;
			for (auto layer : layers)
			{
				std::string layerName = layer.get("name").get<std::string>();
				
				if (layerNum > 0)
					tm->addLayer(layerName);
				else
					tm->get_layer(0)->set_name(layerName);

				TileLayer *layerObject = tm->get_layer(layerName);

				layerObject->properties = PropertyContainer(layer.get("properties"));

				picojson::array tiles = layer.get("data").get<picojson::array>();
				unsigned i = 0;
				for (auto tile = tiles.begin(); tile != tiles.end(); tile++)
				{
					unsigned x = i % width;
					unsigned y = (height - 1) - (i / width);
					unsigned tileID = tile->get<double>();

					Vector2 tilePos = Vector2(x * tileWidth, y * tileHeight);

					bool solid = false;
					if (!layerObject->properties.getProperty<bool>("objectLayer"))
					{
						solid = tileID == 0 ? false 
							: tm->get_sheetFromTileID(tileID - 1).properties
								.getProperty<bool>("solid", tileID - 1);
					}

					layerObject->get(x, y) = 
						Tile(tileID, tilePos,
							solid, tileWidth, tileHeight, tm);
					
					i++;
				}

				layerNum++;
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
