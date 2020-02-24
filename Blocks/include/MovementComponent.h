#pragma once

#include <vector>
#include "Component.h"
#include "Vector2.h"

struct Movement {
	Vector2 Start;
	Vector2 Destination;
	float CurrentStep = 0.0f;
	float Duration;
	unsigned int TimeStarted;
	bool IsFinished = false;

	Movement(Vector2 _start, Vector2 _dest, float _duration) : Start(_start), Destination(_dest), Duration(_duration) {};
};


/*!
 * \class MovementComponent
 *
 * \brief  Enables a game object to be tracked and processed by the MovementSystem, allowing for the lerping of movements.
 */
class MovementComponent : public Component
{


private:


public:
	std::vector<Movement> Movements;

	void MoveTo(Vector2 _start, Vector2 _dest, float _duration);


};

