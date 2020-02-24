#include "Font.h"

Font::Font(const std::string& _fontName, const std::string& _assetPath,Uint32 _fontSize, Uint32 _fontId)
{
	this->TheFont = TTF_OpenFont(_assetPath.c_str(), _fontSize);
	this->FontSize = _fontSize;
	this->FontName = _fontName;
	this->FontId = _fontId;
	this->FontPath = _assetPath;
}

Font::~Font()
{
	TTF_CloseFont(TheFont);
	std::cout << "Deleted font with id: " << FontId << std::endl;
}

TTF_Font* Font::GetFont()
{
	return this->TheFont;
}

Uint32 Font::GetFontSize()
{
	return FontSize;
}

void Font::SetFontSize(Uint32 _newSize)
{
	this->FontSize = _newSize;
	TTF_CloseFont(TheFont);
	this->TheFont = TTF_OpenFont(this->FontPath.c_str(), this->FontSize);

}
