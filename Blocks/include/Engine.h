#pragma once


#include "SDL.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "RenderSystem.h"
#include "AudioSystem.h"
#include "CollisionSystem.h"
#include "SpriteComponent.h"
#include "InputSystem.h"

/*!
 * \class Engine
 *
 * \brief Responsible for the initialization of SDL and final destruction of the SDL environment.
 *
 */
class Engine
{
private:

	
	bool ShouldRun = true;

public:
	bool InitEngine();
	void Cleanup();
	Engine();
	~Engine();
	void SetIsRunning(bool _state);
	bool IsRunning();

protected:

	





};

