#pragma once
#include "System.h"
#include "CollisionComponent.h"
#include <map>
typedef unsigned int GameObjectID;
/*!
 * \class CollisionSystem
 *
 * \brief The system responsible for collision checking between game objects. When a collision is detected, the callbacks for each object are called
 *        with the corresponding colliding object.
 *
 */
class CollisionSystem : public System
{

	std::vector<std::pair<GameObjectID, GameObjectID>> Colliding;
	bool CheckCollision(CollisionComponent& _collider1, CollisionComponent& _collider2);

public:

	CollisionSystem();
	~CollisionSystem();
	virtual void Initialize() override;

	virtual void Update(float _deltaTime) override;

	virtual void Destroy() override;

};

