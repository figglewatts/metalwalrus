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
			p.get_animatedSprite()->play("runShoot");
		}
		else if (machine->peekBelow()->get_name() == "inAir")
		{
			p.get_animatedSprite()->play("jumpShoot");
		}
	}

	void ShootState::exit(Player& p)
	{
		
	}

	void ShootState::update(double delta, Player& p)
	{
		if (!p.get_playerInfo().shooting)
		{
			machine->pop(p);
			return;
		}
	}
}