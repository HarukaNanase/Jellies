#include "TextureManager.h"
#include "SDL_image.h"


void TextureManager::SetRenderer(SDL_Renderer* _renderer)
{
	this->Renderer = _renderer;
}

Texture& TextureManager::LoadResource(const std::string& _assetName, const std::string& _assetPath)
{
	if (Renderer) {
		auto tex = std::make_unique<Texture>(this->Renderer, _assetPath, CurrentId);
		CurrentId++;
		this->AddResource(_assetName, tex);
		return *tex;
	}

}

void TextureManager::DestroyResource(const std::string& _assetName)
{
	//SDL_DestroyTexture(this->Get(_assetName).GetTex());
	this->RemoveResource(_assetName);
}

