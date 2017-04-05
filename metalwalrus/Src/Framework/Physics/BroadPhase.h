#ifndef BROADPHASE_H
#define BROADPHASE_H
#pragma once

#include <vector>

#include "IRigidbody.h"

namespace metalwalrus
{
	struct Pair
	{
		IRigidbody *a;
		IRigidbody *b;
	};
	
	class BroadPhase
	{
		std::vector<Pair> pairs;
		std::vector<IRigidbody> &bodies;
	public:
		BroadPhase(std::vector<IRigidbody> &bodies);
		
		void update(double delta);
		void generatePairs();
		void resolveCollisions();
	};
}

#endif // BROADPHASE_H