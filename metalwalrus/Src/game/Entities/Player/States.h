#ifndef PLAYER_STATES
#define PLAYER_STATES
#pragma once

#include "../../../Framework/State/IState.h"
#include "../../../Framework/State/PushDownStateMachine.h"

#include "Player.h"

namespace metalwalrus
{
	typedef std::tuple<IState<Player>*, bool> PlayerStateTuple;
	
	class PlayerState : public IState<Player>
	{
	protected:
		PushDownStateMachine<Player>* machine;
	public:
		PlayerState(PushDownStateMachine<Player> *machine)
			: machine(machine) { }

		void enter(Player& p) override;
		void exit(Player& p) override;
		PlayerStateTuple changeState(Player &p) override;
		void update(double delta, Player& p) override;
	};
	
	class PlayerOnGroundState : public PlayerState
	{
	public:	
		PlayerOnGroundState(PushDownStateMachine<Player> *machine)
			: PlayerState(machine) { }

		void enter(Player& p) override;
		void exit(Player& p) override;
		PlayerStateTuple changeState(Player &p) override;
		void update(double delta, Player& p) override;
	};

	class PlayerIdleState : public PlayerOnGroundState
	{
	public:
		PlayerIdleState(PushDownStateMachine<Player> *machine)
			: PlayerOnGroundState(machine) { }

		void enter(Player& p) override;
		void exit(Player& p) override;
		PlayerStateTuple changeState(Player &p) override;
		void update(double delta, Player& p) override;
	};

	class PlayerRunningState : public PlayerOnGroundState
	{
	public:
		PlayerRunningState(PushDownStateMachine<Player> *machine)
			: PlayerOnGroundState(machine) { }

		void enter(Player& p) override;
		void exit(Player& p) override;
		PlayerStateTuple changeState(Player &p) override;
		void update(double delta, Player& p) override;
	};

	class PlayerInAirState : public PlayerState
	{
	public:
		PlayerInAirState(PushDownStateMachine<Player> *machine)
			: PlayerState(machine) { }

		void enter(Player &p) override;
		void exit(Player& p) override;
		PlayerStateTuple changeState(Player &p) override;
		void update(double delta, Player& p) override;
	};

	class PlayerJumpingState : public PlayerInAirState
	{
		int frameTimer;
	public:
		PlayerJumpingState(PushDownStateMachine<Player> *machine)
			: PlayerInAirState(machine) { }

		void enter(Player &p) override;
		void exit(Player &p) override;
		PlayerStateTuple changeState(Player &p) override;
		void update(double delta, Player &p) override;
	};

	class PlayerShootingState : public PlayerState
	{
		int frameTimer;
	public:
		PlayerShootingState(PushDownStateMachine<Player> *machine)
			: PlayerState(machine) { }

		void enter(Player &p) override;
		void exit(Player &p) override;
		PlayerStateTuple changeState(Player &p) override;
		void update(double delta, Player& p) override;
	};

	class PlayerDamagedState : public PlayerState
	{
	public:
		PlayerDamagedState(PushDownStateMachine<Player> *machine)
			: PlayerState(machine) { }

		void enter(Player &p) override;
		void exit(Player &p) override;
		PlayerStateTuple changeState(Player &p) override;
		void update(double delta, Player& p) override;
	};
}

#endif // PLAYER_STATES