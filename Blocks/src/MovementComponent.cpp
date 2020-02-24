#include "MovementComponent.h"
#include "sdl.h"
void MovementComponent::MoveTo(Vector2 _start, Vector2 _dest, float _duration)
{
	Movement _movement(_start, _dest, _duration);
	_movement.TimeStarted = SDL_GetTicks();
	if(Movements.size() > 0)
		this->Movements.pop_back();
	this->Movements.push_back(Movement(_start, _dest, _duration));
}

