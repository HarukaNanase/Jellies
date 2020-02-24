#pragma once
#include "Vector2.h"
#include "Component.h"
#include "SDL.h"

/*!
 * \class TransformComponent
 *
 * \brief  Enables a game object to be positioned in the world. Contains position and size of object.
 */
class TransformComponent : public Component
{
	SDL_FRect Rect;
	Vector2 Position;
	Vector2 Size;

public:
	TransformComponent(float x = 0, float y = 0);
	TransformComponent(float x, float y, float w, float h);
    Vector2& GetPosition();
	Vector2& GetSize();
	void SetPosition(Vector2 _newPosition);
	void SetPosition(float _x, float _y);
	void SetSize(Vector2 _newSize);
	void SetSize(float _x, float _y);
	SDL_FRect GetTransform();
	void SetTransform(Vector2 _position);
};

