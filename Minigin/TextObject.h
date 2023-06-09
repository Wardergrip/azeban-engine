#pragma once
#include <string>
#include <memory>
#include <SDL_pixels.h>
#include "Transform.h"

namespace aze
{
	class Font;
	class Texture2D;
	class TextObject final : public Component<TextObject>
	{
	public:
		void Update() override;

		TextObject& SetText(const std::string& text);
		TextObject& SetFont(std::shared_ptr<Font> pFont);
		TextObject& SetColor(const SDL_Color& sdl_Col);

		TextObject(GameObject* pParent, const std::string& text, std::shared_ptr<Font> pFont);
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
	private:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
		SDL_Color m_Color;
	};
}
