#include "TransformComponent.h"

TransformComponent::TransformComponent(float x, float y) : Position(x,y), Rect{x,y,0,0}
{

}

TransformComponent::TransformComponent(float x, float y, float w, float h) : Rect{x,y,w,h}, Position(x,y), Size(w, h)
{
	
}

Vector2& TransformComponent::GetPosition()
{
	return this->Position;
}

Vector2& TransformComponent::GetSize()
{
	return Size;
}

void TransformComponent::SetPosition(Vector2 _newPosition)
{
	this->Position = _newPosition;
}

void TransformComponent::SetPosition(float _x, float _y)
{
	this->Position.x = _x;
	this->Position.y = _y;
}

void TransformComponent::SetSize(Vector2 _newSize)
{
	this->Size = _newSize;
}

void TransformComponent::SetSize(float _x, float _y)
{
	this->Size.x = _x;
	this->Size.y = _y;
}

SDL_FRect TransformComponent::GetTransform()
{
	return { Position.x, Position.y, Size.x, Size.y };
}

void TransformComponent::SetTransform(Vector2 _position)
{
	Position = _position;
}
