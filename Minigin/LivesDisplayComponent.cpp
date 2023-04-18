#include "LivesDisplayComponent.h"
#include "TextObject.h"
#include <sstream>

void aze::LivesDisplayComponent::OnNotify(Ev_PlayerDied* event)
{
	if (event == nullptr) return;

	std::stringstream s;
	s << "Lives: ";
	s << event->GetLivesLeft();
	m_pTextRenderer.lock()->SetText(s.str());
}
