#pragma once
#include "Event.h"

namespace aze
{
	class PhysicsEvent final : public Event
	{
	public:
		PhysicsEvent()
			:Event("PhysicsEvent")
		{
		}
		virtual ~PhysicsEvent() = default;
	};
}