#include "Engine.h"
#include "SDL_image.h"
#include <iostream>
#include "SDL_ttf.h"


bool Engine::InitEngine()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() == -1) {
		std::cout << "Engine Init Error: Error starting SDL_ttf. " << std::endl;
	}

	return true;

}

void Engine::Cleanup()
{
	//other cleanup code
	std::cout << "SDL_TTF Quitting" << std::endl;
	TTF_Quit();

	std::cout << "SDL Quitting" << std::endl;
	SDL_Quit();

}

Engine::Engine()
{
	if(!InitEngine()){
		Cleanup();
		std::cout << "Error initializing engine. Press any key to continue." << std::endl;
		exit(EXIT_FAILURE);
	}

}


Engine::~Engine()
{
}




void Engine::SetIsRunning(bool _state)
{
	ShouldRun = _state;
}


bool Engine::IsRunning()
{
	return ShouldRun;
}

