#pragma once
#include <vector>
#include "GameObject.h"
#include "IDManager.h"
#include <bitset>
#include "Component.h"
typedef Id SystemID;

/*!
 * \class BasicSystem
 *
 * \brief  The skeleton of a system.
 */
class BasicSystem 
{
	
	virtual void OnObjectAdded(GameObject& _object) = 0;
	virtual void OnObjectRemoved(GameObject& _object) = 0;
	virtual void OnUpdate(GameObject& _object) = 0;
	virtual void OnInitialize() = 0;
	
	void SetWorld(class World& world);
	class World* TheWorld;
	std::vector<GameObject*> GameObjects;
	std::bitset<MAX_NUM_COMPONENTS> RequiredComponents;
	std::bitset<MAX_NUM_COMPONENTS> OptionalComponents;
	
public:
	BasicSystem() {};
	BasicSystem(World* _world);
	virtual ~BasicSystem();
	virtual void Initialize();
	virtual void Destroy();
	class World* GetWorld();
	void SetWorld(World* _world);
	virtual void Update(float _deltaTime);


	//************************************
	// @brief Sets the bit for T to true
	// 
	// @return:   void
	//************************************
	template<typename T>
	void RequiresComponent() {
		static_assert (std::is_base_of<Component, T>().value, "T must be a derived class of Component.");
		this->RequiredComponents.set(ComponentId<T>());

	}
	
	//************************************
	// @brief Sets the optional bit for T to true
	// 
	// @return:   void
	//************************************
	template<typename T>
	void OptionalComponent() {
		static_assert (std::is_base_of<Component, T>().value, "T must be a derived class of Component.");
		this->OptionalComponents.set(ComponentId<T>());
		
	}


	template<typename T>
	bool UsesComponent() {
		return this->RequiredComponents[ComponentId<T>()];
	}

	//************************************
	// @brief Returns the component mask for this system.
	// 
	// @return:   std::bitset<MAX_NUM_COMPONENTS>
	//************************************
	std::bitset<MAX_NUM_COMPONENTS> GetComponentMask();

	//************************************
	// @brief Returns the optional component mask for this system.
	// 
	// @return:   std::bitset<MAX_NUM_COMPONENTS>
	std::bitset<MAX_NUM_COMPONENTS> GetOptionalMask();

};
template<typename T>
SystemID SystemId() {
	return IDManager<BasicSystem>::GetId<T>();
};