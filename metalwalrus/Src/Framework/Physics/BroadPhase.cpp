#include "BroadPhase.h"

namespace metalwalrus
{
	BroadPhase::BroadPhase(std::vector<IRigidbody>& bodies)
		: bodies(bodies) { }

	void BroadPhase::update(double delta)
	{
		for (int i = 0; i < bodies.size(); i++)
		{
			bodies[i].integrate(delta);
		}
	}

	void BroadPhase::generatePairs()
	{
		pairs.clear();

		for (int i = 0; i < bodies.size(); i++)
		{
			for (int j = 0; j < bodies.size(); j++)
			{
				if (i == j) continue; // skip self check

				if (bodies[i].get_boundingBox().intersects(bodies[j].get_boundingBox()))
				{
					pairs.push_back({ &bodies[i], &bodies[j] });
				}
			}
		}
	}

	void BroadPhase::resolveCollisions()
	{
		// resolve for X
		for (Pair p : pairs)
		{
			float depth = p.a->get_boundingBox().getXDepth(p.b->get_boundingBox());
			p.a->updatePosition(Vector2(-depth, 0));
		}

		// resolve for Y
		for (Pair p : pairs)
		{
			float depth = p.a->get_boundingBox().getYDepth(p.b->get_boundingBox());
			p.a->updatePosition(Vector2(0, -depth));
		}
	}
}