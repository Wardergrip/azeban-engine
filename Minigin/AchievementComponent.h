#pragma once
#include "Component.h"
#include "Observer.h"
#include "Event.h"
namespace aze
{
	class AchievementComponent : public Component, public Observer<Ev_AddScore>
	{
	public:
		AchievementComponent(std::weak_ptr<GameObject> pParentGameObject)
			:Component{ pParentGameObject }
		{
		}
		AchievementComponent(AchievementComponent&& component) = default;
		AchievementComponent(const AchievementComponent& component) = default;
		AchievementComponent& operator=(AchievementComponent&& component) = default;
		AchievementComponent& operator=(const AchievementComponent& component) = default;
		virtual ~AchievementComponent() = default;

		virtual void OnNotify(Ev_AddScore* event) override;
	};
}

