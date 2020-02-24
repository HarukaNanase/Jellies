#include "AudioManager.h"
#include "AudioSystem.h"

using namespace irrklang;

AudioManager::AudioManager()
{
}

AudioManager::AudioManager(ISoundEngine* _engine, const std::string& _path)
{
	SoundEngine = _engine;
	PathToSoundAssets = _path;
}

void AudioManager::DestroyResource(const std::string& _assetName)
{
	SoundEngine->removeSoundSource(Get(_assetName)->GetSoundSource());
	this->RemoveResource(_assetName);
}

AudioSource& AudioManager::LoadResource(const std::string& _assetName, const std::string& _assetPath)
{
	if (SoundEngine) {
		ISoundSource* soundSource = SoundEngine->addSoundSourceFromFile(_assetPath.c_str(), ESM_AUTO_DETECT, true);
		auto sound = std::make_unique<AudioSource>(soundSource, CurrentId);
		CurrentId++;
		this->AddResource(_assetName, sound);
		return *sound;
	}
	
	std::string message = std::string("AudioManager: Failed to load asset:") + _assetPath;
	throw std::exception(message.c_str());
}

const std::string& AudioManager::GetPathToSoundAssets()
{
	return this->PathToSoundAssets;
}

void AudioManager::SetPathToSoundAssets(const std::string& _path)
{

}

