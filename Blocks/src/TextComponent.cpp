#include "TextComponent.h"

void TextComponent::AddText(const std::string& _textName, Font* _font, Color _color, const std::string& _text, Vector2 _position)
{
	Text text(_font, _color, _text, _position);
	this->Texts.emplace(_textName, text);
}

void TextComponent::RemoveText(const std::string _textName)
{
	Texts.erase(_textName);

}

Text* TextComponent::GetText(const std::string _textName)
{
	if (Texts.find(_textName) != Texts.end()) {
		return &Texts[_textName];
	}
	else
		return nullptr;
}

std::map<std::string, Text>& TextComponent::GetTexts()
{
	return Texts;
}
