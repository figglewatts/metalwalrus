#include "States.h"

namespace metalwalrus
{
	void DamagedState::enter(Player& p)
	{
		p.get_animatedSprite()->play("damaged");
		frameTimer = Player::damageAnimationFrames;
		p.get_playerInfo().jumping = false;
		p.get_playerInfo().canJump = false;
		p.get_playerInfo().canMove = false;

		p.get_playerInfo().facingLeft = p.get_playerInfo().damagedFromLeft;

		p.get_velocity().x = p.get_playerInfo().damagedFromLeft ? 
			p.damageVelocity : -p.damageVelocity;
	}

	void DamagedState::update(double delta, Player& p)
	{
		frameTimer--;
		if (frameTimer <= 0)
		{
			machine->popAndUpdate(p);
			return;
		}
	}

	void DamagedState::exit(Player& p)
	{
		p.get_playerInfo().damaged = false;
		p.get_velocity().x = 0;
		p.get_playerInfo().canMove = true;
	}
}