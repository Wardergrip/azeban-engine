#include "RevolutionComponent.h"
#include "Transform.h"
#include "GameObject.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>

aze::RevolutionComponent::RevolutionComponent(std::weak_ptr<GameObject> pGameObjectParent, float radius, float speed)
	:UpdateComponent(pGameObjectParent)
	,m_ParentGameObjectTransform{pGameObjectParent.lock()->GetTransform()}
	,m_Radius{radius}
	,m_Speed{speed}
	,m_RotationAngle{0}
{
}

void aze::RevolutionComponent::Update(float elapsedSec)
{
	m_RotationAngle += elapsedSec * m_Speed;
	// When frames are long, the rotationAngle is high and small steps might not make any impact.
	// The following lines make sure that m_RotationAngle stays small.
	const constexpr float twoPi = static_cast<float>(2 * M_PI);
	while (m_RotationAngle >= twoPi)
	{
		m_RotationAngle -= twoPi;
	}
	m_ParentGameObjectTransform.SetPosition(m_Radius * std::cosf(m_RotationAngle), m_Radius * std::sinf(m_RotationAngle));
}

aze::RevolutionComponent& aze::RevolutionComponent::SetRadius(float radius)
{
	m_Radius = radius;
	return *this;
}

aze::RevolutionComponent& aze::RevolutionComponent::SetSpeed(float speed)
{
	m_Speed = speed;
	return *this;
}
