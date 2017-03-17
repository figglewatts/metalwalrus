#ifndef GAME_H
#define GAME_H
#pragma once

namespace metalwalrus
{

class Game
{
	char *windowTitle;
	int width;
	int height;

public:
	Game(char *windowTitle, int w, int h);
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