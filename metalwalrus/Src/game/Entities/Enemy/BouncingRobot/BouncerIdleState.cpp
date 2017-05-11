#include "BouncingRobot.h"

namespace metalwalrus
{
	void BouncerIdleState::enter(BouncingRobot& b)
	{
		timer = b.get_timeOnGround();
		if (b.get_springExtended())
			b.get_animatedSprite().playOneShot("compress", [&b] { b.get_animatedSprite().play("idle"); });
		else 
		{
			timer = 0;
			b.get_animatedSprite().play("idle");
		}
		b.get_springExtended() = false;
	}

	void BouncerIdleState::update(double delta, BouncingRobot& b)
	{
		timer -= delta;
		if (timer <= 0)
		{
			machine->transition(new BouncerBouncingState("bouncing", machine), b);
			return;
		}
	}

	void BouncerIdleState::exit(BouncingRobot& b)
	{
		
	}
}