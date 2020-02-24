#include "SoundComponent.h"

#include <string>
void SoundComponent::Play2DSound(const std::string& _soundName, bool _loop)
{
	auto sound = Sound{ _soundName, _loop };
	this->SoundsToPlay.push_back(sound);

}

std::vector<Sound>& SoundComponent::GetSoundsToPlay()
{
	return SoundsToPlay;
}
