#pragma once
#include "Event.h"
namespace aze
{
	class BoxColliderComponent;
	class Ev_Collision final : public Event
	{
	public:
		Ev_Collision(BoxColliderComponent* eventMaker, BoxColliderComponent* colliderHit)
			:Event("Ev_Collision")
			,m_EventMaker{eventMaker}
			, m_ColliderHit{colliderHit}
		{}
		virtual ~Ev_Collision() = default;

		BoxColliderComponent* GetEventMaker() { return m_EventMaker; }
		BoxColliderComponent* GetColliderHit() { return m_ColliderHit; }

	private:
		BoxColliderComponent* m_EventMaker;
		BoxColliderComponent* m_ColliderHit;
	};
}