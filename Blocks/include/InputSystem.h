#pragma once

#include "System.h"
#include "SDL.h"
#include <unordered_map>
#include <functional>
#include "GameObject.h"
#include "InputComponent.h"
#include "Vector2.h"
/*!
 * \class InputSystem
 *
 * \brief The system responsible for reading input and executing callbacks depending on the input detected (MOUSE/KEYBOARD SUPPORTED).
 *
 */
class InputSystem : public System
{	
	struct InputEventBinding {
		GameObject* Object;
		std::function<void()> CallbackMethod;
		int16_t Action;
		InputEventBinding& operator=(const InputEventBinding& _other) {
			this->Object = _other.Object;
			this->CallbackMethod = _other.CallbackMethod;
			this->Action = _other.Action;
			return *this;
		}
	};
	struct WorldEventBinding {
		World* TheWorld;
		std::function<void(const SDL_Event& _event)> CallbackMethod;
		SDL_EventType EventType;
	};
	///Represents a mouse
	struct Mouse {
		Uint32 MouseMask;
		int x;
		int y;
	};
	///Represents the keyboard
	struct Keyboard {
		const Uint8* Keys;
	};

private:
	std::unordered_map<int16_t, std::vector<InputEventBinding>> RegisteredEvents; // game objects can register to receive certain specific input events
	std::unordered_map<SDL_EventType, std::vector<WorldEventBinding>> WorldEvents;
	Mouse TheMouse;
	Keyboard TheKeyboard;
	std::vector<GameObject*> ObjectsToDelete;
	bool IsClickOnObject(const Vector2& _mousePosition, GameObject* _obj);
	bool IsClickOnGame(const Vector2& _mousePosition, const Vector2& _gameRes);
public:

	void Update(float _deltaTime) override;
	InputSystem();

	//************************************
	// @brief Registers a callback to be executed by the world when the specifiec event type happens.
	//		  This is useful for events that happen when resizing  the window.
	// 
	// @param: World * _world
	// @param: SDL_EventType _sdlEventType
	// @param: std::function<void
	// @param: World * _world
	// @param: const SDL_Event & _event
	// @param: > _callback
	// @return:   void
	//************************************
	void RegisterWorldEvent(World* _world, SDL_EventType _sdlEventType, std::function<void(World* _world, const SDL_Event & _event)> _callback);

	void OnInitialize() override;

};

