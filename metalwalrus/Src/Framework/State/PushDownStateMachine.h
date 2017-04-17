#ifndef PUSHDOWNSTATEMACHINE_H
#define PUSHDOWNSTATEMACHINE_H
#pragma once

#include <stack>

#include "IState.h"

namespace metalwalrus
{
	template <typename StateObject>
	class PushDownStateMachine
	{
	protected:
		std::stack<IState<StateObject>*> currentState;
	public:
		void step(StateObject& o)
		{
			auto stateTuple = currentState.top()->changeState(o);
			IState<StateObject> *nextState = std::get<0>(stateTuple);
			bool push = std::get<1>(stateTuple);
			if (nextState != nullptr) // if we have a next state
			{
				if (!push) // replace the old state
				{
					delete currentState.top();
					currentState.pop();
				}

				// if we're not trying to change to the new current state
				// then change to the next state
				if (currentState.top() != nextState)
					currentState.push(nextState);
			}
		}

		void update(double delta, StateObject& o)
		{
			currentState.top()->update(o);
		}
		void pushState(IState<StateObject*> state)
		{
			currentState.push(state);
		}
		IState<StateObject> *popState()
		{
			IState<StateObject> *state = currentState.top();
			currentState.pop();
			return state;
		}
		IState<StateObject> *peekState()
		{
			return currentState.top();
		}
	};
}

#endif // PUSHDOWNSTATEMACHINE_H