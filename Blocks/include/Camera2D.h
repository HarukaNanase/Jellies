#pragma once

#include "Vector2.h"

/*!
 * \class Camera2D
 *
 * \brief A 2D Camera responsible for the transformations between Window Space and the World Space. The Camera takes into account the Scale done automatically by SDL.
 *
 */
class Camera2D
{
	float ScaleX;
	float ScaleY;
	Vector2 Size;
	Vector2 Position;
	Vector2 Resolution;
	Vector2 WindowSize;
public:
	Camera2D();
	Camera2D(Vector2 Position, Vector2 Size);

	void SetResolution(int _x, int _y);
	void SetWindowSize(float _x, float _y);
	void SetScaleX(float _scaleX);
	void SetScaleY(float _scaleY);
	void SetCameraSize(int _sizeX, int _sizeY);
	void SetCameraPosition(float _x, float _y);

	const Vector2& GetResolution();
	const Vector2& GetWindowSize();
	const Vector2& GetSize();
	const Vector2& GetPosition();

	Vector2 ScreenToWorldRaycast(float _x, float _y);

	
	bool IsObjectInView(class TransformComponent& _objectPosition);
};

