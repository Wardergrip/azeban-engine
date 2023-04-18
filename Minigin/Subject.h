#pragma once
#include <vector>
#include "Observer.h"
namespace aze
{
	template <typename T>
	class Subject final
	{
	public:
		Subject() = default;

		void AddObserver(Observer<T>* pObserver)
		{
			m_pObservers.push_back(pObserver);
		}

		void RemoveObserver(Observer<T>* pObserver)
		{
			m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver), m_pObservers.end());
		}

		void NotifyObservers(T* data)
		{
			for (auto pObs : m_pObservers)
			{
				pObs->OnNotify(data);
			}
		}

	private:
		std::vector<Observer<T>*> m_pObservers{};
	};
}