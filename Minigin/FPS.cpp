#include "FPS.h"
#include "TextObject.h"
#include <sstream>

void aze::FPS::SetUpdateInterval(float interval)
{
	m_UpdateInterval = interval;
}

void aze::FPS::Update(float elapsedSec)
{
	m_TimeElapsed += elapsedSec;
	++m_NrFramesPassed;
	if (m_TimeElapsed >= m_UpdateInterval)
	{
		std::stringstream s;
		s << /*static_cast<int>*/(m_NrFramesPassed / m_TimeElapsed);
		s << " FPS";
		m_pTextRenderer.lock()->SetText(s.str());
		m_NrFramesPassed = 0;
		m_TimeElapsed = 0.f;
	}
}
