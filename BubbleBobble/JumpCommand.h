#pragma once
#include <Command.h>
#include <RigidbodyComponent.h>
#include <BoxColliderComponent.h>
#include "ColliderLayers.h"

namespace aze
{
	class JumpCommand final : public Command
	{
	public:
		JumpCommand(RigidbodyComponent* pRigidbody, float jumpForce)
			:m_pRigidbody{pRigidbody}
			,m_JumpForce{jumpForce}
		{}
		virtual ~JumpCommand() = default;

		void Execute() override
		{
			if (m_pRigidbody->IsOnGround() && m_pRigidbody->GetVelocity().y <= FLT_EPSILON)
			{
				glm::vec3 jump{};
				jump.y = m_JumpForce;
				m_pRigidbody->AddVelocity(jump);
				m_pRigidbody->SetIsOnGround(false);
				auto pBoxColl = m_pRigidbody->GetGameObject()->GetComponent<BoxColliderComponent>();
				if (pBoxColl) pBoxColl->RemoveLayerFromMask(layers::L_PLATFORM);
			}
		}
	private:
		RigidbodyComponent* m_pRigidbody;
		const float m_JumpForce;
	};
}