#include "QuitButton.h"
#include "Components.h"
#include "World.h"
#include "HUD.h"
QuitButton::QuitButton(Texture* _tex, Vector2 _position, HUD* _hud)
{
	this->hud = _hud;
	this->AddComponent<TransformComponent>(_position.x, _position.y, 90, 45);
	this->AddComponent<SpriteComponent>(_tex, 1);
	this->AddComponent<InputComponent>();
	this->AddTag("quitbutton");
}

void QuitButton::OnInitialize()
{
	this->GetComponent<InputComponent>()->AddBinding("MOUSE_LEFT", std::bind(&QuitButton::OnClick, this));
}

void QuitButton::OnClick()
{
	this->hud->OnQuitButtonClicked();
}
