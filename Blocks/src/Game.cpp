#include "Game.h"
#include "MovementSystem.h"
#include "MovementComponent.h"
#include "MixerAudioSystem.h"
void Game::Init()
{
	this->TheEngine.InitEngine();
	this->GameWorld.AddSystem<RenderSystem>().RequiresComponent<SpriteComponent>();
	this->GameWorld.GetSystem<RenderSystem>()->OptionalComponent<TextComponent>();
	this->GameWorld.AddSystem<CollisionSystem>().RequiresComponent<CollisionComponent>();
	this->GameWorld.AddSystem<InputSystem>().RequiresComponent<InputComponent>();
	//using irrklang audio engine
	//this->GameWorld.AddSystem<AudioSystem>().RequiresComponent<SoundComponent>();
	//using SDL_mixer engine
	this->GameWorld.AddSystem<MixerAudioSystem>().RequiresComponent<SoundComponent>();
	this->GameWorld.AddSystem<MovementSystem>().RequiresComponent<MovementComponent>();
	this->GameWorld.GetSystem<MovementSystem>()->RequiresComponent<TransformComponent>();
	PreloadResources();
	SetupWorldSystems();
	SetupWorldObjects();

}

void Game::Run()
{
	Init();
	while (GameWorld.IsRunning()) {
		OnWorldUpdate();
		GameWorld.Update(GameWorld.GetDeltaTime());
	}
		
}
