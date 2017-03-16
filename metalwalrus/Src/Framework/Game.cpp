#include<GL/freeglut.h>
#include <lodepng.h>
#include <iostream>
#include <vector>
using namespace std;

#include "Game.h"
#include "Util/Debug.h"
#include "Graphics/Texture2D.h"
#include "Graphics/TextureRegion.h"
#include "Util/IOUtil.h"

namespace metalwalrus
{
	Texture2D *tex;
	TextureRegion *texRegion;

	Game::Game(char *windowTitle, int w, int h)
	{
		this->windowTitle = windowTitle;
		this->width = w;
		this->height = h;
	}

	Game::~Game()
	{
		delete tex;
		delete texRegion;
	}

	void Game::Start()
	{
		Debug::redirect("log.txt");
		
		// test comment

		tex = Texture2D::create("assets/spritesheet.png");
		texRegion = new TextureRegion(tex, 8, 0, 16, 16);
	}

	void Game::Update(double delta)
	{

	}

	void Game::Draw()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		texRegion->draw();

		glMatrixMode(GL_MODELVIEW);
	}
}