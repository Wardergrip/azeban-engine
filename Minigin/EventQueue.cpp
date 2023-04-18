#include "EventQueue.h"

void aze::EventQueue::AddEvent(std::unique_ptr<Event> pEvent)
{
	m_pQueue.push(std::move(pEvent));
}
