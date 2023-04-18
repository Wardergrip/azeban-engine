#include "ScoreDisplayComponent.h"
#include <sstream>
#include "TextObject.h"

void aze::ScoreDisplayComponent::OnNotify(Ev_AddScore* event)
{
	if(event == nullptr) return;

	std::stringstream s;
	s << "Score: ";
	s << event->GetScore();
	m_pTextRenderer.lock()->SetText(s.str());
}
