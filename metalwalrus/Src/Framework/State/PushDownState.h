#ifndef PUSHDOWNSTATE_H
#define PUSHDOWNSTATE_H
#pragma once

#include "IState.h"
#include "PushDownStateMachine.h"

namespace metalwalrus
{
	template <typename T> class PushDownStateMachine;
	
	template <typename T>
	class PushDownState : public IState<T>
	{
	protected:
		PushDownStateMachine<T> *machine;
	public:
		PushDownState(std::string name, PushDownStateMachine<T> *machine) : IState(name), machine(machine) { }
		virtual ~PushDownState() {}
		virtual void enter(T& o) override = 0;
		virtual void exit(T& o) override = 0;
		virtual void update(double delta, T& o) override = 0;
	};
}

#endif // PUSHDOWNSTATE_H