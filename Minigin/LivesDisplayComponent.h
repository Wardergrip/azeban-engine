#pragma once
#include "Component.h"
#include "Observer.h"
#include "Event.h" 
namespace aze
{
	class TextObject;

	class LivesDisplayComponent : public Component, public Observer<Ev_PlayerDied>
	{
	public:
		LivesDisplayComponent(std::weak_ptr<GameObject> pParentGameObject, std::weak_ptr<TextObject> pTextRenderer)
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
		std::weak_ptr<TextObject> m_pTextRenderer;
	};
}

