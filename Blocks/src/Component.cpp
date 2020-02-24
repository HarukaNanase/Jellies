#include "Component.h"

Component::~Component()
{
}



bool Component::IsEnabled()
{
	return Enabled;
}

void Component::SetIsEnabled(bool _enabled)
{
	this->Enabled = _enabled;
}
