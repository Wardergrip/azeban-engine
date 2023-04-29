#pragma once
#include "Event.h"

namespace aze
{
	class Ev_PlayerDied final : public Event
	{
	public:
		Ev_PlayerDied(int livesLeft) :Event("Ev_PlayerDied"), m_LivesLeft{ livesLeft } {};
		virtual ~Ev_PlayerDied() = default;

		int GetLivesLeft() const
		{
			return m_LivesLeft;
		}

	private:
		int m_LivesLeft;
	};
}