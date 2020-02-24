#pragma once
#include "Vector2.h"
#include "Component.h"
#include <functional>

using namespace std::placeholders;

typedef std::function<void(class GameObject & _arg)> ObjectFunction;


/*!
 * CollisionComponent
 * @brief Enables an object to be tracked by the CollisionSystem. One can modify behavior by supplying a callback that will be executed on entering or leaving collisions.
		  These callbacks received the object that the owner of the component collided with.
*/
class CollisionComponent : public Component
{

private:

public:
	CollisionComponent(Vector2& _position, Vector2 _size, class GameObject& _owner, std::function<void(class GameObject & _arg)> enterFunc = nullptr,
		std::function<void(GameObject & _arg)> exitFunc = nullptr);

	/// function callback to be called when entering a collision
	std::function<void(class GameObject & _collidedWith)> OnCollisionEnter;
	/// function callback to be called when exiting a collision
	std::function<void(class GameObject & _collidedWith)> OnCollisionExit;

	Vector2 Position;
	int Width;
	int Height;
	float GetTop();
	float GetBottom();
	float GetLeft();
	float GetRight();
	void SetTop(int _top);
	void SetBottom(int _bottom);
	void SetLeft(int _left);
	void SetRight(int _right);
};