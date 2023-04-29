#pragma once
#include "Event.h"

namespace aze
{
	class Ev_AddScore final : public Event
	{
	public:
		Ev_AddScore(int score) :Event("Ev_AddScore"), m_Score{ score } {};
		virtual ~Ev_AddScore() = default;

		int GetScore() const
		{
			return m_Score;
		}

	private:
		int m_Score;
	};
}