#pragma once
#include "ResourceManager.h"
#include "irrKlang.h"
#include "SDL_stdinc.h"
#include <iostream>
using namespace irrklang;

struct AudioSource {

	ISoundSource* SoundSource;
	Uint32 SoundId;
	ISoundSource* GetSoundSource() { return SoundSource; }
	AudioSource(ISoundSource* _soundSource, Uint32 _id) : SoundSource(_soundSource), SoundId(_id) {}
	~AudioSource() {
		SoundSource = nullptr;
		std::cout << "Deleted audiosource with id: " << SoundId << std::endl;
	}
};

class AudioManager : public ResourceManager<AudioManager, AudioSource>
{

private:
	ISoundEngine* SoundEngine;
	std::string PathToSoundAssets;
public:
	AudioManager();
	AudioManager(ISoundEngine* _engine, const std::string& _path);
	virtual void DestroyResource(const std::string& _assetName) override;
	virtual AudioSource& LoadResource(const std::string& _assetName, const std::string& _assetPath) override;
	const std::string& GetPathToSoundAssets();
	void SetPathToSoundAssets(const std::string& _path);


};

