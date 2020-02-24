#pragma once
#include "GameObject.h"
#include "Vector2.h"

/*!
 * \class The end of the game
 *
 * \brief A simple object with a collider that detects when a jelly enters it. Ends the game.
 *
 */
class EndPoint : public GameObject
{
private:

public:
	EndPoint(Vector2 _position);
	virtual void OnInitialize() override;

	void OnCollisionEnter(GameObject& obj);
};

