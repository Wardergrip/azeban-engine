#pragma once
#include "Component.h"
#include "Observer.h"
#include "Event.h" 
namespace aze
{
	class TextObject;

	class ScoreDisplayComponent : public Component, public Observer<Ev_AddScore>
	{
	public:
		ScoreDisplayComponent(GameObject* pParentGameObject, TextObject* pTextRenderer)
			:Component{ pParentGameObject }
			, m_pTextRenderer{ pTextRenderer }
		{
		}
		ScoreDisplayComponent(ScoreDisplayComponent&& component) = default;
		ScoreDisplayComponent(const ScoreDisplayComponent& component) = default;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&& component) = default;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent& component) = default;
		virtual ~ScoreDisplayComponent() = default;

		virtual void OnNotify(Ev_AddScore* event) override;
	private:
		TextObject* m_pTextRenderer;
	};
}



