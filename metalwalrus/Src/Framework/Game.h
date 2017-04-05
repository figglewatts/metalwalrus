#ifndef GAME_H
#define GAME_H
#pragma once

#include "Graphics/GLContext.h"
#include "Graphics/SpriteBatch.h"
#include "Settings.h"

namespace metalwalrus
{

	class Game
	{
	protected:
		char *windowTitle;
		int width;
		int height;
		GLContext *context;

	public:
		Game(char *windowTitle, int w, int h, GLContext *context)
		{
			this->windowTitle = windowTitle;
			this->width = w;
			this->height = h;
			Settings::WIDTH = w;
			Settings::HEIGHT = h;
		}

		virtual ~Game() { };
		virtual void start() = 0;
		virtual void update(double delta) = 0;
		virtual void draw() = 0;

		char *getTitle() { return windowTitle; }
		int getWidth() { return width; }
		int getHeight() { return height; }
	};



}
#endif // GAME_H