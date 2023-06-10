#pragma once
#include "Event.h"

namespace aze
{
	class BoxColliderComponent;
	class Ev_TriggerOverlap : public Event
	{
	public:
		Ev_TriggerOverlap(BoxColliderComponent* eventMaker, BoxColliderComponent* colliderHit)
			:Event("Ev_TriggerOverlap")
			, m_EventMaker{ eventMaker }
			, m_ColliderHit{ colliderHit }
		{}
		virtual ~Ev_TriggerOverlap() = default;

		BoxColliderComponent* GetEventMaker() { return m_EventMaker; }
		BoxColliderComponent* GetColliderHit() { return m_ColliderHit; }

	private:
		BoxColliderComponent* m_EventMaker;
		BoxColliderComponent* m_ColliderHit;
	};
}