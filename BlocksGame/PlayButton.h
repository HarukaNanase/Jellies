#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "Vector2.h"

/*!
 * \class PlayButton
 *
 * \brief Represents the play button. Calls back to a HUD function.
 *
 */
class PlayButton : public GameObject
{
private:
	class HUD* hud;
public:
	PlayButton(Texture* _tex, Vector2 _position, class HUD* _hud);
	bool IsClicked = false;
	void OnInitialize() override;
	void OnClick();

};

