#include "EndPoint.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "World.h"
#include "HUD.h"
#include <iostream>
EndPoint::EndPoint(Vector2 _position)
{
	AddComponent<TransformComponent>(_position.x, _position.y, 32, 32);
	
}

void EndPoint::OnInitialize()
{
	auto transform = GetComponent<TransformComponent>();
	AddComponent<CollisionComponent>(transform->GetPosition(), transform->GetSize(), *this);
	GetComponent<CollisionComponent>()->OnCollisionEnter = std::bind(&EndPoint::OnCollisionEnter, this, _1);;
}

void EndPoint::OnCollisionEnter(GameObject& obj)
{
	if (obj.HasTag("grid")) {
		std::cout << "GG you lose" << std::endl;
		obj.IsActive = false;
	}

	auto hud = static_cast<HUD*>(GetWorld()->GetGameObjectWithTag("HUD"));
	if(hud != nullptr)
		hud->ShowEndMenu();

}

