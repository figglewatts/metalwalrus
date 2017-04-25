#include "States.h"

#include "../../../Framework/Input/InputHandler.h"

namespace metalwalrus
{
	int frameTimer = 0;

	const static int SHOOTING_ANIMATION_FRAMES = 40;
	const static int SHOOTING_COOLDOWN = 20;

	void PlayerShootingState::enter(Player& p)
	{
		// check to see which state is underneath this one
		if (dynamic_cast<PlayerRunningState*>(machine->peekBelow()) != NULL)
		{
			// we're on the ground shooting while running
			p.get_animatedSprite()->play("runShoot");
		}
		else if (dynamic_cast<PlayerIdleState*>(machine->peekBelow()) != NULL)
		{
			// we're on the ground shooting while not running
			p.get_animatedSprite()->play("idleShoot");
		}
		else if (dynamic_cast<PlayerInAirState*>(machine->peekBelow()) != NULL)
		{
			// we're shooting while in the air
			p.get_animatedSprite()->play("jumpShoot");
		}

		frameTimer = SHOOTING_ANIMATION_FRAMES;
		// shoot a bullet
	}

	void PlayerShootingState::exit(Player& p)
	{
		if (p.get_playerInfo().onGround)
		{
			p.get_animatedSprite()->play("idle");
		}
	}

	std::tuple<IState<Player>*, bool> PlayerShootingState::changeState(Player& p)
	{
		if (frameTimer <= 0)
		{
			// we have not shot again, change back to prior state
			return std::make_tuple<IState<Player>*, bool>(nullptr, true);
		}
		else if (frameTimer <= SHOOTING_ANIMATION_FRAMES - SHOOTING_COOLDOWN)
		{
			if (p.get_playerInfo().onGround)
			
			if (InputHandler::checkButton("space", ButtonState::DOWN))
			{
				// we've shot again
				return std::make_tuple<IState<Player>*, bool>(new PlayerShootingState(machine), false);
			}
		}

		if (InputHandler::checkButton("up", ButtonState::DOWN))
		{
			if (p.get_playerInfo().canJump)
			{
				machine->popState(p);
				return std::make_tuple<IState<Player>*, bool>(new PlayerJumpingState(machine), false);
			}
		}
		else if (InputHandler::checkButton("right", ButtonState::HELD))
		{
			p.get_playerInfo().facingLeft = false;
			machine->popState(p);
			return std::make_tuple<IState<Player>*, bool>(new PlayerRunningState(machine), false);
		}
		else if (InputHandler::checkButton("left", ButtonState::HELD))
		{
			p.get_playerInfo().facingLeft = true;
			machine->popState(p);
			return std::make_tuple<IState<Player>*, bool>(new PlayerRunningState(machine), true);
		}
		

		return std::make_tuple<IState<Player>*, bool>(nullptr, false);
	}

	void PlayerShootingState::update(double delta, Player& p)
	{
		frameTimer--;
		if (frameTimer < 0)
			frameTimer = 0;
	}
}