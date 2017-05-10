#include "RobotShooter.h"

namespace metalwalrus
{
	void RobotIdleState::enter(RobotShooter& r)
	{
		r.get_animatedSprite().play("idle");
	}

	void RobotIdleState::update(double delta, RobotShooter& r)
	{
		if (r.get_playerSensed())
		{
			machine->transition(new RobotShootingState("shoot", machine), r);
			return;
		}
	}

	void RobotIdleState::exit(RobotShooter& r)
	{
		
	}
}