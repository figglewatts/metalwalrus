#ifndef PUSHDOWNSTATEMACHINE_H
#define PUSHDOWNSTATEMACHINE_H
#pragma once

#include <vector>

#include "IState.h"

namespace metalwalrus
{
	template <typename StateObject>
	class PushDownStateMachine
	{
	protected:
		std::vector<IState<StateObject>*> currentState;
	public:
		void step(StateObject& o)
		{
			auto stateTuple = currentState.back()->changeState(o);
			IState<StateObject> *nextState = std::get<0>(stateTuple);

			// should we push the next state?
			bool push = std::get<1>(stateTuple);

			// if we're not replacing states (pushing)
			// or we need to pop a pushed state
			if ((!push && nextState != nullptr) || (push && nextState == nullptr))
			{
				// pop the current state
				currentState.back()->exit(o);
				delete currentState.back();
				currentState.pop_back();
			}

			if (nextState != nullptr)
			{
				currentState.push_back(nextState);
			}
			if (currentState.size() > 0 && (nextState != nullptr || push && nextState == nullptr))
				currentState.back()->enter(o);
		}

		void update(double delta, StateObject& o)
		{
			for (auto it = currentState.begin(); it < currentState.end(); it++)
				currentState.back()->update(delta, o);
		}
		void pushState(IState<StateObject> *state, StateObject& o)
		{
			currentState.push_back(state);
			currentState.back()->enter(o);
		}
		IState<StateObject> *popState(StateObject& o)
		{
			IState<StateObject> *state = currentState.back();
			state->exit(o);
			currentState.pop_back();
			return state;
		}
		IState<StateObject> *peekState(int index)
		{
			if (index < 0 || index >= currentState.size())
				throw runtime_error("Index outside range of currentState vector");

			return currentState.at(index);
		}
		IState<StateObject> *peekState()
		{
			return peekState(currentState.size() - 1);
		}
		IState<StateObject> *peekBelow()
		{
			return peekState(currentState.size() - 2);
		}
	};
}

#endif // PUSHDOWNSTATEMACHINE_H