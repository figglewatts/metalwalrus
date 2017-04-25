#include "States.h"

namespace metalwalrus
{
	void PlayerDamagedState::enter(Player& p)
	{
		
	}

	void PlayerDamagedState::exit(Player& p)
	{
		
	}

	std::tuple<IState<Player>*, bool> PlayerDamagedState::changeState(Player& p)
	{
		return PlayerState::changeState(p);
	}

	void PlayerDamagedState::update(double delta, Player& p)
	{
		
	}
}