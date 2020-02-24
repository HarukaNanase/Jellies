#pragma once

#include "Game.h"


/*!
 * \class JelliesGame
 *
 * \brief The Game class. Preloads resources, sets the world systems and objects up. Can also run logic during world update.
 *
 */

class JelliesGame : public Game
{
public:
	float TimeElapsed = 0;

	virtual void SetupWorldSystems() override;

	virtual void SetupWorldObjects() override;

	virtual void OnWorldUpdate() override;


	virtual void PreloadResources() override;
	void MainMenu();
	void PlayGame();
	void PauseGame();
	void ResumeGame();
	void HandlePauseKey(World* _world, const SDL_Event& _event);
	bool IsPaused = false;

};

