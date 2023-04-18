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
		ScoreDisplayComponent(std::weak_ptr<GameObject> pParentGameObject, std::weak_ptr<TextObject> pTextRenderer)
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
		std::weak_ptr<TextObject> m_pTextRenderer;
	};
}



