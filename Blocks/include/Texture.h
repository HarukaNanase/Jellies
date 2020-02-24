#pragma once
#include "SDL.h"
#include <string>

/*!
 * \class Texture
 *
 * \brief A wrapper around the SDL_Texture type. Handles the release of the SDL_Texture by calling SDL_DestroyTexture upon destruction.
 *
 */
class Texture
{
private:
	SDL_Texture* Tex;
	Uint32 TexId;
	int w=0;
	int h=0;
public:
	Texture(SDL_Renderer* _renderer, const std::string& _texturePath, Uint32 _texId);
	int GetWidth();
	int GetHeight();
	~Texture();
	SDL_Texture* GetTex();
};

