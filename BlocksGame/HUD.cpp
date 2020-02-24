#include "HUD.h"
#include "Components.h"
#include "World.h"
#include "PlayButton.h"
#include "QuitButton.h"
#include "Grid.h"
#include "World.h"
void HUD::CreatePlayButton()
{
	
}

void HUD::CreateQuitButton()
{
	
}

void HUD::CreateScore()
{
	
}


void HUD::OnPlayButtonClicked()
{
	HideButtons();
	HUDObjects["score"]->IsActive = true;
	HUDObjects["finalscore"]->IsActive = false;
	GetWorld()->GetGameObjectWithTag("logo")->IsActive = false;

	GetComponent<TextComponent>()->GetText("FinalScore")->SetText("");

	auto grid = static_cast<Grid*>(GetWorld()->GetGameObjectWithTag("grid"));
	if(grid != nullptr)
		grid->Reset();
}

void HUD::OnQuitButtonClicked()
{
	GetWorld()->SetIsRunning(false);
}

void HUD::ShowPauseButton()
{
	this->HUDObjects["pauseoverlay"]->IsActive = true;
	this->HUDObjects["pausebutton"]->IsActive = true;
}

void HUD::HidePauseButton()
{
	this->HUDObjects["pauseoverlay"]->IsActive = false;
	this->HUDObjects["pausebutton"]->IsActive = false;
}

void HUD::ShowEndMenu()
{
	auto textComp = this->GetComponent<TextComponent>();
	auto grid = static_cast<Grid*>(GetWorld()->GetGameObjectWithTag("grid"));
	if (grid != nullptr) {
		auto scores = grid->GetJellyCount();
		textComp->GetText("RedJelly")->SetText(std::to_string(scores[0]));
		textComp->GetText("GreenJelly")->SetText(std::to_string(scores[1]));
		textComp->GetText("BlueJelly")->SetText(std::to_string(scores[2]));
		textComp->GetText("PurpleJelly")->SetText(std::to_string(scores[3]));
		textComp->GetText("FinalScore")->SetText(std::to_string(grid->GetCurrentScore()));
		textComp->SetIsEnabled(true);
		auto finalScore = HUDObjects["finalscore"];
		finalScore->IsActive = true;
		auto score = HUDObjects["score"];
		score->IsActive = false;
		auto play = HUDObjects["playbutton"];
		play->IsActive = true;
		auto quit = HUDObjects["quitbutton"];
		quit->IsActive = true;
	}


}

void HUD::HideButtons()
{
	HUDObjects["playbutton"]->IsActive = false;
	HUDObjects["quitbutton"]->IsActive = false;
	HUDObjects["finalscore"]->IsActive = false;
	this->GetComponent<TextComponent>()->SetIsEnabled(false);
}

HUD::HUD(Texture* _playButtonTex, Texture* _quitButtonTex, Texture* _scoreTex, Texture* _finalScoreTex, Texture* _pauseButtonTex, Texture* _pauseOverlayTex)
{
	Texs.emplace("PlayButtonTex",_playButtonTex);
	Texs.emplace("QuitButtonTex", _quitButtonTex);
	Texs.emplace("ScoreTex", _scoreTex);
	Texs.emplace("FinalScoreTex", _finalScoreTex);
	Texs.emplace("PauseButtonTex", _pauseButtonTex);
	Texs.emplace("PauseOverlayTex", _pauseOverlayTex);
	this->AddComponent<TextComponent>();	
}

void HUD::OnInitialize()
{
	auto textComponent = this->GetComponent<TextComponent>();
	textComponent->AddText("RedJelly", GetWorld()->GetFontManager().Get("OpenSans-Regular"), Color{ 0x00, 0x00, 0x00, 0x00 }, "", Vector2(0, 102));
	textComponent->AddText("BlueJelly", GetWorld()->GetFontManager().Get("OpenSans-Regular"), Color{ 0x00, 0x00, 0x00, 0x00 }, "", Vector2(0, 74));
	textComponent->AddText("GreenJelly", GetWorld()->GetFontManager().Get("OpenSans-Regular"), Color{ 0x00, 0x00, 0x00, 0x00 }, "", Vector2(0, 44));
	textComponent->AddText("PurpleJelly", GetWorld()->GetFontManager().Get("OpenSans-Regular"), Color{ 0x00, 0x00, 0x00, 0x00 }, "", Vector2(0, 10));
	textComponent->AddText("FinalScore", GetWorld()->GetFontManager().Get("OpenSans-Regular"), Color{ 0x00, 0x00, 0x00, 0x00 }, "", Vector2(0, 140));
	textComponent->GetText("FinalScore")->IsCenter = true;
	textComponent->SetIsEnabled(false);

	PlayButton play = PlayButton(Texs["PlayButtonTex"], Vector2(0, -60), this);
	this->HUDObjects.emplace("playbutton", GetWorld()->AddGameObject(play));
	QuitButton quit = QuitButton(Texs["QuitButtonTex"], Vector2(0, -110), this);
	this->HUDObjects.emplace("quitbutton", GetWorld()->AddGameObject(quit));
	GameObject* score = GetWorld()->CreateGameObject();
	score->AddComponent<SpriteComponent>(Texs["ScoreTex"], 1);
	score->AddComponent<TransformComponent>(-240, 160, Texs["ScoreTex"]->GetWidth() / 4, Texs["ScoreTex"]->GetHeight() / 4);
	score->IsActive = false;
	score->AddTag("score");
	this->HUDObjects.emplace("score", score);

	GameObject* finalScore = GetWorld()->CreateGameObject();
	finalScore->AddComponent<SpriteComponent>(Texs["FinalScoreTex"], 1);
	finalScore->AddComponent<TransformComponent>(0, 60, Texs["FinalScoreTex"]->GetWidth()/4, Texs["FinalScoreTex"]	->GetHeight()/4);
	finalScore->AddTag("finalscore");
	finalScore->IsActive = false;
	this->HUDObjects.emplace("finalscore", finalScore);

	GameObject* pauseButton = GetWorld()->CreateGameObject();
	pauseButton->AddComponent<SpriteComponent>(Texs["PauseButtonTex"], 2);
	pauseButton->AddComponent<TransformComponent>(0, 0, Texs["PauseButtonTex"]->GetWidth()/4, Texs["PauseButtonTex"]->GetHeight()/4);
	pauseButton->AddTag("pausebutton");
	pauseButton->IsActive = false;
	this->HUDObjects.emplace("pausebutton", pauseButton);

	GameObject* overlay = GetWorld()->CreateGameObject();
	overlay->AddComponent<SpriteComponent>(Texs["PauseOverlayTex"], 1);
	overlay->AddTag("pauseoverlay");
	overlay->IsActive = false;
	this->HUDObjects.emplace("pauseoverlay", overlay);


	this->AddTag("HUD");

}

void HUD::OnDestroy()
{
	for (auto pair : HUDObjects) {
		pair.second->Destroy();
	}
	HUDObjects.clear();
}

