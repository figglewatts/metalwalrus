#include "Game.h"

#include <GL/glew.h>

#include <iostream>
#include <vector>
using namespace std;

#include "Settings.h"
#include "Graphics/VertexData.h"
#include "Graphics/Texture2D.h"
#include "Graphics/TextureRegion.h"
#include "Graphics/FrameBuffer.h"
#include "Util/Debug.h"
#include "Util/IOUtil.h"

#include <lodepng.h>

namespace metalwalrus
{
	Texture2D *tex;
	TextureRegion *texRegion;
	FrameBuffer *frameBuffer;

	float vertices[] =
	{
		0, 0,
		0, 200,
		250, 200,
		250, 0
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
		Settings::WIDTH = w;
		Settings::HEIGHT = h;
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
		frameBuffer = new FrameBuffer(150, 100);
	}

	void Game::Update(double delta)
	{

	}

	void Game::Draw()
	{
		frameBuffer->bind();

		glClearColor(1, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		//texRegion->draw();
		
		//glColor3f(0, 1, 0);

		glPushMatrix();

		glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 0.5F);
		glVertex2f(0.5F, 0.5F);
		glVertex2f(0.5F, 0);
		glEnd();

		glPopMatrix();

		frameBuffer->unbind();

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, frameBuffer->get_color());

		//glBindTexture(GL_TEXTURE_2D, frameBuffer->get_BufferTex()->get_glHandle());
		vertData->draw(1);
		//frameBuffer->get_BufferTex()->bind();

		//frameBuffer->get_BufferTex()->unbind();

		glMatrixMode(GL_MODELVIEW);
	}
}