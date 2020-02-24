// BlocksGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "JelliesGame.h"
#include "RenderSystem.h"
#include "AudioSystem.h"
#include "InputSystem.h"
#include "CollisionSystem.h"
#include "MixerAudioSystem.h"
#include "MovementSystem.h"
#include "TransformComponent.h"
#include "MovementComponent.h"
#include "Jelly.h"
#include "GameObject.h"

#include "EndPoint.h"
#include "Grid.h"
#include "World.h"
#include "PlayButton.h"
#include "QuitButton.h"
#include "HUD.h"

void ResizeWindow(World* world, const SDL_Event& _event) {
	if (_event.window.event == SDL_WINDOWEVENT_RESIZED) {
		float scaleX, scaleY;
		int w, h;
		SDL_RenderGetScale(world->GetSystem<RenderSystem>()->GetSDLRenderer(), &scaleX, &scaleY);
		world->GetCamera2D().SetScaleX(scaleX);
		world->GetCamera2D().SetScaleY(scaleY);
		world->GetCamera2D().SetResolution((round(world->GetCamera2D().GetSize().x * scaleX)),round(world->GetCamera2D().GetSize().y * scaleY));
		world->GetCamera2D().SetWindowSize(world->GetSystem<RenderSystem>()->GetWindowWidth(), world->GetSystem<RenderSystem>()->GetWindowHeight());
		auto font = world->GetFontManager().Get("OpenSans-Regular");
		//font->SetFontSize(world->GetFontManager().DefaultFontSize);
		std::cout << "Window Size:" << world->GetSystem<RenderSystem>()->GetWindowWidth() << "x" << world->GetSystem<RenderSystem>()->GetWindowHeight() << std::endl;
		std::cout << "External Resolution: " << world->GetCamera2D().GetSize().x * scaleX << "x" << world->GetCamera2D().GetSize().y * scaleY << std::endl;
		std::cout << "Virtual Resolution: " << world->GetCamera2D().GetSize().x << "x" << world->GetCamera2D().GetSize().y << std::endl;

	}
}



void JelliesGame::SetupWorldSystems()
{
	// using irrKlang audio engine
	//auto audioSystem = GameWorld.GetSystem<AudioSystem>(); 
	auto audioSystem = GameWorld.GetSystem<MixerAudioSystem>();
	auto& soundManager = audioSystem->GetAudioManager();
	GameWorld.GetSystem<InputSystem>()->RegisterWorldEvent(&GameWorld, SDL_QUIT, std::function<void(World*, const SDL_Event&)>([](World* _world, const SDL_Event& _event) { _world->SetIsRunning(false); }));
	GameWorld.GetSystem<InputSystem>()->RegisterWorldEvent(&GameWorld, SDL_WINDOWEVENT, &ResizeWindow);
	GameWorld.GetSystem<InputSystem>()->RegisterWorldEvent(&GameWorld, SDL_KEYDOWN, std::bind(&JelliesGame::HandlePauseKey, this, _1, _2));
	audioSystem->SetVolume(0.10f);
	audioSystem->GetAudioManager().LoadMusic("theme", ".\\assets\\audio\\ElectronicFantasy.ogg");
	audioSystem->Play2DSound("theme", true);
}

void JelliesGame::SetupWorldObjects()
{
	auto& TexManager = GameWorld.GetSystem<RenderSystem>()->GetTextureManager();

	GameObject* background = GameWorld.CreateGameObject();
	background->AddComponent<SpriteComponent>(TexManager.Get("background"), -1);
	GameObject* logo = GameWorld.CreateGameObject();

	Texture* logoTex = TexManager.Get("jellieslogo");
	logo->AddComponent<SpriteComponent>(logoTex);
	logo->AddComponent<TransformComponent>(0, 50, logoTex->GetWidth(), logoTex->GetHeight());
	logo->AddTag("logo");

	std::vector<Texture*> cubeTextures {TexManager.Get("JellyR"), TexManager.Get("JellyG"), TexManager.Get("JellyB"), TexManager.Get("JellyP")};
	Grid _grid(cubeTextures, Vector2(310, -102));
	auto grid = GameWorld.AddGameObject(_grid);
	grid->IsActive = false;
	EndPoint end = EndPoint(Vector2(-75, -102));
	GameWorld.AddGameObject(end);
	
	HUD hud = HUD(TexManager.Get("playbutton"), TexManager.Get("quitbutton"), TexManager.Get("score"), TexManager.Get("finalscore"), TexManager.Get("pausebutton"),  TexManager.Get("pauseoverlay"));
	GameWorld.AddGameObject(hud);



}

void JelliesGame::OnWorldUpdate()
{


}

void JelliesGame::PreloadResources()
{
	TextureManager& texManager = GameWorld.GetSystem<RenderSystem>()->GetTextureManager();
	texManager.LoadResource("crate", "assets\\sprites\\crate.png");
	texManager.LoadResource("JellyR", "assets\\sprites\\JellyR.png");
	texManager.LoadResource("JellyG", "assets\\sprites\\JellyG.png");
	texManager.LoadResource("JellyB", "assets\\sprites\\JellyB.png");
	texManager.LoadResource("JellyP", "assets\\sprites\\JellyP.png");
	texManager.LoadResource("background", "assets\\sprites\\Background.png");
	texManager.LoadResource("jellieslogo", "assets\\sprites\\Jellies.png");
	texManager.LoadResource("playbutton", "assets\\sprites\\Button.png");
	texManager.LoadResource("score", "assets\\sprites\\ScoreWindow.png");
	texManager.LoadResource("quitbutton", "assets\\sprites\\Quit.png");
	texManager.LoadResource("finalscore", "assets\\sprites\\FinalScore.png");
	texManager.LoadResource("pausebutton", "assets\\sprites\\Pause.png");
	texManager.LoadResource("pauseoverlay", "assets\\sprites\\PauseOverlay.png");
	//using irrkland sound engine
	//AudioManager& soundManager = GameWorld.GetSystem<AudioSystem>()->GetAudioManager();
	//using SDL_mixer engine
	auto& soundManager = GameWorld.GetSystem<MixerAudioSystem>()->GetAudioManager();
	soundManager.LoadResource("slimedestroy", "assets\\audio\\slimedestroy.wav");
	FontManager& fontManager = GameWorld.GetFontManager();
	fontManager.LoadResource("OpenSans-Regular", "assets\\fonts\\OpenSans-Regular.ttf");
}

void JelliesGame::MainMenu()
{
}

void JelliesGame::PlayGame()
{
	GameWorld.GetGameObjectWithTag("grid")->IsActive = true;
}

void JelliesGame::PauseGame()
{

	auto hud = static_cast<HUD*>(GameWorld.GetGameObjectWithTag("HUD"));
	auto grid = static_cast<Grid*>(GameWorld.GetGameObjectWithTag("grid"));
	if (grid->IsActive) {
		grid->IsActive = false;
		grid->GetComponent<TextComponent>()->SetIsEnabled(true);
		hud->ShowPauseButton();
		IsPaused = true;
	}
	
}

void JelliesGame::ResumeGame()
{
	if (IsPaused) {
		auto hud = static_cast<HUD*>(GameWorld.GetGameObjectWithTag("HUD"));
		auto grid = static_cast<Grid*>(GameWorld.GetGameObjectWithTag("grid"));
		grid->IsActive = true;
		hud->HidePauseButton();
		IsPaused = false;
	}
	
}

void JelliesGame::HandlePauseKey(World* _world, const SDL_Event& _event)
{
	if (_event.type == SDL_KEYDOWN) {
		if (_event.key.keysym.scancode == SDL_SCANCODE_P) {
			if (!IsPaused) {
				PauseGame();
			}
			else {
				ResumeGame();
			}
		}
	}
	
}
