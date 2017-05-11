#include "TitleScreenScene.h"

#include "../../Framework/Graphics/FontSheet.h"
#include "../../Framework/Input/InputHandler.h"
#include "../../Framework/Scene/SceneManager.h"
#include "GameScene.h"
#include "../../Framework/Graphics/GLContext.h"

#include <cmath>

namespace metalwalrus
{
	extern Texture2D *fontTex;
	extern FontSheet *font;

	Texture2D *logoTex;
	Vector2 logoPos = Vector2(0, 125);

	Vector2 startTextPos = Vector2(66, 70);
	Vector2 authorTextPos = Vector2(75, 115);

	bool drawStartText = true;
	float t = 0;
	
	TitleScreenScene::~TitleScreenScene()
	{
		delete batch;
		delete logoTex;
	}

	void TitleScreenScene::start()
	{
		this->updateable = true;
		
		GLContext::clearColor = Color::BLACK;
		
		batch = new SpriteBatch();

		fontTex = Texture2D::create("assets/font.png");
		font = new FontSheet(fontTex, 8, 8);

		logoTex = Texture2D::create("assets/sprite/logo.png");
	}

	void TitleScreenScene::update(double delta)
	{
		t += delta;
		drawStartText = (fmod(t, 1) < 0.5);

		if (InputHandler::checkButton("shoot", ButtonState::DOWN))
		{
			SceneManager::switchScene(new GameScene());
		}
	}

	void TitleScreenScene::draw()
	{
		batch->begin();

		batch->drawtex(*logoTex, logoPos.x, logoPos.y);

		font->drawText(*batch, "By Sam Gibson", authorTextPos.x, authorTextPos.y);

		if (drawStartText)
			font->drawText(*batch, "Press X to play", startTextPos.x, startTextPos.y);

		batch->end();
	}
}
