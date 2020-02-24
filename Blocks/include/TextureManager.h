#pragma once
#include "Texture.h"
#include "ResourceManager.h"

/*!
 * \class TextureManager
 *
 * \brief  Responsible for loading and storing textures. Interfaces with SDL_Renderer for the generation of the texture.
 */
class TextureManager : public ResourceManager<TextureManager, Texture>
{

private:
	SDL_Renderer* Renderer;
public:
	
	void SetRenderer(SDL_Renderer* _renderer);
	// Inherited via ResourceManager
	virtual Texture& LoadResource(const std::string& _assetName, const std::string& _assetPath) override;
	virtual void DestroyResource(const std::string& _assetName) override;

	
};

