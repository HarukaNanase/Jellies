#include "MixerAudioManager.h"
#include "SDL_mixer.h"
#include <iostream>

MixerAudioManager::MixerAudioManager(const std::string& _path)
{
	this->PathToSoundAssets = _path;
}

MixerAudioManager::MixerAudioManager()
{

}

void MixerAudioManager::DestroyResource(const std::string& _assetName)
{
	this->RemoveResource(_assetName);
}

const std::string& MixerAudioManager::GetPathToSoundAssets()
{
	return this->PathToSoundAssets;
}

Audio& MixerAudioManager::LoadResource(const std::string& _assetName, const std::string& _assetPath)
{
	Mix_Chunk* chunk = Mix_LoadWAV(_assetPath.c_str());
	auto audio = std::make_unique<Audio>(chunk, CurrentId++);
	this->AddResource(_assetName, audio);
	return *audio;
}

Audio* MixerAudioManager::LoadMusic(const std::string& _assetName, const std::string& _assetPath)
{
	Mix_Music* music = Mix_LoadMUS(_assetPath.c_str());
	if (music == nullptr) {
		std::cout << "AudioManager:" << Mix_GetError() << std:: endl;
		return nullptr;
	}
	auto audio = std::make_unique<Audio>(music, CurrentId++);
	this->AddResource(_assetName, audio);
	return audio.get();
}
