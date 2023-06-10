#include "RigidbodyComponent.h"
#include "GameObject.h"
#include "GameTime.h"
#include <iostream>

float aze::RigidbodyComponent::s_Gravity{ -10.f };
float aze::RigidbodyComponent::s_MaxFallVelocity{ -20.f };

aze::RigidbodyComponent::RigidbodyComponent(GameObject* pParent)
	:Component{pParent}
	,m_Transform{pParent->GetTransform()}
	,m_IsOnGround{false}
{
}

void aze::RigidbodyComponent::FixedUpdate()
{
	const auto& localPos{ m_Transform.GetLocalPosition() };
	m_Transform.SetPosition(m_Velocity.x + localPos.x, localPos.y - m_Velocity.y);
	if (m_IsOnGround) return;
	if (m_Velocity.y < s_MaxFallVelocity) return;
	m_Velocity.y += s_Gravity * GameTime::GetInstance().GetFixedTimeStep();
}
