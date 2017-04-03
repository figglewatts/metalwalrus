#ifndef GAME_H
#define GAME_H
#pragma once

#include "Graphics/GLContext.h"
#include "Graphics/SpriteBatch.h"

namespace metalwalrus
{

class Game
{
	char *windowTitle;
	int width;
	int height;
	GLContext *context;

	void drawFrameBuffer();
	void drawDebug(SpriteBatch& batch);
public:
	Game(char *windowTitle, int w, int h, GLContext *context);
	~Game();
	void Start();
	void Update(double delta);
	void Draw();

	char *getTitle() { return windowTitle; }
	int getWidth() { return width; }
	int getHeight() { return height; }
};



}
#endif