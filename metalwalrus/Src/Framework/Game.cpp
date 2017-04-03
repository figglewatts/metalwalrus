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
	SpriteBatch *batch;
	
	Texture2D *fontTex;
	FontSheet *fontSheet;

	FrameBuffer *screenBuffer;
	VertData2D screenFboVertices[4];
	GLuint indices[] =
	{
		0, 1, 2, 3
	};
	VertexData *screenVbo;

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
		delete fontTex;
		delete fontSheet;
		delete screenVbo;
		delete screenBuffer;
		delete batch;
	}

	void Game::Start()
	{
		// initialize inputs
		InputHandler::addInput("left", true, { GLUT_KEY_LEFT });
		InputHandler::addInput("up", true, { GLUT_KEY_UP });
		InputHandler::addInput("down", true, { GLUT_KEY_DOWN });
		InputHandler::addInput("right", true, { GLUT_KEY_RIGHT });
		InputHandler::addInput("A", false, { 'z' });
		InputHandler::addInput("B", false, { 'x' });
		InputHandler::addInput("esc", false, { 27 }); // escape key
		InputHandler::addInput("f5", true, { GLUT_KEY_F5 }); // debug key
		
		// load fonts
		fontTex = Texture2D::create("assets/font.png");
		fontSheet = new FontSheet(fontTex, 8, 8, 0, 0);
		
		// create screen FBO
		screenFboVertices[0].pos = Vector2(0, 0);
		screenFboVertices[1].pos = Vector2(0, Settings::TARGET_HEIGHT);
		screenFboVertices[2].pos = Vector2(Settings::TARGET_WIDTH, Settings::TARGET_HEIGHT);
		screenFboVertices[3].pos = Vector2(Settings::TARGET_WIDTH, 0);

		screenFboVertices[0].texCoord = Vector2(0, 0);
		screenFboVertices[1].texCoord = Vector2(0, 1);
		screenFboVertices[2].texCoord = Vector2(1, 1);
		screenFboVertices[3].texCoord = Vector2(1, 0);

		screenVbo = VertexData::create(screenFboVertices, 4, indices, 4);
		screenBuffer = new FrameBuffer(Settings::VIRTUAL_WIDTH, Settings::VIRTUAL_HEIGHT);
		
		// create main SpriteBatch
		batch = new SpriteBatch();
	}

	void Game::Update(double delta)
	{
	    // toggle debug mode
		if (InputHandler::checkButton("f5", ButtonState::DOWN))
			Debug::debugMode = !Debug::debugMode;
	}

	void Game::Draw()
	{
		glLoadIdentity();
		screenBuffer->bind();
			context->clear(Color::BLUE); // background color of scene
			batch->begin();

				if (Debug::debugMode)
					drawDebug(*batch);
		
			batch->end();
		screenBuffer->unbind();
		
		drawFrameBuffer();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void Game::drawFrameBuffer()
	{
		// the color of the black bars around the screen
		context->clear(Color::BLACK);

		glBindTexture(GL_TEXTURE_2D, screenBuffer->get_color());

		screenVbo->draw(1);
	}

	void Game::drawDebug(SpriteBatch& batch)
	{
		string debugString = "FT:  " + std::to_string(Debug::frameTime) + "\n"
			+ "DC:  " + std::to_string(Debug::get_drawCalls()) + "\n"
			+ "FPS: " + std::to_string(Debug::fps);
		fontSheet->drawText(batch, debugString, 0, 232);
	}
}