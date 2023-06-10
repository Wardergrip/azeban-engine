#pragma once
#include <memory>
#include <stdexcept>
#include "Subject.h"
#include "Ev_Destroy.h"

namespace aze
{
	class GameObject;

	class missing_component : public std::runtime_error
	{
	public:
		missing_component() :runtime_error(what()) {}
		const char* what() const override
		{
			return "A crucial component is not present";
		}
	};

	class Component
	{
	public:
		Component(GameObject* pParent):m_pParentGameObject{pParent}{}
		Component(Component&& component) = delete;
		Component(const Component& component) = delete;
		Component& operator=(Component&& component) = delete;
		Component& operator=(const Component& component) = delete;
		virtual ~Component()
		{
			Ev_Destroy<Component> destroyE{this};
			m_OnDestroyEvent.NotifyObservers(&destroyE);
		}

		virtual void Start(){}
		virtual void Render() const{}
		virtual void Update(){}
		virtual void FixedUpdate(){}
		virtual void OnGUI(){}

		GameObject* GetGameObject() const { return m_pParentGameObject; }
		void SubscribeOnDestroyEvent(Observer<Ev_Destroy<Component>>* pObserver)
		{
			m_OnDestroyEvent.AddObserver(pObserver);
		}
		void UnsubscribeOnDestroyEvent(Observer<Ev_Destroy<Component>>* pObserver)
		{
			m_OnDestroyEvent.RemoveObserver(pObserver);
		}
	private:
		GameObject* m_pParentGameObject;
		Subject<Ev_Destroy<Component>> m_OnDestroyEvent;
	};
}