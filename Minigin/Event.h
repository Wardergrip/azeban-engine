#pragma once
#include <string>
namespace aze
{
	class Event
	{
	public:
		Event() = default;
		Event(const std::string& eventName) 
		{ 
			m_EventName = eventName; 
		}
		virtual ~Event() = default;

		const std::string& GetName() const
		{
			return m_EventName;
		}
	private:
		std::string m_EventName{};
	};

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