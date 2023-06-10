#pragma once
#include <Component.h>
#include <BoxColliderComponent.h>
#include <RigidbodyComponent.h>
#include "ColliderLayers.h"

namespace aze
{
	class LandOnPlatformComponent final : public Component
	{
	public:
		LandOnPlatformComponent(GameObject* pParent, BoxColliderComponent* pBoxCollider, RigidbodyComponent* pRigidbody)
			:Component{pParent}
			,m_pBoxCollider{pBoxCollider}
			,m_pRigidbody{pRigidbody}
		{}
		virtual ~LandOnPlatformComponent() = default;

		virtual void FixedUpdate() override
		{
			if (m_pRigidbody->GetVelocity().y < 0.f)
			{
				m_pBoxCollider->AddLayerToMask(layers::L_PLATFORM);
			}
		}

	private:
		BoxColliderComponent* m_pBoxCollider;
		RigidbodyComponent* m_pRigidbody;
	};
}