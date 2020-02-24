#pragma once

#include "IDManager.h"


typedef Id ComponentID;



class Component
{
	bool Enabled = true;
public:
	virtual ~Component();

	bool IsEnabled();
	void SetIsEnabled(bool _enabled);
};



template<class T>
ComponentID ComponentId() {
	return IDManager<Component>::GetId<T>();
}

