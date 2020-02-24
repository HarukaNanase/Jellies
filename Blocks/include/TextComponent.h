#pragma once

#include "SDL_ttf.h"
#include "Color.h"
#include "Font.h"
#include "Vector2.h"
#include "Component.h"
#include <map>


/*!
 * \struct Text
 *
 * \brief A structure representing a Text to be processed by the RenderSystem.
 *
 */
struct Text {
	Text() {};
	Font* TheFont = nullptr;
	Color TextColor = { 0x00, 0x00, 0x00, 0x00 };
	std::string text = "";
	Vector2 Position;
	bool IsEnabled = true;
	bool IsCenter = false;

	Text(Font* _font, Color _color, const std::string& _text, Vector2 _position) {
		this->TheFont = _font;
		this->TextColor = _color;
		this->text = _text;
		this->Position = _position;
	};
	Color GetTextColor() const { return TextColor; }
	void SetTextColor(Color val) { TextColor = val; }
	const std::string& GetText() { return text; }
	void SetText(const std::string& val) { text = val; }
	Font* GetFont() { return TheFont; }
	void SetFont(Font* val) { TheFont = val; }
	const Vector2 GetPosition() { return Position; }
	void SetPosition(Vector2 val) { Position = val; }
};


/*!
 * \class TextComponent
 *
 * \brief Enables objects to write and render text to the screen. Useful for GUI.


 *
 */
class TextComponent : public Component
{
private:
	std::map<std::string, Text> Texts;
public:
	void AddText(const std::string& _textName, Font* _font, Color _color, const std::string& _text, Vector2 _position);
	void RemoveText(const std::string _textName);
	Text* GetText(const std::string _textName);
	std::map<std::string, Text>& GetTexts();
	


};

