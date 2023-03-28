#include "RevolutionComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "GameTime.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#include <iostream>

aze::RevolutionComponent::RevolutionComponent(std::weak_ptr<GameObject> pGameObjectParent, float radius, float speed)
	:Component(pGameObjectParent)
	,m_ParentGameObjectTransform{pGameObjectParent.lock()->GetTransform()}
	,m_Radius{radius}
	,m_Speed{speed}
	,m_RotationAngle{0}
{
}

void aze::RevolutionComponent::Update()
{
	m_RotationAngle += GameTime::GetInstance().GetElapsed() * m_Speed;
	// When frames are long, the rotationAngle is high and small steps might not make any impact.
	// The following lines make sure that m_RotationAngle stays small.
	const constexpr float twoPi = static_cast<float>(2 * M_PI);

	// The std::fmod function calculates the floating-point remainder of division 
	// and returns a result with the same sign as the dividend.
	// The std::fmod function takes care of wrapping the value of m_RotationAngle
	// within the range of [-twoPi, twoPi].
	m_RotationAngle = std::fmod(m_RotationAngle, twoPi);
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
