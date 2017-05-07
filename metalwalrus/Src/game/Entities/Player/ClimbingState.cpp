#include "States.h"

namespace metalwalrus
{
	void ClimbingState::enter(Player& p)
	{
		p.get_animatedSprite()->play("climbing");
	}

	void ClimbingState::update(double delta, Player& p)
	{
		if (p.get_playerInfo().damaged)
		{
			machine->push(new DamagedState("damaged", machine), p);
			return;
		}

		if (!p.get_playerInfo().climbing)
		{
			machine->transition(new IdleState("idle", machine), p);
			return;
		}

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

		if (!p.get_playerInfo().moving)
		{
			p.get_animatedSprite()->pause();
		}
		else
		{
			p.get_animatedSprite()->resume();
		}
	}

	void ClimbingState::exit(Player& p)
	{
		p.get_playerInfo().climbing = false;
		p.get_playerInfo().canJump = false;

		// move the player a little on the x axis to stop them falling down again
		//p.moveBy(Vector2(p.get_playerInfo().facingLeft ? -3 : 2, 0));
	}
}