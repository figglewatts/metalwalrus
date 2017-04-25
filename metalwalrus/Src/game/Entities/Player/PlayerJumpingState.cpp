#include "States.h"

#include "../../../Framework/Input/InputHandler.h"

namespace metalwalrus
{	
	void PlayerJumpingState::enter(Player& p)
	{
		p.get_playerInfo().jumping = true;
		frameTimer = Player::jumpFrames;
		
		PlayerInAirState::enter(p);
	}

	void PlayerJumpingState::exit(Player& p)
	{
		p.get_playerInfo().jumping = false;
	}

	PlayerStateTuple PlayerJumpingState::changeState(Player& p)
	{
		if (frameTimer <= 0)
		{
			return std::make_tuple<IState<Player>*, bool>(new PlayerInAirState(machine), false);
		}
		
		return PlayerInAirState::changeState(p);
	}

	void PlayerJumpingState::update(double delta, Player& p)
	{
		if (InputHandler::checkButton("up", ButtonState::HELD))
		{
			if (frameTimer > 0)
				p.get_velocity().y = Player::jumpSpeed;
			frameTimer--;
		}
		else if (InputHandler::checkButton("up", ButtonState::IDLE))
		{
			frameTimer = 0;
		}

		PlayerInAirState::update(delta, p);
	}
}