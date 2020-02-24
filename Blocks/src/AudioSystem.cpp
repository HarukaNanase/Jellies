#include "AudioSystem.h"
#include "SDL.h"
#include <iostream>
#include "SoundComponent.h"
#include "World.h"
#define SOUND_ASSETS_PATH "assets"

AudioSystem::~AudioSystem()
{
	this->Destroy();
	this->SoundEngine->drop();
	this->SoundEngine = nullptr;
	
}

void AudioSystem::Play2DSound(const std::string& _assetName, bool _loop)
{

	auto source = SoundManager.Get(_assetName);
	if (source) {
		Play2DSoundFromMemory(source->GetSoundSource(), _loop);
	}
	else {
		Play2DSoundStream(_assetName, _loop);
	}
	
}


void AudioSystem::Play2DSoundFromMemory(ISoundSource* _source, bool _loop)
{
	SoundEngine->play2D(_source, _loop);
}

void AudioSystem::Play2DSoundStream(const std::string& _assetName, bool _loop) {
	SoundEngine->play2D((SoundManager.GetPathToSoundAssets() + _assetName).c_str(), _loop);
}


AudioSystem::AudioSystem()
{
	Initialize();
}

ISoundEngine* AudioSystem::GetSoundEngine()
{
	return SoundEngine;
}

AudioManager& AudioSystem::GetAudioManager()
{
	return SoundManager;
}

void AudioSystem::SetVolume(float _newVolume)
{
	SoundEngine->setSoundVolume(_newVolume);
}

void AudioSystem::Initialize()
{
	
	SoundEngine = createIrrKlangDevice();
	SoundEngine->setSoundVolume(0.005f);
	SoundManager = AudioManager(SoundEngine, "assets//audio//");
}

void AudioSystem::Update(float _deltaTime)
{
	auto& objects = GetWorld()->GetGameObjects(this->GetComponentMask());
	for (int i = 0; i < objects.size(); i++) {
		auto& object = objects[i];
		auto soundComponent = object->GetComponent< SoundComponent > ();
		if (soundComponent->IsEnabled()) {
			auto& soundsToPlay = soundComponent->GetSoundsToPlay();
			for (auto it = soundsToPlay.begin(); it != soundsToPlay.end(); ++it) {
				auto& sound = *it;
				SoundEngine->setSoundVolume(0.3f);
				this->Play2DSound(sound.SoundName, sound.IsLoop);
				SoundEngine->setSoundVolume(0.1f);
				if (!sound.IsLoop) {
					auto newSoundIt = soundsToPlay.erase(it);
					if (newSoundIt == soundsToPlay.end()) {
						break;
					}
				}
			}
		}
	}

}

void AudioSystem::Destroy()
{
}
