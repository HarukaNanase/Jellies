#pragma once
#include "System.h"
#include "SDL.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "Camera2D.h"


/*!
 * \class RenderSystem
 *
 * \brief The system responsible for everything that is drawn to the screen. Capable of drawing textures to the screen, as well as text using SDL_TTF.
 *  
 */
class RenderSystem : public System
{	
private:
	SDL_Window* WindowHandle;
	SDL_Renderer* Renderer;
	TextureManager TexManager;

	void RenderToScreen();
	const void ClearScreen();
	const void Draw(SpriteComponent& _sprite, SDL_FRect* _component);
	const void Draw(Text& _text);
	const void Draw(class World& _world);
	bool InitWindow(const char* _windowTitle, int _x, int _y, int _width, int _height, Uint32 flags);
	bool InitRenderer(int _driverIndex = -1, Uint32 _flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	bool IsOnScreen(TransformComponent& transform, Camera2D& camera);
	float TargetFPS = 60;
	float FrameTime = 0;
public:
	RenderSystem();
	~RenderSystem();
	SDL_Renderer* GetSDLRenderer();
	SDL_Window* GetWindowHandle();
	TextureManager& GetTextureManager();
	void SetTargetFPS(float _newTarget);
	virtual void Initialize() override;
	virtual void Update(float _deltaTime) override;
	virtual void Destroy() override;

	const int GetWindowWidth();
	const int GetWindowHeight();
};

