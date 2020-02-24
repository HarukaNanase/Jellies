#pragma once
#include "GameObject.h"
#include <map>
#include "Vector2.h"
/*!
 * \class HUD
 *
 * \brief The HUD for the game. Contains the PlayButton, Quit Button, and Score windows.
 *
 */
class HUD : public GameObject
{

private:
	std::map<std::string, GameObject*> HUDObjects;
	void CreatePlayButton();
	void CreateQuitButton();
	void CreateScore();

	std::map<std::string, Texture*> Texs;


public:
	HUD(Texture* _playButtonTex, Texture* _quitButtonTex, Texture* _scoreTex, Texture* _finalScoreTex, Texture* _pauseButtonTex, Texture* _pauseOverlayTex);
	
	void OnPlayButtonClicked();
	void OnQuitButtonClicked();
	void ShowPauseButton();
	void HidePauseButton();
	void ShowEndMenu();
	void HideButtons();


	virtual void OnInitialize() override;
	virtual void OnDestroy() override;


};

