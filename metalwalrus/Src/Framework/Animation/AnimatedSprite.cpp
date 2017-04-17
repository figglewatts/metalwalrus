#include "AnimatedSprite.h"

namespace metalwalrus
{
	AnimatedSprite::AnimatedSprite(SpriteSheet *animationSheet)
	{
		this->animationSheet = animationSheet;
		this->isAnimating = false;
		this->loop = false;
	}

	AnimatedSprite::AnimatedSprite(const AnimatedSprite& other)
	{
		this->animationSheet = other.animationSheet;
		this->isAnimating = other.isAnimating;
		this->animations = other.animations;
		this->currentAnimation = other.currentAnimation;
		this->loop = other.loop;
		this->animationQueue = other.animationQueue;
	}

	AnimatedSprite& AnimatedSprite::operator=(const AnimatedSprite& other)
	{
		if (this != &other)
		{
			this->animationSheet = other.animationSheet;
			this->isAnimating = other.isAnimating;
			this->animations = other.animations;
			this->currentAnimation = other.currentAnimation;
			this->loop = other.loop;
			this->animationQueue = other.animationQueue;
		}
		return *this;
	}

	std::vector<std::string> AnimatedSprite::get_animations()
	{
		std::vector<std::string> returnVal;
		for (auto anim : animations)
			returnVal.push_back(anim.first);
		return returnVal;
	}

	void AnimatedSprite::addAnimation(std::string name, FrameAnimation anim)
	{
		animations.insert(std::make_pair(name, anim));
	}

	void AnimatedSprite::playOneShot(std::string name)
	{
		this->animations[currentAnimation].resetToFirstFrame();
		this->currentAnimation = name;
		this->isAnimating = true;
		this->loop = false;
	}

	void AnimatedSprite::playOneShot(std::string name, std::function<void()> onFinish)
	{
		this->animations[name].registerOnFinish(onFinish);
		this->playOneShot(name);
	}

	void AnimatedSprite::play(std::string name)
	{
		if (currentAnimation == name) return;
		this->animations[currentAnimation].resetToFirstFrame();
		this->currentAnimation = name;
		this->isAnimating = true;
		this->loop = true;
	}

	void AnimatedSprite::play(std::string name, std::function<void()> onLoop)
	{
		if (currentAnimation == name) return;
		this->animations[name].registerOnFinish(onLoop);
		this->play(name);
	}

	void AnimatedSprite::stop()
	{
		this->isAnimating = false;
		this->animations[currentAnimation].resetToFirstFrame();
	}

	void AnimatedSprite::pause()
	{
		this->isAnimating = false;
	}

	void AnimatedSprite::resume()
	{
		this->isAnimating = true;
	}

	void AnimatedSprite::queue(std::string name, std::function<void()> onFinish)
	{
		this->animationQueue.push(name);
		this->animations[name].registerOnFinish(onFinish);
	}

	void AnimatedSprite::queue(std::string name)
	{
		this->animationQueue.push(name);
	}

	void AnimatedSprite::update(double delta)
	{
		if (!isAnimating)
			return;
		if (currentAnimation.empty())
			return;

		auto current = &animations[currentAnimation];

		current->update(delta);

		if (current->is_finished())
		{
			if (loop)
				current->resetToFirstFrame();
			else
			{
				if (current->has_next())
				{
					currentAnimation = current->get_nextAnimation();
				}
				else if (animationQueue.size() > 0)
				{
					currentAnimation = animationQueue.front();
					animationQueue.pop();
				}
				else
				{
					isAnimating = false;
				}
				current->resetToFirstFrame();
				current->callback();
			}
		}
	}

	TextureRegion *AnimatedSprite::get_keyframe()
	{
		return animationSheet->get_sprite(
			animations[currentAnimation].get_currentFrame());
	}
}