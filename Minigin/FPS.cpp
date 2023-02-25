#include "FPS.h"
#include "TextObject.h"
#include <sstream>

void aze::FPS::SetUpdateInterval(float interval)
{
	m_UpdateInterval = interval;
}

void aze::FPS::SetTextureRenderer(std::weak_ptr<TextObject> pTextRenderer)
{
	m_pTextRenderer = pTextRenderer;
}

void aze::FPS::Update(float elapsedSec)
{
	m_TimeElapsed += elapsedSec;
	if (m_TimeElapsed >= m_UpdateInterval)
	{
		m_TimeElapsed = 0.f;
		std::stringstream s;
		s << /*static_cast<int>*/(1.f / elapsedSec);
		s << " FPS";
		m_pTextRenderer.lock()->SetText(s.str());
	}
}
