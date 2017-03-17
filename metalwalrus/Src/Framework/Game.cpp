#include "Game.h"

#include <GL/glew.h>

#include <iostream>
#include <vector>
using namespace std;

#include "Graphics/VertexData.h"
#include "Graphics/Texture2D.h"
#include "Graphics/TextureRegion.h"
#include "Util/Debug.h"
#include "Util/IOUtil.h"

#include <lodepng.h>

namespace metalwalrus
{
	Texture2D *tex;
	TextureRegion *texRegion;

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

	VertexData *vertData;

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
		delete vertData;
	}

	void Game::Start()
	{
		tex = Texture2D::create("assets/spritesheet.png");
		texRegion = new TextureRegion(tex, 8, 0, 16, 16);
		
		vertData = VertexData::create(vertices, 4, indices, 4);
	}

	void Game::Update(double delta)
	{

	}

	void Game::Draw()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		texRegion->draw();

		vertData->draw(1);

		glMatrixMode(GL_MODELVIEW);
	}
}