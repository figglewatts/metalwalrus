#ifndef PUSHDOWNSTATEMACHINE_H
#define PUSHDOWNSTATEMACHINE_H
#pragma once

#include <vector>

#include "IState.h"
#include "PushDownState.h"
#include "IStateMachine.h"

namespace metalwalrus
{
	template <typename StateObject>
	class PushDownStateMachine : public IStateMachine<StateObject>
	{
	protected:
		std::vector<IState<StateObject>*> currentState;
	public:
		void update(double delta, StateObject& o) override
		{
			this->currentState.back()->update(delta, o);
		}
		void push(IState<StateObject> *state, StateObject& o)
		{
			this->currentState.push_back(state);
			this->currentState.back()->enter(o);
		}
		void transition(IState<StateObject> *state, StateObject& o) override
		{
			this->pop(o);
			this->push(state, o);
		}
		void pop(StateObject& o)
		{
			if (this->currentState.size() <= 0) return;

			this->currentState.back()->exit(o);
			delete currentState.back();
			this->currentState.pop_back();
		}
		IState<StateObject> *peek(int index)
		{
			if (index < 0 || index >= this->currentState.size())
				throw runtime_error("Index outside range of states");

			return this->currentState.at(index);
		}
		IState<StateObject> *peek()
		{
			return this->peek(this->currentState.size() - 1);
		}
		IState<StateObject> *peekBelow()
		{
			return this->peek(this->currentState.size() - 2);
		}
	};
}

#endif // PUSHDOWNSTATEMACHINE_H