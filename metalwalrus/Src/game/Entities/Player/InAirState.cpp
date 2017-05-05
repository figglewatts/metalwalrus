#include "States.h"

namespace metalwalrus
{
	void InAirState::enter(Player& p)
	{
		p.get_animatedSprite()->play("jump");
		p.get_playerInfo().canJump = false;
	}

	void InAirState::exit(Player& p)
	{
	}

	void InAirState::update(double delta, Player& p)
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
		
		if (p.get_playerInfo().onGround)
		{
			machine->transition(new IdleState("idle", machine), p);
			return;
		}
	}
}