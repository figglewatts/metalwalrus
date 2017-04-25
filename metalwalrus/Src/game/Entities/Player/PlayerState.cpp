#include "States.h"

#include "../../../Framework/Input/InputHandler.h"

namespace metalwalrus
{
	void PlayerState::enter(Player& p)
	{
		
	}

	void PlayerState::exit(Player& p)
	{
		
	}

	std::tuple<IState<Player>*, bool> PlayerState::changeState(Player& p)
	{
		if (InputHandler::checkButton("space", ButtonState::DOWN))
		{
			// add shooting state to stack
			return std::make_tuple<IState<Player>*, bool>(new PlayerShootingState(machine), true);
		}
		else if (InputHandler::checkButton("left", ButtonState::IDLE)
			&& InputHandler::checkButton("right", ButtonState::IDLE)
			&& p.get_playerInfo().onGround)
		{
			return std::make_tuple<IState<Player>*, bool>(new PlayerIdleState(machine), false);
		}
		
		// nothing was handled, stay in this state
		return std::make_tuple<IState<Player>*, bool>(nullptr, false);
	}

	void PlayerState::update(double delta, Player& p)
	{
		
	}
}