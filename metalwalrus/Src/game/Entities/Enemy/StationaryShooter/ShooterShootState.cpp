#include "StationaryShooter.h"

namespace metalwalrus
{
	void ShooterShootState::enter(StationaryShooter& s)
	{
		frameTimer = s.get_shotCooldownFrames();
		if (!s.get_isOpen())
			s.get_animatedSprite().playOneShot("open", [&s] {
				s.get_animatedSprite().play("shoot");
				s.shoot();
			});
		else
			s.get_animatedSprite().play("shoot");
		s.get_isOpen() = true;
	}

	void ShooterShootState::update(double delta, StationaryShooter& s)
	{
		frameTimer--;
		if (frameTimer <= 0)
		{
			machine->transition(new ShooterIdleState("idle", machine), s);
			return;
		}
	}

	void ShooterShootState::exit(StationaryShooter& s)
	{
		
	}
}