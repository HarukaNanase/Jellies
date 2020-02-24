#include "Camera2D.h"
#include "Vector2.h"
#include <iostream>
#include "TransformComponent.h"
#define DEBUG_MOUSE


Camera2D::Camera2D()
{
}
Camera2D::Camera2D(Vector2 _position, Vector2 _size)
{
	this->Position = _position;
	this->Size = _size;
	this->Resolution = _size;
	this->WindowSize = _size;
	this->ScaleX = Resolution.x / Size.x;
	this->ScaleY = Resolution.y / Size.y;
}
void Camera2D::SetScaleX(float _scaleX)
{
	this->ScaleX = _scaleX;
}
void Camera2D::SetScaleY(float _scaleY)
{
	this->ScaleY = _scaleY;
}
void Camera2D::SetCameraSize(int _x, int _y)
{
	this->Size.x = _x;
	this->Size.y = _y;
}



void Camera2D::SetCameraPosition(float _x, float _y)
{
	this->Position.x = _x;
	this->Position.y = _y;
}


const Vector2& Camera2D::GetResolution()
{
	return Resolution;
}

const Vector2& Camera2D::GetWindowSize()
{
	return this->WindowSize;
}

const Vector2& Camera2D::GetSize()
{
	return this->Size;
}

const Vector2& Camera2D::GetPosition()
{
	return this->Position;
}

void Camera2D::SetWindowSize(float _x, float _y)
{
	this->WindowSize = Vector2(_x, _y);
}

Vector2 Camera2D::ScreenToWorldRaycast(float _x, float _y)
{
	// convert _x from window coordinates to external resolution coordinates
	//calculate x and y difference between window size and external resolution

	float xDif = (WindowSize.x - Resolution.x);
	float yDif = (WindowSize.y - Resolution.y);
	float x = _x - (xDif / 2);
	float y = _y - (yDif / 2);
	// now take x and y to world coordinates

	x /= ScaleX;
	y /= ScaleY;

	//move x/y in relation to camera and world size

	x = x - (Size.x / 2) - Position.x;
	y = y - (Size.y / 2) - Position.y;

#ifdef DEBUG_MOUSE
	std::cout << "Mouse input in world coordinates: x:" << x << " y:" << -y << std::endl;
#endif
	return Vector2(x, -y);
}


void Camera2D::SetResolution(int _x, int _y)
{
	this->Resolution = Vector2{ _x, _y };
}

bool Camera2D::IsObjectInView(TransformComponent& _objectTransform)
{
	auto objectPosition = _objectTransform.GetPosition();
	auto objectSize = _objectTransform.GetSize();

	if ((objectPosition.x + objectSize.x / 2 > (-this->Size.x / 2))
		
		
		) {
		;
	}
	return true;

}

