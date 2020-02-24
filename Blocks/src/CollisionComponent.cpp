#include "CollisionComponent.h"
#include "GameObject.h"



CollisionComponent::CollisionComponent(Vector2& _position, Vector2 _size, GameObject& _owner, std::function<void(GameObject & _arg)> enterFunc, std::function<void(GameObject & _arg)> exitFunc)
: Position(_position), Width(_size.x), Height(_size.y) {
		if (enterFunc != nullptr) {
			OnCollisionEnter = enterFunc;
		}
		if (exitFunc != nullptr) {
			OnCollisionExit = exitFunc;
		}
}

float CollisionComponent::GetTop()
{
	return Position.y - Height/2;
}

float CollisionComponent::GetBottom()
{
	return Position.y + Height/2;
}

float CollisionComponent::GetLeft()
{
	return Position.x - Width/2;
}

float CollisionComponent::GetRight()
{
	return Position.x + Width/2;
}

void CollisionComponent::SetTop(int _top)
{
	this->Position.y = _top;
}

void CollisionComponent::SetBottom(int _bottom)
{
	this->Position.y = _bottom + Height;
}

void CollisionComponent::SetLeft(int _left)
{
	this->Position.x = _left;
}

void CollisionComponent::SetRight(int _right)
{
	this->Position.x = _right - Width;
}
