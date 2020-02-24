#include "RenderSystem.h"
#include "World.h"
#include <iostream>
#include <TransformComponent.h>
#include <SDL_ttf.h>
#define WINDOW_TITLE "Miniclip Challenge - Blocks"


const void RenderSystem::Draw(SpriteComponent& _spriteToDraw, SDL_FRect* _transform)
{
	SDL_SetTextureColorMod(_spriteToDraw.GetTexture()->GetTex(), _spriteToDraw.GetColor().r, _spriteToDraw.GetColor().g, _spriteToDraw.GetColor().b);
	SDL_RenderCopyF(this->Renderer, _spriteToDraw.GetTexture()->GetTex(), NULL, _transform);
}

const void RenderSystem::Draw(Text& _text)
{
	auto textToDraw = _text.GetText();
	auto font = _text.GetFont();
	auto textColor = _text.GetTextColor();
	auto position = _text.GetPosition();
	auto& camera = GetWorld()->GetCamera2D();
	SDL_Color color = { textColor.r, textColor.g, textColor.b };
	if (font->GetFont() != nullptr) {
		SDL_Surface* surface = TTF_RenderText_Blended(font->GetFont(), textToDraw.c_str(), color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(GetSDLRenderer(), surface);
		SDL_FreeSurface(surface);
		int textWidth, textHeight;
		SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
		float inScreenX = (position.x + (camera.GetSize().x / 2) - camera.GetPosition().x);
		if (_text.IsCenter)
			inScreenX -= textWidth / 2;
		float inScreenY = (-position.y + (camera.GetSize().y / 2) - camera.GetPosition().y - textHeight / 2);
		SDL_FRect dst = { inScreenX, inScreenY ,textWidth, textHeight };

		SDL_RenderCopyF(GetSDLRenderer(), texture, NULL, &dst);

		SDL_DestroyTexture(texture);
	}
}


const void RenderSystem::Draw(World& _world)
{
	this->ClearScreen();
	Camera2D& camera = GetWorld()->GetCamera2D();
	auto& objects = GetWorld()->GetGameObjects(this->GetComponentMask());
	auto objCopy = objects;
	auto& optionalObjects = GetWorld()->GetGameObjects(this->GetOptionalMask());

	std::sort(objCopy.begin(), objCopy.end(), [](GameObject* _obj1, GameObject* _obj2) {
		auto _obj1Sprite = _obj1->GetComponent<SpriteComponent>();
		auto _obj2Sprite = _obj2->GetComponent<SpriteComponent>();
		return _obj1Sprite->GetZIndex() < _obj2Sprite->GetZIndex();
	});


	for (auto& renderable : objCopy) {
		auto spriteComponent = renderable->GetComponent<SpriteComponent>();
		if (spriteComponent->IsEnabled() ) {
			if (renderable->HasComponent<TransformComponent>()) {
				auto transform = renderable->GetComponent<TransformComponent>();
				if (IsOnScreen(*transform, camera)) {
					SDL_FRect target = transform->GetTransform();
					auto& position = transform->GetPosition();
					auto& size = transform->GetSize();
					target.x = (position.x + (camera.GetSize().x / 2) - camera.GetPosition().x - size.x / 2);
					target.y = (-position.y + (camera.GetSize().y / 2) - camera.GetPosition().y - size.y / 2);
					target.w = size.x;
					target.h = size.y;
					Draw(*renderable->GetComponent<SpriteComponent>(), &target);
				}
			}
			else {
				Draw(*renderable->GetComponent<SpriteComponent>(), nullptr);
			}
		
		}
	}
	
	for (auto& object : optionalObjects) {
		auto textComponent = object->GetComponent<TextComponent>();
		if (textComponent->IsEnabled())
			for (auto& text : textComponent->GetTexts()) {
				if(text.second.IsEnabled)
					Draw(text.second);
			}
	}


	this->RenderToScreen();
}

bool RenderSystem::InitWindow(const char* _WindowTitle, int _x, int _y, int _width, int _height, Uint32 flags)
{

	WindowHandle = SDL_CreateWindow(WINDOW_TITLE, 100, 100, GetWorld()->GetCamera2D().GetSize().x, GetWorld()->GetCamera2D().GetSize().y, flags );
	return WindowHandle != nullptr;
}

bool RenderSystem::InitRenderer(int _DriverIndex, Uint32 _flags)
{
	Renderer = SDL_CreateRenderer(WindowHandle, _DriverIndex, _flags);
	return Renderer != nullptr;
}

bool RenderSystem::IsOnScreen(TransformComponent& transform, Camera2D& camera)
{
	auto& position = transform.GetPosition();
	auto size = transform.GetSize();
	
	if (position.x + size.x / 2 >= -camera.GetSize().x / 2)
		return true;
	else if (position.x - size.x / 2 <= camera.GetSize().x / 2)
		return true;
	else if (position.y - size.y / 2 <= camera.GetSize().y / 2)
		return true;
	else if (position.y + size.y / 2 >= -camera.GetSize().y / 2)
		return true;

	return false;
}

void RenderSystem::RenderToScreen()
{
	SDL_RenderPresent(Renderer);
}

const void RenderSystem::ClearScreen()
{
	SDL_RenderClear(Renderer);
}

const int RenderSystem::GetWindowWidth()
{
	return SDL_GetWindowSurface(this->WindowHandle)->w;
}

const int RenderSystem::GetWindowHeight()
{
	return SDL_GetWindowSurface(this->WindowHandle)->h;

}


RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem()
{
	Destroy();
}

SDL_Renderer* RenderSystem::GetSDLRenderer()
{
	return Renderer;
}

SDL_Window* RenderSystem::GetWindowHandle()
{
	return WindowHandle;
}

TextureManager& RenderSystem::GetTextureManager()
{
	return TexManager;
}



void RenderSystem::SetTargetFPS(float _newTarget)
{
	this->TargetFPS = _newTarget;
}

void RenderSystem::Initialize()
{

	Camera2D& camera = GetWorld()->GetCamera2D();
	if (!InitWindow("Miniclip Challenge - Blocks", 100, 100, camera.GetSize().x, camera.GetSize().y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI)) {
		std::cout << "Error creating SDL Window: " << SDL_GetError() << std::endl;
	}

	if (!InitRenderer(-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC )) {
		std::cout << "Error creating SDL Renderer: " << SDL_GetError() << std::endl;;
	}
	TexManager.SetRenderer(GetSDLRenderer());

	SDL_RendererInfo rendererInfo = {};
	SDL_GetRenderDriverInfo(0, &rendererInfo);
	std::cout << "Running on: " << rendererInfo.name << std::endl;
	SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	
	SDL_RenderSetLogicalSize(GetSDLRenderer(), camera.GetSize().x, camera.GetSize().y);



}

void RenderSystem::Update(float _deltaTime)
{
	
	Draw(*this->GetWorld());
	
}

void RenderSystem::Destroy()
{
	TexManager.GetResources().clear();
	SDL_DestroyRenderer(this->Renderer);
	std::cout << "SDL_Renderer has been destroyed." << std::endl;
	SDL_DestroyWindow(this->WindowHandle);
	std::cout << "SDL_Window has been destroyed." << std::endl;

}
