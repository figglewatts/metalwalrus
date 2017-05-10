#include "BouncingRobot.h"

namespace metalwalrus
{
	void BouncerIdleState::enter(BouncingRobot& b)
	{
		if (b.get_springExtended())
			b.get_animatedSprite().playOneShot("compress", [&b] { b.get_animatedSprite().play("idle"); });
		else 
			b.get_animatedSprite().play("idle");
		b.get_springExtended() = false;
		timer = b.get_timeOnGround();
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