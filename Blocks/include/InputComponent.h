#pragma once

#include "Component.h"
#include <functional>


/*!
 * CollisionComponent
 * @brief Enables an object to be tracked by the InputSystem. Callbacks are supplied and are executed when the specified binding is pressed.
*/
class InputComponent : public Component
{

private:
	std::unordered_map<int16_t, std::function<void()>> bindings;

public:
	void AddBinding(const std::string& _input, std::function<void()> _callback);
	const std::unordered_map < int16_t, std::function<void()>>& GetBindings();
};

