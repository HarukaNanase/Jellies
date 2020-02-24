#include "InputComponent.h"
#include "GameObject.h"
#include "SDL.h"
//
//void InputComponent::AddBinding(int16_t _key, std::function<void()> _callback)
//{
//	bindings.push_back(InputEventBinding{_callback, _key });
//}

void InputComponent::AddBinding(const std::string& _input, std::function<void()> _callback)
{
	int16_t key;
	if (_input == "MOUSE_LEFT" ) {
		key = SDL_BUTTON_LEFT;
	}
	else if (_input == "MOUSE_RIGHT") {
		key = SDL_BUTTON_RIGHT;
	}
	else if (_input == "MOUSE_MIDDLE") {
		key = SDL_BUTTON_MIDDLE;
	}
	else {
		auto _realKey = SDL_GetScancodeFromName(_input.c_str());
		key = _realKey;
		
	}
	this->bindings.emplace(key, _callback);

}

const std::unordered_map<int16_t, std::function<void()>>& InputComponent::GetBindings()
{
	return bindings;
}
