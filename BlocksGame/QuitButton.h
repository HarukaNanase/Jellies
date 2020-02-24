#pragma once
#include "GameObject.h"
#include "Vector2.h"

/*!
 * \class QuitButton
 *
 * \brief Represents the quit button. Calls back to a HUD function.
 *
 */
class QuitButton :	public GameObject
{

private:
	class HUD* hud;
public:

	QuitButton(Texture* _tex, Vector2 _position, class HUD* hud);

	virtual void OnInitialize() override;

	void OnClick();
};

