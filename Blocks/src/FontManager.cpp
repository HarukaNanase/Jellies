#include "FontManager.h"

Font& FontManager::LoadResource(const std::string& _assetName, const std::string& _assetPath)
{
	auto font = std::make_unique<Font>(_assetName, _assetPath, DefaultFontSize, CurrentId++);
	this->AddResource(_assetName, font);

	return *font;
}

void FontManager::DestroyResource(const std::string& _assetName)
{
	this->RemoveResource(_assetName);
}
