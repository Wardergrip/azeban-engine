#include "FPS.h"
#include "TextObject.h"
#include "GameTime.h"
#include <sstream>

void aze::FPS::SetUpdateInterval(float interval)
{
	m_UpdateInterval = interval;
}

void aze::FPS::Update()
{
	m_TimeElapsed += GameTime::GetInstance().GetElapsed();
	++m_NrFramesPassed;
	if (m_TimeElapsed >= m_UpdateInterval)
	{
		std::stringstream s;
		s << /*static_cast<int>*/(m_NrFramesPassed / m_TimeElapsed);
		s << " FPS";
		m_pTextRenderer->SetText(s.str());
		m_NrFramesPassed = 0;
		m_TimeElapsed = 0.f;
	}
}
