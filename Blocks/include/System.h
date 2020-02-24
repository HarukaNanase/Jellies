#pragma once
#include "BasicSystem.h"


class System : public BasicSystem {

private:
	SystemID Id;
public:

	System() {}
	System(World* _world) {
		SetWorld(_world);
	}

	virtual void OnObjectAdded(GameObject& _object) override;

	virtual void OnObjectRemoved(GameObject& _object) override;

	virtual void OnUpdate(GameObject& _object) override;

	virtual void OnInitialize() override;

};
