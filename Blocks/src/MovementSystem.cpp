#include "MovementSystem.h"
#include "World.h"
#include "MovementComponent.h"
#include "TransformComponent.h"
#include "sdl.h"
void MovementSystem::Initialize()
{
}

void MovementSystem::Update(float _deltaTime)
{
	auto& objects = GetWorld()->GetGameObjects(this->GetComponentMask());

	for (auto& object : objects) {
		//get movement component and transform
		auto movementComponent = object->GetComponent<MovementComponent>();
		auto& movements = movementComponent->Movements;
		auto transform = object->GetComponent<TransformComponent>();
		auto position = transform->GetPosition();
		Vector2 finalMovement;
		for (auto& movement : movements) {
			if (!movement.IsFinished) {
				movement.CurrentStep += _deltaTime/1000;
				auto step = std::clamp(movement.CurrentStep, 0.f, movement.Duration);
				auto newPosition = Vector2::Lerp(movement.Start, movement.Destination, step / movement.Duration);
				finalMovement += newPosition - position;

				if (movement.CurrentStep >= movement.Duration)
					movement.IsFinished = true;
			}
		}
		if (movements.size() > 0) {
			transform->GetPosition().x += finalMovement.x;
			transform->GetPosition().y += finalMovement.y;
		}
		

		

		movements.erase(std::remove_if(movements.begin(), movements.end(), [](const Movement& _movement) { return _movement.IsFinished; }), movements.end());
	
	}

}

void MovementSystem::Destroy()
{
}
