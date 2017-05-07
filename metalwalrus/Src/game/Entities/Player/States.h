#ifndef PLAYER_STATES
#define PLAYER_STATES
#pragma once

#include "../../../Framework/State/PushDownState.h"
#include "../../../Framework/State/PushDownStateMachine.h"

#include "Player.h"

namespace metalwalrus
{
	class IdleState : public PushDownState<Player>
	{
	public:
		IdleState(std::string name, PushDownStateMachine<Player> *machine)
			: PushDownState(name, machine) { }
		void enter(Player& p) override;
		void exit(Player& p) override;
		void update(double delta, Player& p) override;
	};

	class RunState : public PushDownState<Player>
	{
	public:
		RunState(std::string name, PushDownStateMachine<Player> *machine)
			: PushDownState(name, machine) { }
		void enter(Player& p) override;
		void exit(Player& p) override;
		void update(double delta, Player& p) override;
	};

	class InAirState : public PushDownState<Player>
	{
	public:
		InAirState(std::string name, PushDownStateMachine<Player> *machine)
			: PushDownState(name, machine) { }
		void enter(Player& p) override;
		void exit(Player& p) override;
		void update(double delta, Player& p) override;
	};

	class ShootState : public PushDownState<Player>
	{
		int frameTimer;
	public:
		ShootState(std::string name, PushDownStateMachine<Player> *machine)
			: PushDownState(name, machine), frameTimer(0) { }
		void enter(Player& p) override;
		void exit(Player& p) override;
		void update(double delta, Player& p) override;
	};

	class DamagedState : public PushDownState<Player>
	{
		int frameTimer;
	public:
		DamagedState(std::string name, PushDownStateMachine<Player> *machine)
			: PushDownState(name, machine), frameTimer(0) { }
		void enter(Player& p) override;
		void exit(Player& p) override;
		void update(double delta, Player& p) override;
	};

	class ClimbingState : public PushDownState<Player>
	{
	public:
		ClimbingState(std::string name, PushDownStateMachine<Player> *machine)
			: PushDownState(name, machine) { }
		void enter(Player& p) override;
		void exit(Player& p) override;
		void update(double delta, Player& p) override;
	};
}

#endif // PLAYER_STATES