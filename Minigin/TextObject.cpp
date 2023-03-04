#include <stdexcept>
#include <SDL_ttf.h>
#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"

#include "Azemacros.h"

aze::TextObject::TextObject(std::weak_ptr<GameObject> pParent, const std::string& text, std::shared_ptr<Font> pFont)
	:Component(pParent)
	, m_needsUpdate{ true }
	, m_text{ text }
	, m_font{ pFont }
	, m_textTexture{ nullptr }
	, m_Color{255,255,255}
{
}

void aze::TextObject::Update(float)
{
	if (m_needsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_Color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void aze::TextObject::Render() const
{
	if (m_textTexture != nullptr)
	{
		const auto& pos = GetGameObject().lock()->GetTransform().GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
aze::TextObject& aze::TextObject::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
	return *this;
}

aze::TextObject& aze::TextObject::SetPosition(const float , const float )
{
	assert(false && "Currently not implemented");
	return *this;
}

aze::TextObject& aze::TextObject::SetFont(std::shared_ptr<Font> pFont)
{
	m_font = pFont;
	m_needsUpdate = true;
	return *this;
}

aze::TextObject& aze::TextObject::SetColor(const SDL_Color& sdl_Col)
{
	m_Color = sdl_Col;
	m_needsUpdate = true;
	return *this;
}


