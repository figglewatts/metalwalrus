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
#include "Math/Matrix3.h"
#include "Util/Debug.h"
#include "Util/IOUtil.h"

#include <lodepng.h>

namespace metalwalrus
{
	Texture2D *tex;
	TextureRegion *texRegion;
	FrameBuffer *frameBuffer;

	VertData2D vertices[4];
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
		delete frameBuffer;
	}

	void Game::Start()
	{
		tex = Texture2D::create("assets/spritesheet.png");
		texRegion = new TextureRegion(tex, 8, 0, 16, 16);
		
		vertices[0].pos = Vector2(0, 0);
		vertices[1].pos = Vector2(0, 200);
		vertices[2].pos = Vector2(300, 200);
		vertices[3].pos = Vector2(300, 0);

		vertices[0].texCoord = Vector2(0, 0);
		vertices[1].texCoord = Vector2(0, 1);
		vertices[2].texCoord = Vector2(1, 1);
		vertices[3].texCoord = Vector2(1, 0);

		vertData = VertexData::create(vertices, 4, indices, 4);
		frameBuffer = new FrameBuffer(150, 100);
	}

	void Game::Update(double delta)
	{

	}

	void Game::Draw()
	{
		frameBuffer->bind();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
		glLoadIdentity();                       // Reset The View

		texRegion->draw();

		glPushMatrix();

		Matrix3 transMat = Matrix3();
		transMat.translation(30, 0).translation(0, 50).rotate(10).scale(1.5, 2);
		glLoadMatrixf(transMat.glMatrix());

		glBegin(GL_TRIANGLES);                      // Drawing Using Triangles
		glVertex3f(25, 50, 0);              // Top
		glVertex3f(0, 0, 0);              // Bottom Left
		glVertex3f(50, 0, 0);              // Bottom Right
		glEnd();

		glColor3f(1, 1, 1);

		glPopMatrix();

		frameBuffer->unbind();
		
		drawFrameBuffer();

		glMatrixMode(GL_MODELVIEW);
	}

	void Game::drawFrameBuffer()
	{
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, frameBuffer->get_color());

		glPushMatrix();

		vertData->draw(1);

		glPopMatrix();
	}
}