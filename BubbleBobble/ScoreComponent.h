#pragma once
#include "Component.h"
#include "Subject.h"
#include "Ev_AddScore.h"
namespace aze
{
	class ScoreComponent : public Component
	{
	public:
		ScoreComponent(GameObject* pParentGameObject, int score = 0)
			:Component{ pParentGameObject }
			, m_pSubject{ std::make_unique<Subject<Ev_AddScore>>() }
			, m_Score{ score }
		{
		}
		ScoreComponent(ScoreComponent&& component) = default;
		ScoreComponent(const ScoreComponent& component) = default;
		ScoreComponent& operator=(ScoreComponent&& component) = default;
		ScoreComponent& operator=(const ScoreComponent& component) = default;
		virtual ~ScoreComponent() = default;

		void AddObserver(Observer<Ev_AddScore>* pObserver)
		{
			m_pSubject->AddObserver(pObserver);
		}
		void RemoveObserver(Observer<Ev_AddScore>* pObserver)
		{
			m_pSubject->RemoveObserver(pObserver);
		}

		void AddScore(int score)
		{
			m_Score += score;
			std::unique_ptr<Ev_AddScore> addScore = std::make_unique<Ev_AddScore>(m_Score);
			m_pSubject->NotifyObservers(addScore.get());
		}

		int GetScoreAmount() const
		{
			return m_Score;
		}
	private:
		std::unique_ptr<Subject<Ev_AddScore>> m_pSubject;
		int m_Score;
	};
}
