#include "States.h"

namespace metalwalrus
{
	void RunState::enter(Player& p)
	{
		p.get_animatedSprite()->play("run");
		p.get_playerInfo().canJump = true;
	}

	void RunState::exit(Player& p)
	{
		
	}

	void RunState::update(double delta, Player& p)
	{
		if (p.get_playerInfo().shooting)
		{
			machine->push(new ShootState("shoot", machine), p);
			return;
		}
		
		if (!p.get_playerInfo().moving)
		{
			machine->transition(new IdleState("idle", machine), p);
			return;
		}

		if (!p.get_playerInfo().onGround)
		{
			machine->transition(new InAirState("inAir", machine), p);
			return;
		}
	}
}