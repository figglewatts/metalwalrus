#ifndef FRAMEANIMATION_H
#define FRAMEANIMATION_H
#pragma once

#include <functional>

namespace metalwalrus
{
	class FrameAnimation
	{
		int frameCount = 1;
		int startFrame = 0;
		float frameLength = 0;
		int currentFrame;
		float frameTimer = 0;
		int playCount = 0;
		std::string nextAnimation;
		std::function<void()> onFinish;
		bool finished = false;

		void animateFrame(bool reverse)
		{
			if ((!reverse && this->currentFrame < (this->startFrame + this->frameCount - 1))
				|| (reverse && this->currentFrame > this->startFrame))
				reverse ? this->currentFrame-- : this->currentFrame++;
			else
			{
				finished = true;
				playCount++;
			}
		}

	public:
		FrameAnimation()
			: frameCount(1), startFrame(0), frameLength(1), currentFrame(startFrame),
			frameTimer(0), playCount(0), finished(false) { }
		FrameAnimation(int frameCount, int startFrame, float frameLength, 
			std::string nextAnimation = "")
			: frameCount(frameCount), startFrame(startFrame),
			frameLength(frameLength), currentFrame(startFrame),
			frameTimer(0), nextAnimation(nextAnimation) { }
		FrameAnimation(const FrameAnimation& other)
			: frameCount(other.frameCount), startFrame(other.startFrame),
			frameLength(other.frameLength), currentFrame(other.currentFrame), 
			frameTimer(other.frameTimer), playCount(other.playCount),
			nextAnimation(other.nextAnimation), onFinish(other.onFinish),
			finished(other.finished) { }

		FrameAnimation& operator=(const FrameAnimation& other)
		{
			if (this != &other)
			{
				this->frameCount = other.frameCount;
				this->startFrame = other.startFrame;
				this->frameLength = other.frameLength;
				this->currentFrame = other.currentFrame;
				this->frameTimer = other.frameTimer;
				this->playCount = other.playCount;
				this->nextAnimation = other.nextAnimation;
				this->onFinish = other.onFinish;
				this->finished = other.finished;
			}
			return *this;
		}

		int get_frameCount() const { return frameCount; }
		int get_startFrame() const { return startFrame; }
		float get_frameLength() const { return frameLength; }
		int get_currentFrame() const { return currentFrame; }
		void set_currentFrame(int frame) { currentFrame = frame; }
		int get_currentFrameRelative() const { return currentFrame - startFrame; }
		void set_currentFrameRelative(int frame) { currentFrame = startFrame + frame; }
		int get_playCount() const { return playCount; }
		std::string get_nextAnimation() const { return nextAnimation; }
		bool has_next() const { return !nextAnimation.empty(); }
		bool is_finished() const { return finished; }

		void registerOnFinish(std::function<void()> callback) { onFinish = callback; }
		void callback() const { if (onFinish != nullptr) onFinish(); }
		
		void resetToFirstFrame()
		{
			currentFrame = startFrame;
			finished = false;
			frameTimer = 0;
		}

		void resetToLastFrame()
		{
			currentFrame = startFrame + frameCount - 1;
			finished = false;
			frameTimer = 0;
		}

		void update(double delta, bool reverse)
		{
			if (frameLength == 0) return;
			
			frameTimer += delta;

			if (frameTimer > frameLength)
			{
				frameTimer = 0;
				animateFrame(reverse);
			}
		}
	};
}

#endif // FRAMEANIMATION_H