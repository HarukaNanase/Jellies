#pragma once
#include "SDL_mixer.h"
class Audio
{
public:
	Mix_Chunk* Chunk;
	Mix_Music* Music;
	Uint8 Type;
	Uint32 ID;
	~Audio();
	Audio(Mix_Music* _music, Uint32 _id);
	Audio(Mix_Chunk* _chunk, Uint32 _id);
};

