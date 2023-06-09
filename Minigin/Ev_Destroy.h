#pragma once
#include "Event.h"

namespace aze
{
	template <typename T>
	class Ev_Destroy final : public Event
	{
	public:
		Ev_Destroy(T* pDestroyed)
			:Event("DestroyEvent")
			,m_pEntity{ pDestroyed }
		{}

		const T* GetEntity() const { return m_pEntity; }

	private:
		const T* m_pEntity;
	};
}