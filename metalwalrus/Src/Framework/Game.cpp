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
	
	float degrees = 0;

	VertData2D vertices[4];
	GLubyte indices[] =
	{
		0, 1, 2, 3
	};

	VertexData *vertData;

	Game::Game(char *windowTitle, int w, int h, GLContext *context)
	{
		this->windowTitle = windowTitle;
		this->width = w;
		this->height = h;
		this->context = context;
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
		vertices[1].pos = Vector2(0, 480);
		vertices[2].pos = Vector2(512, 480);
		vertices[3].pos = Vector2(512, 0);

		vertices[0].texCoord = Vector2(0, 0);
		vertices[1].texCoord = Vector2(0, 1);
		vertices[2].texCoord = Vector2(1, 1);
		vertices[3].texCoord = Vector2(1, 0);

		vertData = VertexData::create(vertices, 4, indices, 4);
		frameBuffer = new FrameBuffer(Settings::VIRTUAL_WIDTH, Settings::VIRTUAL_HEIGHT);
	}

	void Game::Update(double delta)
	{
	    degrees += 100 * delta;
	    if (degrees > 360) degrees = 0;
	}

	void Game::Draw()
	{
		glLoadIdentity();
		frameBuffer->bind();

		context->clear(1, 0, 0);

		glPushMatrix();
			texRegion->draw();
		glPopMatrix();

		glPushMatrix();
			Matrix3 resultMat = Matrix3();
			resultMat.translation(40, 40).rotate(degrees);
                        
			std::vector<float> glMat = resultMat.glMatrix();
            
			glLoadMatrixf(&glMat[0]);

			glBegin(GL_TRIANGLES);
			glVertex3f(25, 50, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(50, 0, 0);
			glEnd();
		glPopMatrix();

		frameBuffer->unbind();
		
		drawFrameBuffer();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void Game::drawFrameBuffer()
	{
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, frameBuffer->get_color());

		vertData->draw(1);
	}
}