#include "States.h"

#include "../../../Framework/Input/InputHandler.h"

namespace metalwalrus
{
	void PlayerRunningState::enter(Player& p)
	{
		p.get_animatedSprite()->play("run");
		p.get_velocity().x = p.get_playerInfo().facingLeft ? -Player::walkSpeed : Player::walkSpeed;
	}

	void PlayerRunningState::exit(Player& p)
	{
		p.get_velocity().x = 0;
	}

	std::tuple<IState<Player>*, bool> PlayerRunningState::changeState(Player& p)
	{
		if (InputHandler::checkButton(p.get_playerInfo().facingLeft ? "left" : "right", ButtonState::UP))
		{
			return std::make_tuple<IState<Player>*, bool>(new PlayerIdleState(machine), false);
		}

		// change not handled, fall back to more generic state
		return PlayerOnGroundState::changeState(p);
	}

	void PlayerRunningState::update(double delta, Player& p)
	{
		
	}
}