#pragma once
#include "Component.h"
#include "Subject.h"
#include "Ev_PlayerDied.h"
namespace aze
{
	class LivesComponent : public Component
	{
	public:
		LivesComponent(GameObject* pParentGameObject, int lives = 3)
			:Component{ pParentGameObject }
			,m_pSubject{std::make_unique<Subject<Ev_PlayerDied>>()}
			,m_Lives{lives}
			,m_IsInvincible{false}
		{
		}
		LivesComponent(LivesComponent&& component) = default;
		LivesComponent(const LivesComponent& component) = default;
		LivesComponent& operator=(LivesComponent&& component) = default;
		LivesComponent& operator=(const LivesComponent& component) = default;
		virtual ~LivesComponent() = default;

		void AddObserver(Observer<Ev_PlayerDied>* pObserver)
		{
			m_pSubject->AddObserver(pObserver);
		}
		void RemoveObserver(Observer<Ev_PlayerDied>* pObserver)
		{
			m_pSubject->RemoveObserver(pObserver);
		}

		void RemoveLife()
		{
			--m_Lives;
			std::unique_ptr<Ev_PlayerDied> playerDied = std::make_unique<Ev_PlayerDied>(m_Lives);
			m_pSubject->NotifyObservers(playerDied.get());
		}

		int GetLivesAmount() const 
		{ 
			return m_Lives; 
		}

		void SetIsInvincible(bool state) { m_IsInvincible = state; }
		bool IsInvincible() const { return m_IsInvincible; }
	private:
		std::unique_ptr<Subject<Ev_PlayerDied>> m_pSubject;
		int m_Lives;
		bool m_IsInvincible;
	};
}

