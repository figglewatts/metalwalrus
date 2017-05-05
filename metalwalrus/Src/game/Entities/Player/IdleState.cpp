#include "States.h"

namespace metalwalrus
{
	void IdleState::enter(Player& p)
	{
		p.get_animatedSprite()->play("idle");
		p.get_playerInfo().canJump = true;
	}

	void IdleState::exit(Player& p)
	{

	}

	void IdleState::update(double delta, Player& p)
	{
		if (p.get_playerInfo().damaged)
		{
			machine->push(new DamagedState("damaged", machine), p);
			return;
		}
		
		if (p.get_playerInfo().shooting)
		{
			machine->push(new ShootState("shoot", machine), p);
			return;
		}
		
		if (p.get_playerInfo().moving)
		{
			machine->transition(new RunState("run", machine), p);
			return;
		}

		if (!p.get_playerInfo().onGround)
		{
			machine->transition(new InAirState("inAir", machine), p);
			return;
		}
	}
}