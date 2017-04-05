#ifndef IRIGIDBODY_H
#define IRIGIDBODY_H
#pragma once

#include "../Math/Vector2.h"
#include "AABB.h"

namespace metalwalrus
{
	class IRigidbody
	{
		IRigidbody();
	protected:	
		bool usePhysics;
		AABB boundingBox;
		Vector2 velocity;
		Vector2 position;
	public:
		IRigidbody(Vector2 position, AABB boundingBox, bool usePhysics) 
			: position(position)
			, boundingBox(boundingBox)
			, usePhysics(usePhysics) { }
		IRigidbody(const IRigidbody& other)
			: position(position)
			, boundingBox(other.boundingBox)
			, usePhysics(other.usePhysics)
			, velocity(other.velocity) { }
		virtual ~IRigidbody() { }

		IRigidbody& operator=(const IRigidbody& other)
		{
			if (this != &other)
			{
				this->boundingBox = other.boundingBox;
				this->usePhysics = other.usePhysics;
				this->velocity = other.velocity;
				this->position = other.position;
			}
			return *this;
		}

		virtual void integrate(double delta) final
		{
			if (!usePhysics) return;
			this->updatePosition(velocity * delta);
		}

		inline bool get_usePhysics() { return usePhysics; }
		inline void set_usePhysics(bool b) { usePhysics = b; }
		inline AABB get_boundingBox() { return boundingBox; }
		inline Vector2 get_velocity() { return velocity; }
		inline void set_velocity(Vector2 v) { velocity = v; }
		inline void set_position(Vector2 pos) { position = pos; }

		void updatePosition(Vector2 diff)
		{
			position += diff;
			boundingBox += diff;
		}
	};
}

#endif // IRIGIDBODY_H