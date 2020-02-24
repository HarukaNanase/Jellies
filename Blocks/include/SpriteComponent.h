#pragma once
#include "Color.h"
#include "Texture.h"
#include <memory>
#include "Component.h"


/*!
 * \class SpriteComponent
 *
 * \brief  Enables a game object to be tracked by the RenderSystem to be rendered into the world.
 */
class SpriteComponent : public Component
{
private:
	Color SpriteColor;
	Texture* Tex;
	float ZIndex = 0;

public:
	SpriteComponent(Texture* _tex, float _zIndex = 0);
	SpriteComponent(Texture* _tex, Color _color, float _zIndex = 0);
	const Color& GetColor();
	Texture* GetTexture();
	void SetZIndex(float _zIndex);
	float GetZIndex();
	void SetTexture(Texture* _tex);
	void SetColor(Color _color);
};
