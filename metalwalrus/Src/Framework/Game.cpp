#include "Game.h"

#include <GL/glew.h>

// for random
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <vector>
using namespace std;

#include "Settings.h"
#include "Graphics/VertexData.h"
#include "Graphics/Texture2D.h"
#include "Graphics/TextureRegion.h"
#include "Graphics/FrameBuffer.h"
#include "Graphics/SpriteBatch.h"
#include "Graphics/Color.h"
#include "Math/Matrix3.h"
#include "Util/Debug.h"
#include "Util/IOUtil.h"

#include <lodepng.h>

namespace metalwalrus
{
	Texture2D *tex;
	Texture2D *tex2;
	TextureRegion *texRegion;
	FrameBuffer *frameBuffer;
	SpriteBatch *batch;
	
	float degrees = 0;

	VertData2D vertices[4];
	GLuint indices[] =
	{
		0, 1, 2, 3
	};

	VertexData *vertData;
	
	const int NUM_SPRITES = 10000;
	
	Vector2 positions[NUM_SPRITES] = {};

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
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		tex = Texture2D::create("assets/spritesheet.png");
		tex2 = Texture2D::create("assets/test.png");
		texRegion = new TextureRegion(tex, 8, 0, 16, 16);
		
		vertices[0].pos = Vector2(0, 0);
		vertices[1].pos = Vector2(0, Settings::TARGET_HEIGHT);
		vertices[2].pos = Vector2(Settings::TARGET_WIDTH, Settings::TARGET_HEIGHT);
		vertices[3].pos = Vector2(Settings::TARGET_WIDTH, 0);

		vertices[0].texCoord = Vector2(0, 0);
		vertices[1].texCoord = Vector2(0, 1);
		vertices[2].texCoord = Vector2(1, 1);
		vertices[3].texCoord = Vector2(1, 0);

		vertData = VertexData::create(vertices, 4, indices, 4);
		frameBuffer = new FrameBuffer(Settings::VIRTUAL_WIDTH, Settings::VIRTUAL_HEIGHT);
		
		batch = new SpriteBatch();
		
		srand(time(NULL));
		for (int i = 0; i < NUM_SPRITES; i++)
		{
			positions[i] = Vector2(rand() % 256, rand() % 240);
		}
	}

	void Game::Update(double delta)
	{
	    degrees += 1;
	    if (degrees > 360) degrees = 0;
	}

	void Game::Draw()
	{
		glLoadIdentity();
		frameBuffer->bind();
		
		// background color of scene
		context->clear(Color::BLUE);
		
		batch->begin();
		
		for (int i = 0; i < NUM_SPRITES; i++)
		{
			batch->drawtex(*tex2, positions[i].x, positions[i].y, 1.0, 1.0, 0);
		}

		batch->end();

		frameBuffer->unbind();
		
		drawFrameBuffer();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void Game::drawFrameBuffer()
	{
		// the color of the black bars around the screen
		context->clear(Color::BLACK);

		glBindTexture(GL_TEXTURE_2D, frameBuffer->get_color());

		vertData->draw(1);
	}
}