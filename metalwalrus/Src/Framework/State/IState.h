#ifndef ISTATE_H
#define ISTATE_H
#pragma once

#include <tuple>

namespace metalwalrus
{
	template <typename StateObject>
	class IState
	{
	public:
		virtual ~IState() {}
		virtual void enter(StateObject& o) = 0;
		virtual void exit(StateObject& o) = 0;
		virtual std::tuple<IState<StateObject>*, bool> changeState(StateObject& o) = 0;
		virtual void update(double delta, StateObject& o) = 0;
	};
}

#endif // ISTATE_H