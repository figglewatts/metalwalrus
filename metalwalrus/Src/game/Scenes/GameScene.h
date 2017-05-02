#ifndef GAMESCENE_H
#define GAMESCENE_H
#pragma once

#include "../../Framework/Scene/IScene.h"
#include "../../Framework/Graphics/TileMap.h"
#include "../../Framework/Graphics/Camera.h"

#include "../Entities/Player/Player.h"

namespace metalwalrus
{
	class GameScene : public IScene
	{
		Camera *camera;
		SpriteBatch *batch;

		void loadMapObjects();
	public:
		~GameScene();

		void start() override;
		void update(double delta) override;
		void draw() override;

		static TileMap *loadedMap;
		static int playerID;
	};
}

#endif