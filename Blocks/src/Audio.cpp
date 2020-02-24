#include "Audio.h"
#include <iostream>
Audio::~Audio()
{
	std::cout << "Destroyed Audio: " << this->ID << std::endl;
	if (Type == 0) {
		Mix_FreeMusic(Music);
	}
	else {
		Mix_FreeChunk(Chunk);
	}
}

Audio::Audio(Mix_Music* _music, Uint32 _id)
{
	this->Music = _music;
	this->Type = 0;
	this->ID = _id;
	this->Chunk = nullptr;
}

Audio::Audio(Mix_Chunk* _chunk, Uint32 _id)
{
	this->Chunk = _chunk;
	this->Type = 1;
	this->ID = _id;
	this->Music = nullptr;
}
