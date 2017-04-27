#ifndef ISTATE_H
#define ISTATE_H
#pragma once

#include <string>

#include "IStateMachine.h"

namespace metalwalrus
{
	template <typename T>
	class IState
	{
	protected:
		std::string name;
	public:
		IState(std::string name) : name(name) { }
		virtual ~IState() {}
		virtual void enter(T& o) = 0;
		virtual void exit(T& o) = 0;
		virtual void update(double delta, T& o) = 0;

		std::string get_name() const { return this->name; }
	};
}

#endif // ISTATE_H