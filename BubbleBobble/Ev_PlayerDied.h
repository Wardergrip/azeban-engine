#pragma once
#include "Event.h"

namespace aze
{
	class GameObject;
	class Ev_PlayerDied final : public Event
	{
	public:
		Ev_PlayerDied(int livesLeft, GameObject* pPlayer) :Event("Ev_PlayerDied"), m_LivesLeft{ livesLeft }, m_pObject{ pPlayer } {};
		virtual ~Ev_PlayerDied() = default;

		int GetLivesLeft() const
		{
			return m_LivesLeft;
		}

		GameObject* GetPlayer() { return m_pObject; }

	private:
		int m_LivesLeft;
		GameObject* m_pObject;
	};
}