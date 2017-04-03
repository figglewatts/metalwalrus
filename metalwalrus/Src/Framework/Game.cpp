#include "Game.h"

#include <GL/glew.h>
#include <GL/glut.h>

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
#include "Graphics/FontSheet.h"
#include "Input/InputHandler.h"
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

	Texture2D *fontTex;
	FontSheet *fontSheet;
	
	float degrees = 0;

	VertData2D vertices[4];
	GLuint indices[] =
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
		InputHandler::addInput("left", true, { GLUT_KEY_LEFT });
		InputHandler::addInput("up", true, { GLUT_KEY_UP });
		InputHandler::addInput("down", true, { GLUT_KEY_DOWN });
		InputHandler::addInput("right", true, { GLUT_KEY_RIGHT });
		InputHandler::addInput("A", false, { 'z' });
		InputHandler::addInput("B", false, { 'x' });
		InputHandler::addInput("esc", false, { 27 }); // escape key
		InputHandler::addInput("f5", true, { GLUT_KEY_F5 }); // debug key
		
		tex = Texture2D::create("assets/spritesheet.png");
		tex2 = Texture2D::create("assets/test.png");
		fontTex = Texture2D::create("assets/font.png");
		fontSheet = new FontSheet(fontTex, 8, 8, 0, 4);
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
	}

	void Game::Update(double delta)
	{
	    if (InputHandler::checkButton("left", ButtonState::HELD))
			degrees += 1;
		if (InputHandler::checkButton("right", ButtonState::HELD))
			degrees -= 1;
	    if (degrees > 360) degrees = 0;
		else if (degrees < 0) degrees = 360;
	}

	void Game::Draw()
	{
		glLoadIdentity();
		frameBuffer->bind();
		
		// background color of scene
		context->clear(Color::BLUE);
		
		batch->begin();

		fontSheet->drawText(*batch, "Degrees: " + std::to_string(degrees), 0, 232);
		
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