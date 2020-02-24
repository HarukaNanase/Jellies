#pragma once
#include "ResourceManager.h"
#include "SDL_ttf.h"
#include "Font.h"

/*!
 * \class FontManager
 *
 * \brief  Responsible for loading and storing Fonts, which are wrappers around the TTF_Font* pointer.
 */
class FontManager :	public ResourceManager<FontManager, Font>
{
private:

public:
	Uint32 DefaultFontSize = 14;
	virtual Font& LoadResource(const std::string& _assetName, const std::string& _assetPath) override;
	virtual void DestroyResource(const std::string& _assetName) override;

};

