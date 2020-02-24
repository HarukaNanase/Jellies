#include "World.h"
#include "memory.h"
#include <iostream>
#include <AudioSystem.h>
#include <InputSystem.h>
#include <CollisionSystem.h>
#include <RenderSystem.h>
#include <BasicSystem.h>
#include <MovementSystem.h>
#include <MixerAudioSystem.h>
#include "Vector2.h"
#include "sdl.h"
World::World()
{
	auto position = Vector2(0, 0);
	auto size = Vector2(640, 360);
	Camera = Camera2D(position, size);
	LastTime = SDL_GetPerformanceCounter();
	Now = LastTime;
}

World::~World()
{

}

GameObject* World::CreateGameObject()
{
	auto object = std::make_unique<GameObject>(CurrentEntityId, this); 
	CurrentEntityId++;
	GameObjects.push_back(std::move(object));
	return GameObjects.back().get();
}




void World::SetTargetFPS(int _newTarget)
{
	this->TargetFPS = _newTarget;
}

FontManager& World::GetFontManager()
{
	return TheFontManager;
}


void World::RemoveDeadObjects() {
	
	GameObjects.erase(std::remove_if(GameObjects.begin(), GameObjects.end(), [](const std::unique_ptr<GameObject>& _obj) {
		return !_obj->IsAlive;
	}), GameObjects.end());
}


void World::ProcessObjects()
{
	for (int i = 0; i < GameObjects.size(); i++) {
		auto& object = GameObjects[i];
		object->Update();
	}
}

void World::Update(float _deltaTime)
{
	LastTime = Now;
	
	ProcessObjects();


	this->GetSystem<InputSystem>()->Update(this->DeltaTime);
	// using irrklang audio engine
	//this->GetSystem<AudioSystem>()->Update(this->DeltaTime);
	//using SDL_Mixer audio engine
	this->GetSystem<MixerAudioSystem>()->Update(this->DeltaTime);
	this->GetSystem<CollisionSystem>()->Update(this->DeltaTime);


	this->GetSystem<MovementSystem>()->Update(this->DeltaTime);
	this->GetSystem<RenderSystem>()->Update(this->DeltaTime);
	
	RemoveDeadObjects();


	Now = SDL_GetPerformanceCounter();
	this->DeltaTime = (double)((Now - LastTime) * 1000) / (double)SDL_GetPerformanceFrequency();


}

const std::vector<GameObject*> World::GetGameObjects(std::bitset<MAX_NUM_COMPONENTS> SystemMask)
{
	std::vector<GameObject*> viewForSystem;
	for (auto& object : GameObjects) {
		if (object->IsActive && (object->GetComponentMask() & SystemMask) == SystemMask) {
			viewForSystem.push_back(object.get());
		}
	}

	return viewForSystem;
}

Camera2D& World::GetCamera2D()
{
	return Camera;
}



float World::GetDeltaTime()
{
	return this->DeltaTime;
}






bool World::IsRunning()
{
	return Running;
}

void World::SetIsRunning(bool _running)
{
	Running = _running;
}

GameObject* World::GetGameObjectWithTag(std::string _tag)
{
	for (auto& object : GameObjects) {
		if (object->HasTag(_tag)) {
			return object.get();
		}
	}

	return nullptr;
}

