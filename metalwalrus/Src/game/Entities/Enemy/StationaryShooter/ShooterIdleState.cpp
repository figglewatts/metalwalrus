#include "StationaryShooter.h"

namespace metalwalrus
{
	void ShooterIdleState::enter(StationaryShooter& s)
	{
		frameTimer = s.get_shotCooldownFrames();
		if (s.get_isOpen())
			s.get_animatedSprite().playOneShot("close", [&s] {s.get_animatedSprite().play("idle");});
		else 
			s.get_animatedSprite().play("idle");
		s.get_isOpen() = false;
	}
	
	void ShooterIdleState::update(double delta, StationaryShooter& s)
	{
		frameTimer--;
		if (frameTimer <= 0)
		{
			machine->transition(new ShooterShootState("shoot", machine), s);
			return;
		}
	}

	void ShooterIdleState::exit(StationaryShooter& s)
	{
		
	}
}