#pragma once
#include <Component.h>
#include "MovementComponent.h"
#include "GameManager.h"
#include "GameObject.h"

namespace aze
{
	class EnemyMovementComponent final : public Component
	{
	public:
		EnemyMovementComponent(GameObject* pParent, MovementComponent* pMovementComp, float speed)
			:Component{pParent}
			, m_pMovementComp{pMovementComp}
			, m_Speed{speed}
		{
		}

		virtual void Update() override
		{
			GameObject* bob = GameManager::GetInstance().GetBobPlayer();
			GameObject* bub = GameManager::GetInstance().GetBubPlayer();
			const auto& thisPos = GetGameObject()->GetTransform().GetWorldPosition();
			float bobDistance{ FLT_MAX };
			float bubDistance{ FLT_MAX };

			if (bob)
			{
				const auto& bobPos = bob->GetTransform().GetWorldPosition();
				bobDistance = (bobPos.x - thisPos.x) * (bobPos.x - thisPos.x);
				bobDistance += (bobPos.y - thisPos.y) * (bobPos.y - thisPos.y);
			}
			if (bub)
			{
				const auto& bubPos = bub->GetTransform().GetWorldPosition();
				bubDistance = (bubPos.x - thisPos.x) * (bubPos.x - thisPos.x);
				bubDistance += (bubPos.y - thisPos.y) * (bubPos.y - thisPos.y);
			}
			GameObject* target = (bobDistance < bubDistance) ? bob : bub;
			glm::vec3 dir{};
			dir.x = (target->GetTransform().GetWorldPosition().x < thisPos.x) ? -1.f : 1.f;
			m_pMovementComp->Move(dir, m_Speed);
		}

	private:
		MovementComponent* m_pMovementComp;
		float m_Speed;
	};
}