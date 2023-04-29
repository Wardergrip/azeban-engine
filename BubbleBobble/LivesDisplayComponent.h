#pragma once
#include "Component.h"
#include "Observer.h"
#include "Ev_PlayerDied.h" 
namespace aze
{
	class TextObject;

	class LivesDisplayComponent : public Component, public Observer<Ev_PlayerDied>
	{
	public:
		LivesDisplayComponent(GameObject* pParentGameObject, TextObject* pTextRenderer)
			:Component{ pParentGameObject }
			, m_pTextRenderer{ pTextRenderer }
		{
		}
		LivesDisplayComponent(LivesDisplayComponent&& component) = default;
		LivesDisplayComponent(const LivesDisplayComponent& component) = default;
		LivesDisplayComponent& operator=(LivesDisplayComponent&& component) = default;
		LivesDisplayComponent& operator=(const LivesDisplayComponent& component) = default;
		virtual ~LivesDisplayComponent() = default;

		virtual void OnNotify(Ev_PlayerDied* event) override;
	private:
		TextObject* m_pTextRenderer;
	};
}

