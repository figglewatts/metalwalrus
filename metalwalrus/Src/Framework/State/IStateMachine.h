#ifndef ISTATEMACHINE_H
#define ISTATEMACHINE_H
#pragma once

#include <vector>

#include "IState.h"

namespace metalwalrus
{
	template <typename T> class IState;
	
	template <typename T>
	class IStateMachine
	{
	public:
		virtual ~IStateMachine() { }
		virtual void transition(IState<T> *state, T& stateObject) = 0;
		virtual void update(double delta, T& stateObject) = 0;
	};
}

#endif // ISTATEMACHINE_H