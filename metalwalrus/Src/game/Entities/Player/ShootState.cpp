#include "States.h"

namespace metalwalrus
{
	void ShootState::enter(Player& p)
	{
		if (machine->peekBelow()->get_name() == "idle")
		{
			p.get_animatedSprite()->play("idleShoot");
		}
		else if (machine->peekBelow()->get_name() == "run")
		{
			int runFrames = p.get_animatedSprite()->get_currentAnim().get_currentFrameRelative();
			p.get_animatedSprite()->playAtFrame("runShoot", runFrames);
		}
		else if (machine->peekBelow()->get_name() == "inAir")
		{
			p.get_animatedSprite()->play("jumpShoot");
		}
		frameTimer = Player::framesBetweenShotAnimation;
		p.get_playerInfo().canShoot = false;
	}

	void ShootState::exit(Player& p)
	{
		p.get_playerInfo().shooting = false;
		p.get_playerInfo().canShoot = true;
	}

	void ShootState::update(double delta, Player& p)
	{
		if (p.get_playerInfo().onGround && p.get_playerInfo().moving)
		{
			p.get_animatedSprite()->play("runShoot");
			p.get_playerInfo().canJump = true;
		}

		if (p.get_playerInfo().onGround && !p.get_playerInfo().moving)
		{
			p.get_animatedSprite()->play("idleShoot");
			p.get_playerInfo().canJump = true;
		}

		if (!p.get_playerInfo().onGround)
		{
			p.get_animatedSprite()->play("jumpShoot");
			p.get_playerInfo().canJump = false;
		}
		
		if (!p.get_playerInfo().shooting)
		{
			machine->popAndUpdate(p);
			return;
		}

		frameTimer--;

		if (p.get_playerInfo().canShoot == false
			&& frameTimer <= Player::framesBetweenShotAnimation - Player::framesBetweenShots)
		{
			p.get_playerInfo().canShoot = true;
			frameTimer = Player::framesBetweenShotAnimation;
		}
		else if (frameTimer <= 0)
		{
			machine->popAndUpdate(p);
			return;
		}
	}
}