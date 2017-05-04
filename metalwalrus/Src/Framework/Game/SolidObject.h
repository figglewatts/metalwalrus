#ifndef SOLIDOBJECT_H
#define SOLIDOBJECT_H
#pragma once

#include "GameObject.h"

#include "../Physics/AABB.h"

namespace metalwalrus
{
	class SolidObject : public GameObject
	{
	protected:	
		AABB boundingBox;
		Vector2 boundingBoxOffset;

		void recomputeBoundingBox();
	public:
		SolidObject(Vector2 position, float width, float height, Vector2 offset = Vector2(), std::string tag = "");
		SolidObject(const SolidObject& other);

		SolidObject& operator=(const SolidObject& other);

		virtual void start() override { };
		virtual void update(double delta) override { };
		virtual void draw(SpriteBatch& batch) override { };
		virtual void drawDebug() override;

		virtual void moveBy(Vector2 v) override;
		virtual void moveTo(Vector2 v) override;

		inline AABB get_boundingBox() const { return boundingBox; }
	};
}

#endif // SOLIDOBJECT_H