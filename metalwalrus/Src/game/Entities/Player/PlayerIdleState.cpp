#include "States.h"

namespace metalwalrus
{
	void PlayerIdleState::enter(Player& p)
	{
		p.get_animatedSprite()->play("idle");
	}

	void PlayerIdleState::exit(Player& p)
	{
		
	}
	
	std::tuple<IState<Player>*, bool> PlayerIdleState::changeState(Player& p)
	{
		return PlayerOnGroundState::changeState(p);
	}

	void PlayerIdleState::update(double delta, Player& p)
	{
		
	}
}