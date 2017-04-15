#include "MetalWalrus.h"

#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "../Framework/Settings.h"
#include "../Framework/Graphics/VertexData.h"
#include "../Framework/Graphics/Texture2D.h"
#include "../Framework/Graphics/FrameBuffer.h"
#include "../Framework/Graphics/SpriteBatch.h"
#include "../Framework/Graphics/Color.h"
#include "../Framework/Graphics/FontSheet.h"
#include "../Framework/Graphics/Camera.h"
#include "../Framework/Graphics/TileMap.h"
#include "../Framework/Input/InputHandler.h"
#include "../Framework/Util/Debug.h"
#include "../Framework/Util/JSONUtil.h"

#include "Entities/Player.h"

namespace metalwalrus
{
	SpriteBatch *batch;

	Texture2D *fontTex;
	FontSheet *fontSheet;

	SpriteSheet *fromJson;
	TileMap *tileMap;

	Camera *camera;

	FrameBuffer *screenBuffer;
	VertData2D screenFboVertices[4];
	GLuint indices[] =
	{
		0, 1, 2, 3
	};
	VertexData *screenVbo;

	Player *player;

	MetalWalrus::~MetalWalrus()
	{
		delete fontTex;
		delete fontSheet;
		delete screenVbo;
		delete screenBuffer;
		delete batch;
		delete camera;
		delete fromJson;
		delete tileMap;
		delete player;
	}

	void MetalWalrus::start()
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

		// create camera
		camera = new Camera();

		tileMap = utilities::JSONUtil::tiled_tilemap("assets/data/level/playground.json", camera);

		player = new Player(Vector2(150, 230), 12, 20, Vector2(11, 0));
		player->updateCollisionEnvironment(tileMap);
		player->start();
	}

	void MetalWalrus::update(double delta)
	{
		// toggle debug mode
		if (InputHandler::checkButton("f5", ButtonState::DOWN))
			Debug::debugMode = !Debug::debugMode;

		player->update(delta);

		Vector2 playerCenter = player->get_center();
		camera->centerOn(Vector2(playerCenter.x, playerCenter.y));
	}

	void MetalWalrus::draw()
	{
		glLoadIdentity();
		screenBuffer->bind();
		context->clear(Color(0.38, 0.827, 0.890)); // background color of scene
		batch->begin();
		// set to world coords
		batch->setTransformMat(camera->getTransform());

		// draw world
		tileMap->draw(*batch, 16, 17);

		player->draw(*batch);

		// screen coords
		batch->setTransformMat(Matrix3());

		// draw overlays
		if (Debug::debugMode)
			drawDebug(*batch);

		batch->end();
		screenBuffer->unbind();

		drawFrameBuffer();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void MetalWalrus::drawFrameBuffer()
	{
		// the color of the black bars around the screen
		context->clear(Color::BLACK);

		glBindTexture(GL_TEXTURE_2D, screenBuffer->get_color());

		screenVbo->draw(1);
	}

	void MetalWalrus::drawDebug(SpriteBatch& batch)
	{
		string debugString = "FT:  " + std::to_string(Debug::frameTime) + "\n"
			+ "DC:  " + std::to_string(Debug::get_drawCalls()) + "\n"
			+ "FPS: " + std::to_string(Debug::fps);
		fontSheet->drawText(batch, debugString, 0, 232);
	}
}