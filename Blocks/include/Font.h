#pragma once
#include "SDL_ttf.h"

#include <string>
#include <iostream>

/*!
 * \class Font
 *
 * \brief A wrapper around the TTF_Font type that handles release of the TTF_Font upon destruction.
 */
class Font
{
private:
	TTF_Font* TheFont;
	std::string FontName;
	std::string FontPath;
	Uint32 FontId;
	Uint32 FontSize;
public:
	Font(const std::string& _fontName, const std::string& _assetPath, Uint32 _fontSize, Uint32 _fontId);
	~Font();
	TTF_Font* GetFont();
	
	Uint32 GetFontSize();
	void SetFontSize(Uint32 _newSize);
};

