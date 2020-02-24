#pragma once
#include "Component.h"
#include "AudioManager.h"
struct Sound {
	std::string SoundName;
	bool IsLoop;
};

/*!
 * \class SoundComponent
 *
 * \brief  Enables a game object to queue sounds to be played by the SoundSystem.
 */
class SoundComponent : public Component
{
private:

public:
	std::vector<Sound> SoundsToPlay;

	void Play2DSound(const std::string& _soundName, bool _loop = false);
	std::vector<Sound>&  GetSoundsToPlay();

};

