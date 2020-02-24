#pragma once
#include "System.h"
#include "MixerAudioManager.h"
#include "SoundComponent.h"
class MixerAudioSystem : public System
{

private:
	MixerAudioManager SoundManager;
public:
	MixerAudioManager& GetAudioManager();
	void OnInitialize() override;
	void Destroy() override;
	void Update(float _deltaTime) override;
	void StopPlaying();
	void ResumePlaying();
	void SetVolume(float _newVolume);
	void Play2DSound(const std::string& _assetName, bool _isLoop);
};

