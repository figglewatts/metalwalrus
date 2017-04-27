#include "States.h"

namespace metalwalrus
{
	void InAirState::enter(Player& p)
	{
		p.get_animatedSprite()->play("jump");
	}

	void InAirState::exit(Player& p)
	{
		p.get_playerInfo().canJump = true;
	}

	void InAirState::update(double delta, Player& p)
	{
		if (p.get_playerInfo().onGround)
		{
			machine->transition(new IdleState("idle", machine), p);
			return;
		}

		if (p.get_playerInfo().shooting)
		{
			machine->push(new ShootState("shoot", machine), p);
			return;
		}
	}
}