#ifndef TITLESCREENSCENE_H
#define TITLESCREENSCENE_H
#pragma once
#include "../../Framework/Scene/IScene.h"
#include "../../Framework/Graphics/SpriteBatch.h"

namespace metalwalrus
{
	class TitleScreenScene : public IScene
	{
		SpriteBatch *batch;
	public:
		~TitleScreenScene();

		void start() override;
		void update(double delta) override;
		void draw() override;
	};
}

#endif // TITLESCREENSCENE_H