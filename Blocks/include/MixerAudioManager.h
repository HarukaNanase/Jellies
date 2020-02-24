#pragma once
#include "ResourceManager.h"
#include "Audio.h"


class MixerAudioManager : public ResourceManager<MixerAudioManager, Audio>
{
private:
	std::string PathToSoundAssets;
public:
	MixerAudioManager();
	MixerAudioManager(const std::string& _path);
	void DestroyResource(const std::string& _assetName) override;
	const std::string& GetPathToSoundAssets();

	Audio& LoadResource(const std::string& _assetName, const std::string& _assetPath) override;
	Audio* LoadMusic(const std::string& _assetName, const std::string& _assetPath);


};

