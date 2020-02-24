#include "Jelly.h"
#include "InputComponent.h"
#include "SpriteComponent.h"
#include "SoundComponent.h"	
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "MovementComponent.h"
#include "World.h"
#include <functional>
#include <iostream>
#include "Grid.h"



Jelly::Jelly(Texture* _tex, const Vector2& _position, Uint8 _type, Grid* _grid)
{

	this->Type = _type;
	this->OwningGrid = _grid;
	AddComponent<InputComponent>();
	AddComponent<SpriteComponent>(_tex, this->color);
	AddComponent<MovementComponent>();
	AddComponent<TransformComponent>(_position.x, _position.y, 32, 32);
	this->AddTag("cube");
}

void Jelly::OnClick()
{
	std::cout << "Clicked on Cube(" << this->GridPosition.x << "," << this->GridPosition.y << ")." << std::endl;
	this->OwningGrid->OnCubeClicked(this->GridPosition.x, this->GridPosition.y, this->Type);
}

Jelly::~Jelly()
{
	this->OwningGrid = nullptr;
}

void Jelly::OnInitialize()
{
	this->GetComponent<InputComponent>()->AddBinding("MOUSE_LEFT", std::bind(&Jelly::OnClick, this));

}

