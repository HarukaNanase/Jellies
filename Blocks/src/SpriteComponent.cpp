#include "SpriteComponent.h"
#include "RenderSystem.h"
#include "GameObject.h"


SpriteComponent::SpriteComponent(Texture* _tex, Color _color, float _zIndex) : Tex(_tex)
{

	this->SpriteColor = _color;
	this->ZIndex = _zIndex;
}

SpriteComponent::SpriteComponent(Texture* _tex, float _zIndex) : Tex(_tex)
{
	this->SpriteColor = Color{ 0xFF, 0xFF, 0xFF, 0xFF };
	this->ZIndex = _zIndex;
}

const Color& SpriteComponent::GetColor()
{
	// TODO: insert return statement here
	return this->SpriteColor;
}


Texture* SpriteComponent::GetTexture()
{
	return this->Tex;
}


void SpriteComponent::SetZIndex(float _zIndex)
{
	this->ZIndex = _zIndex;
}



float SpriteComponent::GetZIndex()
{
	return this->ZIndex;
}

void SpriteComponent::SetTexture(Texture* _tex)
{
	Tex = _tex;
}

void SpriteComponent::SetColor(Color _color)
{
	SpriteColor = _color;
}

