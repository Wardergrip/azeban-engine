#pragma once
#include <Component.h>
#include <Observer.h>
#include <BoxColliderComponent.h>
#include "LivesComponent.h"
#include "GameManager.h"

namespace aze 
{
	class HitPlayerComponent final : public Component, public Observer<Ev_TriggerOverlap>
	{
	public:
		HitPlayerComponent(GameObject* pParent)
			:Component{ pParent }
		{
			GetGameObject()->GetComponent<BoxColliderComponent>()->SubscribeOnTriggerOverlap(this);
		}

		void OnNotify(Ev_TriggerOverlap* data)
		{
			static auto& gameManager = GameManager::GetInstance();
			auto objHit = data->GetColliderHit()->GetGameObject();
			if (objHit == gameManager.GetBobPlayer())
			{
				gameManager.GetBobPlayer()->GetComponent<LivesComponent>()->RemoveLife();
				return;
			}
			else if (objHit == gameManager.GetBubPlayer())
			{
				gameManager.GetBubPlayer()->GetComponent<LivesComponent>()->RemoveLife();
				return;
			}
		}
	};
}