#ifndef METALWALRUS_H
#define METALWALRUS_H
#pragma once

#include "../Framework/Game.h"

namespace metalwalrus
{
	class MetalWalrus : public Game
	{
		void drawFrameBuffer();
		void drawDebug(SpriteBatch& batch);
	public:
		MetalWalrus(char *windowTitle, int w, int h, GLContext *context) 
			: Game(windowTitle, w, h, context) { }
		~MetalWalrus();

		void start() override;
		void update(double delta) override;
		void draw() override;
	};
}

#endif // METALWALRUS_H