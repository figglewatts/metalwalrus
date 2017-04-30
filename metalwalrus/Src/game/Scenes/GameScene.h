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
		TileMap *tileMap;
		Camera *camera;
		SpriteBatch *batch;

		Player *player;
	public:
		~GameScene();

		void start() override;
		void update(double delta) override;
		void draw() override;
	};
}

#endif