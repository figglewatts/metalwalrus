#include "BouncingRobot.h"

namespace metalwalrus
{
	void BouncerBouncingState::enter(BouncingRobot& b)
	{
		b.get_animatedSprite().play("inAir");
		b.get_springExtended() = true;
		b.jump();
	}

	void BouncerBouncingState::update(double delta, BouncingRobot& b)
	{
		if (b.get_onGround())
		{
			machine->transition(new BouncerIdleState("idle", machine), b);
			return;
		}
	}

	void BouncerBouncingState::exit(BouncingRobot& b)
	{
		
	}
}