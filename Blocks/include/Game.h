#pragma once
#include "World.h"
#include "Engine.h"
/*!
 * \class Game
 *
 * \brief The game base class.
 *
 */
class Game
{

private:
	
public:
	World GameWorld;
	Engine TheEngine;
	bool IsRunning = true;
	void Init();
	virtual void SetupWorldSystems() = 0;

	virtual void PreloadResources() = 0;
	virtual void SetupWorldObjects() = 0;

	virtual void OnWorldUpdate() = 0;

	void Run();


};

