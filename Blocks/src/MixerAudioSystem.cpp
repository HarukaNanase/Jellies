#include "MixerAudioSystem.h"
#include "SDL_mixer.h"
#include "World.h"

MixerAudioManager& MixerAudioSystem::GetAudioManager()
{
	return this->SoundManager;
}

void MixerAudioSystem::OnInitialize()
{
	int flags = MIX_INIT_MP3 || MIX_INIT_OGG;
	int status = Mix_Init(flags);
	if ((status & flags) != flags) {
		std::cout << "Failed to initialize SDL_Mixer with flags: " << Mix_GetError() << std::endl;
		return;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		std::cout << "Failed to initialize SDL_Mixer: "  << Mix_GetError() << std::endl;
	}

	this->SoundManager = MixerAudioManager("assets//audio//");

}

void MixerAudioSystem::Destroy()
{
	Mix_HaltMusic();
	Mix_Quit();
}

void MixerAudioSystem::Update(float _deltaTime)
{
	auto& objects = GetWorld()->GetGameObjects(this->GetComponentMask());
	for (int i = 0; i < objects.size(); i++) {
		auto& object = objects[i];
		auto soundComponent = object->GetComponent< SoundComponent >();
		if (soundComponent->IsEnabled()) {
			auto& soundsToPlay = soundComponent->GetSoundsToPlay();
			for (auto it = soundsToPlay.begin(); it != soundsToPlay.end(); ++it) {
				auto& sound = *it;
				this->Play2DSound(sound.SoundName, sound.IsLoop);
				if (!sound.IsLoop) {
					it = soundsToPlay.erase(it);
					if (it == soundsToPlay.end()) {
						break;
					}
				}
			}
		}
	}

}

void MixerAudioSystem::StopPlaying()
{
	Mix_HaltMusic();
}

void MixerAudioSystem::ResumePlaying()
{
	Mix_ResumeMusic();
}

void MixerAudioSystem::SetVolume(float _newVolume)
{
	int mixerVolume = _newVolume * MIX_MAX_VOLUME; //128 is sdl_mixer max volume
	std::clamp(mixerVolume, 0, MIX_MAX_VOLUME);
	Mix_Volume(-1, mixerVolume);
	Mix_VolumeMusic(mixerVolume);
}

void MixerAudioSystem::Play2DSound(const std::string& _assetName, bool _isLoop)
{
	Audio* audioToPlay = GetAudioManager().Get(_assetName);
	if (audioToPlay != nullptr) {
		int loops = (_isLoop) ? -1 : 0;
		if (audioToPlay->Type == 0) {	//music
			if (audioToPlay->Music != nullptr) {

				Mix_PlayMusic(audioToPlay->Music, loops);
			}
		}
		else if (audioToPlay->Type == 1) { //chunk
			if (audioToPlay->Chunk != nullptr) {
				Mix_PlayChannel(-1, audioToPlay->Chunk, loops);
			}
		}
	}
}
	

