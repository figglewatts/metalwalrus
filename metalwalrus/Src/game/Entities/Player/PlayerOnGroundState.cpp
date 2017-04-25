#include "States.h"

#include "../../../Framework/Input/InputHandler.h"

namespace metalwalrus
{
	void PlayerOnGroundState::enter(Player& p)
	{
		p.get_playerInfo().canJump = true;
	}

	void PlayerOnGroundState::exit(Player& p)
	{
		
	}

	PlayerStateTuple PlayerOnGroundState::changeState(Player& p)
	{
		if (p.get_playerInfo().onGround == false)
		{
			return std::make_tuple<IState<Player>*, bool>(new PlayerInAirState(machine), false);
		}
		else if (InputHandler::checkButton("up", ButtonState::DOWN))
		{
			return std::make_tuple<IState<Player>*, bool>(new PlayerJumpingState(machine), false);
		}
		else if (InputHandler::checkButton("right", ButtonState::HELD))
		{
			p.get_playerInfo().facingLeft = false;
			return std::make_tuple<IState<Player>*, bool>(new PlayerRunningState(machine), false);
		}
		else if (InputHandler::checkButton("left", ButtonState::HELD))
		{
			p.get_playerInfo().facingLeft = true;
			return std::make_tuple<IState<Player>*, bool>(new PlayerRunningState(machine), false);
		}
		

		return PlayerState::changeState(p);
	}

	void PlayerOnGroundState::update(double delta, Player& p)
	{
		
	}
}
