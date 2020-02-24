#pragma once
#include "Component.h"

#include "SpriteComponent.h"
#include "SoundComponent.h"
#include <unordered_map>
#include <bitset>
#include <assert.h>
#define MAX_NUM_COMPONENTS 8

/*!
 * \class GameObject
 *
 * \brief The core entity of the engine. A game object can be almost anything. It can be a GUI Button, a background, a logical entity that spawns other entities.
 *		  Behavior can be added through polymorphism and composition of components.
 */
class GameObject
{
	unsigned int ObjectId;
	class World* TheWorld;	
	bool IsRegistered = false;

	void Initialize();
	std::unordered_map<ComponentID, std::shared_ptr<Component>> ObjectComponents;
	std::bitset<MAX_NUM_COMPONENTS> ExistingComponents;
	std::vector<std::string> Tags;
public:
	~GameObject();

	GameObject();
	GameObject(const GameObject& _other);
	GameObject(unsigned int _id);
	GameObject(unsigned int _id, World* _world);


	void Update();
	virtual void OnUpdate();
	virtual void OnInitialize();
	virtual void OnDestroy();


	unsigned int GetObjectId();
	void SetObjectId(unsigned int _id);


	class World* GetWorld();
	void SetWorld(World* _world);


	void Destroy();
	void Disable();

	void AddTag(const std::string& _tag);
	void RemoveTag(const std::string& _tag);
	bool HasTag(const std::string& _tag);



	std::bitset<MAX_NUM_COMPONENTS> GetComponentMask();


	template<typename T, typename... Args>
	T* AddComponent(Args&&... args);

	template<typename T>
	void RemoveComponent();

	template<typename T>
	T* GetComponent();

	template<typename T>
	bool HasComponent();

	bool IsActive = true;
	bool IsAlive = true;
	
};

template<typename T, typename ...Args>
inline T* GameObject::AddComponent(Args&& ...args)
{
	static_assert(std::is_base_of<Component, T>().value, "T must be a derived class of Component.");
	auto component = std::make_shared<T>(std::forward<Args>(args)...);
	this->ObjectComponents.emplace(ComponentId<T>() , std::move(component));
	this->ExistingComponents[ComponentId<T>()] = true;
	return static_cast<T*>(ObjectComponents[ComponentId<T>()].get());

	
}

template<typename T>
inline void GameObject::RemoveComponent()
{
	if (HasComponent<T>()) {
		ObjectComponents.erase(ComponentId<T>());
		ExistingComponents[ComponentId<T>()] = false;
	}
	
}

template<typename T>
inline T* GameObject::GetComponent()
{
	static_assert(std::is_base_of<Component, T>().value, "T must be a subtype of Component");
	if (this->HasComponent<T>())
		return static_cast<T*>((ObjectComponents[ComponentId<T>()].get()));
	else
		return nullptr;
}

template<typename T>
inline bool GameObject::HasComponent()
{
	return ExistingComponents[ComponentId<T>()];

}
