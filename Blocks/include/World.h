#pragma once
#include <vector>
#include "GameObject.h"
#include <algorithm>
#include <memory>
#include <unordered_map>
#include "IDManager.h"
#include "System.h"
#include "Camera2D.h"
#include "FontManager.h"


/*!
 * \class World
 *
 * \brief The World is where every system and every gameobject lives. The world is the sole creator and destroyer of gameobjects, ensuring strong ownership of each object.
 *	      It is possible to add derived gameobjects that implement behavior. When this happens, the world creates a copy of the object and returns a raw pointer.
 */
class World
{
	typedef IDManager<System> SystemIDManager;

private:


	Camera2D Camera;

	bool Running = true;
	std::vector <std::unique_ptr<GameObject>> GameObjects;
	unsigned int CurrentEntityId;
	std::unordered_map <SystemID, std::unique_ptr<System>> Systems;
	float DeltaTime = 0.0;
	Uint64 LastTime = 0.0, Now = 0.0;
	FontManager TheFontManager;
	void RemoveDeadObjects();
	void ProcessObjects();
	int TargetFPS = 60;
public:
	World();
	~World();
	GameObject* CreateGameObject();

	template<typename TObject>
	TObject* AddGameObject(TObject& _object);


	void SetTargetFPS(int _newTarget);

	FontManager& GetFontManager();


	virtual void Update(float _deltaTime);
	
	/// Returns a view for a given system mask. The gameobjects contained within are guaranteed to be alive for the scope of the function that called this method.
	const std::vector<GameObject*> GetGameObjects(std::bitset<MAX_NUM_COMPONENTS> SystemMask);

	template<class TSys>
	TSys& AddSystem();
	float GetDeltaTime();
	template<class TSys>
	TSys* GetSystem();
	Camera2D& GetCamera2D();
	
	bool IsRunning();
	void SetIsRunning(bool _running);
	
	GameObject* GetGameObjectWithTag(std::string _tag);
	
};



template<typename TObject>
TObject* World::AddGameObject(TObject& _object)
{
	static_assert(std::is_base_of<GameObject, TObject>().value, "TObject must derive from GameObject");
	auto object = std::make_unique<TObject>(_object);
	object->SetObjectId(CurrentEntityId++);
	object->SetWorld(this);
	object->OnInitialize();
	GameObjects.push_back(std::move(object));
	return static_cast<TObject*>(GameObjects.back().get());

}
	

template<class TSys>
inline TSys& World::AddSystem()
{
	static_assert(std::is_base_of<System, TSys>().value, "TSys must be a derived class of Basic System.");
	auto newSystem = std::make_unique<TSys>();
	newSystem->SetWorld(this);
	newSystem->Initialize();
	this->Systems.emplace(SystemId<TSys>(), std::move(newSystem));
	return static_cast<TSys&>(*this->Systems[SystemId<TSys>()]);
}

template<class TSys>
inline TSys* World::GetSystem() {
	static_assert(std::is_base_of<System, TSys>().value, "TSys must be a derived class of Basic System.");
	if (this->Systems.find(SystemId<TSys>()) != Systems.end())
		return static_cast<TSys*>(this->Systems[SystemId<TSys>()].get());

	return nullptr;

}