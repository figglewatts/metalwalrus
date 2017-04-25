#include "States.h"

#include "../../../Framework/Input/InputHandler.h"

namespace metalwalrus
{
	void PlayerInAirState::enter(Player& p)
	{
		p.get_animatedSprite()->play("jump");
		p.get_playerInfo().canJump = false;
		p.get_playerInfo().onGround = false;
	}

	void PlayerInAirState::exit(Player& p)
	{
		
	}

	std::tuple<IState<Player>*, bool> PlayerInAirState::changeState(Player& p)
	{
		if (p.get_playerInfo().onGround)
		{
			return std::make_tuple<IState<Player>*, bool>(new PlayerOnGroundState(machine), false);
		}
		
		return PlayerState::changeState(p);
	}

	void PlayerInAirState::update(double delta, Player& p)
	{
		if (InputHandler::checkButton("left", ButtonState::HELD))
		{
			p.get_playerInfo().facingLeft = true;
			p.get_velocity().x = -Player::walkSpeed;
		}
		else if (InputHandler::checkButton("right", ButtonState::HELD))
		{
			p.get_playerInfo().facingLeft = false;
			p.get_velocity().x = Player::walkSpeed;
		}
		else if (InputHandler::checkButton("left", ButtonState::IDLE)
			&& InputHandler::checkButton("right", ButtonState::IDLE))
		{
			p.get_velocity().x = 0;
		}
	}
}