#pragma once
#include <queue>
#include <memory>
#include "Singleton.h"
#include "Event.h" 
#include "Observer.h"
namespace aze
{
	class EventQueue final : Singleton<EventQueue>
	{
	public:
		EventQueue() = default;
		~EventQueue() = default;
		EventQueue(EventQueue&&) = delete;
		EventQueue(const EventQueue&) = delete;
		const EventQueue& operator= (const EventQueue&) = delete;
		const EventQueue& operator= (const EventQueue&&) = delete;

		void AddEvent(std::unique_ptr<Event> pEvent);

		template <typename T>
		void AddListener(Observer<T>* pObserver)
		{
			m_pObservers.push_back(reinterpret_cast<Observer<void>>(pObserver));
		}
	private:
		std::queue<std::unique_ptr<Event>> m_pQueue{};
		std::vector<Observer<void>*> m_pObservers{};
	};
}

