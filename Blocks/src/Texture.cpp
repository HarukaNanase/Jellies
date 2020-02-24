#include "Texture.h"
#include "SDL_image.h"
#include <iostream>
Texture::Texture(SDL_Renderer* _renderer, const std::string& _texturePath, Uint32 _texId)
{
	auto surface = IMG_Load(_texturePath.c_str());
	Tex = SDL_CreateTextureFromSurface(_renderer, surface);
	TexId = _texId;
	SDL_FreeSurface(surface);
	SDL_QueryTexture(Tex, NULL, NULL, &this->w, &this->h);
}

int Texture::GetWidth()
{
	return w;
}

int Texture::GetHeight()
{
	return h;
}

Texture::~Texture()
{
	SDL_DestroyTexture(Tex);
	std::cout << "Deleted texture with id: " << TexId << std::endl;

}

SDL_Texture* Texture::GetTex()
{
	return Tex;
}
