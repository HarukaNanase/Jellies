#include "InputSystem.h"
#include "TransformComponent.h"
#include <iostream>
#include <World.h>
using namespace std::placeholders;

bool InputSystem::IsClickOnObject(const Vector2& _mousePosition, GameObject* _obj)
{
	if (_obj->HasComponent<TransformComponent>()) {
		auto transform = _obj->GetComponent<TransformComponent>();
		Vector2 objectCenter = transform->GetPosition();
		auto objectSize = transform->GetSize();
		auto objectBoundTop = objectCenter.y + objectSize.y / 2;
		auto objectBoundBottom = objectCenter.y - objectSize.y / 2;
		auto objectBoundRight = objectCenter.x + objectSize.x / 2;
		auto objectBoundLeft = objectCenter.x - objectSize.x / 2;
		if (_mousePosition.x <= objectBoundRight && _mousePosition.x >= objectBoundLeft
			&& _mousePosition.y >= objectBoundBottom && _mousePosition.y <= objectBoundTop) {

			return true;
		}
	}


	return false;
}

bool InputSystem::IsClickOnGame(const Vector2& _mousePosition, const Vector2& _gameRes)
{
	return !(_mousePosition.x < (-_gameRes.x / 2) || _mousePosition.x >(_gameRes.x / 2) || _mousePosition.y < (-_gameRes.y / 2) || _mousePosition.y >(_gameRes.y / 2));
}

void InputSystem::Update(float _deltaTime)
{	
	auto& gameObjects = GetWorld()->GetGameObjects(this->GetComponentMask());
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_WINDOWEVENT || e.type == SDL_QUIT || e.type == SDL_KEYDOWN) {
			for (auto& typesAndEvents : WorldEvents) {
				auto& worldEvents = typesAndEvents.second;
				for (auto& _event : worldEvents) {
					if(_event.EventType == e.type)
						_event.CallbackMethod(e);
				
				}
			}
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) {
			TheMouse.MouseMask = SDL_GetMouseState(&TheMouse.x, &TheMouse.y);
			if ((TheMouse.MouseMask & SDL_BUTTON(SDL_BUTTON_LEFT))) {
				auto inWorldMouse = GetWorld()->GetCamera2D().ScreenToWorldRaycast(TheMouse.x, TheMouse.y);
				if (IsClickOnGame(inWorldMouse, GetWorld()->GetCamera2D().GetSize())) {
					for (auto obj : gameObjects) {
						if (obj->GetComponent<InputComponent>()->IsEnabled())
							if (IsClickOnObject(inWorldMouse, obj)) {
								auto& bindings = obj->GetComponent<InputComponent>()->GetBindings();
								for (auto binding : bindings) {
									if (binding.first == SDL_BUTTON_LEFT) {
										binding.second();
										return;
									}
								}
							}
					}
				}

			}
		}

		else {
			for (auto obj : gameObjects) {
				if (obj->GetComponent<InputComponent>()->IsEnabled()) {
						auto& bindings = obj->GetComponent<InputComponent>()->GetBindings();
						for (auto& binding : bindings) {
							if (TheKeyboard.Keys[binding.first]) {
								binding.second();
							}
						}
					
				}

			}
		}
	}




}

InputSystem::InputSystem()
{
	
}



void InputSystem::RegisterWorldEvent(World* _world, SDL_EventType _sdlEventType, std::function<void(World* _world, const SDL_Event& _event)> _callback)
{
	auto& eventsForEventType = WorldEvents[_sdlEventType];
	auto bindedMethod = std::bind(_callback, _world, _1);
	WorldEventBinding _worldBinding = WorldEventBinding{ _world, bindedMethod, _sdlEventType };
	eventsForEventType.push_back(_worldBinding);
}

void InputSystem::OnInitialize()
{
	TheKeyboard.Keys = SDL_GetKeyboardState(NULL);
	TheMouse.MouseMask = SDL_GetMouseState(&TheMouse.x, &TheMouse.y);
}


