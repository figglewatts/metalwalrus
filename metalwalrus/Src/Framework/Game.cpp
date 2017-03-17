#include "Game.h"

#include <iostream>
#include <vector>
using namespace std;

#include "Graphics/VertexData.h"
#include "Graphics/Texture2D.h"
#include "Graphics/TextureRegion.h"
#include "Util/Debug.h"
#include "Util/IOUtil.h"

#include <lodepng.h>

#include <GL/freeglut.h>

namespace metalwalrus
{
	Texture2D *tex;
	TextureRegion *texRegion;

	VertexData vertData;

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

		float vertices[] =
		{
			100, 100,
			100, 200,
			200, 200,
			200, 100
		};
		GLubyte indices[] = 
		{
			0, 1, 2, 3
		};

		vertData = VertexData(vertices, 4, indices, 4);
	}

	void Game::Update(double delta)
	{

	}

	void Game::Draw()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		texRegion->draw();

		vertData.draw(1);

		glMatrixMode(GL_MODELVIEW);
	}
}