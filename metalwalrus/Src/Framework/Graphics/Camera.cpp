#include "Camera.h"

#include "../Settings.h"

namespace metalwalrus
{
	void Camera::updateTransform()
	{
		transform = Matrix3::translation(-position);
	}

	Camera::Camera()
	{
		this->transform = Matrix3();
		this->position = Vector2();
	}

	Camera::Camera(Vector2 position)
	{
		this->transform = Matrix3();
	}

	Camera::Camera(const Camera & other)
	{
		this->transform = other.transform;
	}

	Camera & Camera::operator=(const Camera & other)
	{
		if (this != &other)
		{
			this->transform = other.transform;
		}
		return *this;
	}

	void Camera::translate(int x, int y)
	{
		this->position += Vector2(x, y);
		updateTransform();
	}

	void Camera::translate(Vector2 v)
	{
		this->position += v;
		updateTransform();
	}

	void Camera::moveTo(Vector2 v)
	{
		this->position = v;
		updateTransform();
	}

	void Camera::centerOn(Vector2 v)
	{
		moveTo(v - Vector2(Settings::VIRTUAL_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 2));
	}
}