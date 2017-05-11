#ifndef GAMESCENE_H
#define GAMESCENE_H
#pragma once

#include "../../Framework/Scene/IScene.h"
#include "../../Framework/Graphics/TileMap.h"
#include "../../Framework/Graphics/Camera.h"

#include "../Entities/Player/Player.h"
#include "../Entities/World/Ladder.h"
#include "../Entities/World/KillBox.h"
#include "../Entities/World/LevelFinish.h"

namespace metalwalrus
{
	class GameScene : public IScene
	{
		static Camera *camera;
		SpriteBatch *batch;
		std::vector<std::string> levels;

		void loadMapObjects();
		void onLevelLoad();
	public:
		~GameScene();

		void start() override;
		void update(double delta) override;
		void draw() override;

		static TileMap *loadedMap;
		static int playerID;
		static std::vector<GameObject*> *enemies;
		static std::vector<Ladder*> ladders;
		static std::vector<KillBox*> killBoxes;
		static std::vector<LevelFinish*> levelFinish;
		static int currentLevel;
		static const float gravity;
		static const float terminalVelocity;
		static bool playerDead;

		void loadLevel(int levelIndex);
	};
}

#endif