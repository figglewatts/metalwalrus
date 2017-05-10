#include "RobotShooter.h"

namespace metalwalrus
{
	void RobotShootingState::enter(RobotShooter& r)
	{
		shotCooldownTimer = r.get_shotCooldown();
		timeBetweenShotsTimer = 0;
		shotCount = 0;

		r.get_animatedSprite().play("shoot");
	}

	void RobotShootingState::update(double delta, RobotShooter& r)
	{
		if (!r.get_playerSensed())
		{
			machine->transition(new RobotIdleState("idle", machine), r);
			return;
		}
		
		shotCooldownTimer -= delta;
		if (shotCooldownTimer <= 0)
		{
			r.shoot();
			shotCooldownTimer = r.get_shotCooldown();
		}
	}

	void RobotShootingState::exit(RobotShooter& r)
	{
		
	}
}