#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#pragma once

#include <map>
#include <queue>
#include <functional>

#include "../Graphics/SpriteSheet.h"
#include "FrameAnimation.h"

namespace metalwalrus
{
	class AnimatedSprite
	{
		SpriteSheet *animationSheet;
		bool isAnimating;
		std::map<std::string, FrameAnimation> animations;
		std::string currentAnimation;
		std::queue<std::string> animationQueue;
		bool loop;
		int currentFrameCounter;

	public:
		AnimatedSprite(SpriteSheet* animationSheet);
		AnimatedSprite(const AnimatedSprite& other);

		AnimatedSprite& operator=(const AnimatedSprite& other);

		bool get_isAnimating() const { return isAnimating; }
		bool get_looping() const { return loop; }
		void set_looping(bool looping) { this->loop = looping; }

		FrameAnimation get_currentAnim() const { return this->animations.at(currentAnimation); }

		std::vector<std::string> get_animations();

		void addAnimation(std::string name, FrameAnimation anim);

		void playOneShot(std::string name);
		void playOneShot(std::string name, std::function<void()> onFinish);
		void play(std::string name);
		void play(std::string name, std::function<void()> onLoop);
		void playAtFrame(std::string name, int frame);
		void playAtFrame(std::string name, int frame, std::function<void()> onLoop);
		void playForFrames(std::string name, int frames);
		void playForFrames(std::string name, int frames, std::function<void()> onFinish);
		void stop();
		void pause();
		void resume();
		void queue(std::string name);
		void queue(std::string name, std::function<void()> onFinish);

		void update(double delta);
		void draw(SpriteBatch& batch);
		TextureRegion *get_keyframe();
	};
}

#endif // ANIMATEDSPRITE_H