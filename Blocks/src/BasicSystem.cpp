#include "BasicSystem.h"
#include "World.h"




void BasicSystem::SetWorld(World& _world)
{
	this->TheWorld = &_world;
}



BasicSystem::BasicSystem(World* _world)
{
	SetWorld(_world);
}

BasicSystem::~BasicSystem()
{
	Destroy();
}

void BasicSystem::Initialize()
{
	OnInitialize();
}

void BasicSystem::Destroy()
{
	
	this->TheWorld = nullptr;
}

World* BasicSystem::GetWorld()
{
	return TheWorld;
}

void BasicSystem::SetWorld(World* _world)
{
	this->TheWorld = _world;
}



void BasicSystem::Update(float _deltaTime)
{
	for (auto& object : this->GameObjects) {
		OnUpdate(*object);
	}
}

std::bitset<MAX_NUM_COMPONENTS> BasicSystem::GetComponentMask()
{
	return RequiredComponents;
}

std::bitset<MAX_NUM_COMPONENTS> BasicSystem::GetOptionalMask()
{
	return OptionalComponents;
}

