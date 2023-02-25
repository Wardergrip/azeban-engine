#pragma once
#include <string>
#include <memory>
#include <SDL_pixels.h>
#include "Transform.h"

#include "RenderComponent.h"
#include "UpdateComponent.h"

namespace aze
{
	class Font;
	class Texture2D;
	class TextObject final : public RenderComponent
	{
	public:
		void Update(float elapsedSec) override;
		void Render() const override;

		TextObject* SetText(const std::string& text);
		TextObject* SetPosition(float x, float y);
		TextObject* SetFont(std::shared_ptr<Font> pFont);
		TextObject* SetColor(const SDL_Color& sdl_Col);

		TextObject() = default;
		TextObject(std::weak_ptr<GameObject> pParent);
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
	private:
		bool m_needsUpdate{ true };
		std::string m_text{};
		Transform m_transform{};
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
		SDL_Color m_Color{ 255,255,255 };
	};
}
