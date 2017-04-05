#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include "../Math/Matrix3.h"

namespace metalwalrus
{
	class Camera
	{
		Matrix3 transform;
		Vector2 position;

		void updateTransform();
	public:
		Camera();
		Camera(Vector2 position);
		Camera(const Camera& other);

		Camera& operator=(const Camera& other);

		void translate(int x, int y);
		void translate(Vector2 v);
		void moveTo(Vector2 v);
		void centerOn(Vector2 v);
		
		inline Matrix3 getTransform() { return transform; }
		inline Vector2 getPosition() { return position; }
	};
}

#endif // CAMERA_H