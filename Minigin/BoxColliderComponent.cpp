#include "BoxColliderComponent.h"
#include "GameObject.h"

aze::BoxColliderComponent::BoxColliderComponent(GameObject* pParent, const Rectf& hitbox)
	:Component(pParent)
	,m_Rect{hitbox}
{
}

aze::BoxColliderComponent::~BoxColliderComponent()
{
}

const aze::Rectf& aze::BoxColliderComponent::GetRect() const
{
	return m_Rect;
}

aze::Rectf& aze::BoxColliderComponent::GetRect()
{
	return m_Rect;
}

void aze::BoxColliderComponent::SetRect(const Rectf& rect)
{
	m_Rect = rect;
}

// Get Rect in world
aze::Rectf aze::BoxColliderComponent::GetHitbox() const
{
	Rectf r;
	auto worldPos = GetGameObject()->GetTransform().GetWorldPosition();
	r.width = m_Rect.width;
	r.height = m_Rect.height;
	r.topLeft.x = worldPos.x - r.width / 2;
	r.topLeft.y = worldPos.y - r.height / 2;
	return r;
}
