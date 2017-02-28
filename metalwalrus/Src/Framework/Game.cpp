#include<GL/freeglut.h>
#include <lodepng.h>
#include <iostream>
#include <vector>
using namespace std;

#include "Game.h"
#include "Util\Debug.h"
#include "Graphics\Texture2D.h"
#include "Util\IOUtil.h"

namespace metalwalrus
{
	Texture2D *tex;

	vector<unsigned char> *texData;

	GLuint texHandle;

	Game::Game(char *windowTitle, int w, int h)
	{
		this->windowTitle = windowTitle;
		this->width = w;
		this->height = h;
	}

	Game::~Game()
	{
		delete tex;
	}

	void Game::Start()
	{
		Debug::redirect("log.txt");
		tex = Texture2D::create("assets/test.png");
	}

	void Game::Update(double delta)
	{

	}

	void Game::Draw()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		tex->draw();

		glMatrixMode(GL_MODELVIEW);
	}
}