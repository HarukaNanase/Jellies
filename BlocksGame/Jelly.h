#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "Vector2.h"
class Jelly : public GameObject
{
public:
	Jelly() {};
	~Jelly();
	Vector2 GridPosition;
	bool IsMoving = false;
	class Grid* OwningGrid;
	Color color = { 0xFF, 0xFF, 0xFF, 0xFF };
	Uint8 Type;
	Jelly(Texture* _tex, const Vector2& _position, Uint8 type, Grid* _grid);
	void OnClick();
	void OnInitialize() override;
};

