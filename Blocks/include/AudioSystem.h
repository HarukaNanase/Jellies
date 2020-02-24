#pragma once
#include <string>
#include "AudioManager.h"
#include "System.h"
#include "irrKlang.h"
#include "SDL_mixer.h"
using namespace irrklang;

/*!
 * \class AudioSystem
 *
 * \brief The system responsible for every sound played. Is able to play from memory (streaming) and from memory (preloaded assets).
 *        Uses the irrKlang sound library.
 */
class AudioSystem : public System
{
private:
	ISoundEngine* SoundEngine;
	AudioManager SoundManager;
	void Play2DSoundFromMemory(ISoundSource* _source, bool _loop = false);
	void Play2DSoundStream(const std::string& _assetName, bool _loop = false);
public:
	~AudioSystem();
	void Play2DSound(const std::string& _assetPath, bool _loop = false);
	AudioSystem();
	ISoundEngine* GetSoundEngine();
	AudioManager& GetAudioManager();
	void SetVolume(float _newVolume);
	// Inherited via ISystem
	virtual void Initialize() override;
	virtual void Update(float _deltaTime) override;
	virtual void Destroy() override;
};

