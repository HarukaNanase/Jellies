#include "PlayButton.h"
#include "Components.h"
#include "Grid.h"
#include "World.h"
#include "HUD.h"
PlayButton::PlayButton(Texture* _tex, Vector2 _position, HUD* _hud)
{
	this->hud = _hud;
	AddComponent<InputComponent>();
	AddComponent<SpriteComponent>(_tex, 1);
	AddComponent<TransformComponent>(_position.x, _position.y, 90, 45);
	this->AddTag("playbutton");
}

void PlayButton::OnInitialize()
{
	this->GetComponent<InputComponent>()->AddBinding("MOUSE_LEFT", std::bind(&PlayButton::OnClick, this));
}

void PlayButton::OnClick()
{
	this->hud->OnPlayButtonClicked();
}


