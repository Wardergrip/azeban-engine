#include "Transform.h"
#include "GameObject.h"

aze::Transform::Transform(GameObject* pParent, const glm::vec3& pos)
	:Component(pParent)
	, m_LocalPosition{ pos }
	, m_WorldPosition{}
	, m_IsWorldPosDirty{ true }
{
}

aze::Transform::Transform(GameObject* pParent, float x, float y, float z)
	:Transform(pParent, glm::vec3{x,y,z})
{
}

aze::Transform::Transform(GameObject* pParent)
	:Transform{ pParent, glm::vec3{0,0,0} }
{
}

void aze::Transform::SetPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetWorldPosDirty();
}

void aze::Transform::SetPosition(float x, float y, float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
	SetWorldPosDirty();
}

const glm::vec3& aze::Transform::GetWorldPosition()
{
	if (m_IsWorldPosDirty)
	{
		UpdateWorldPos();
	}
	return m_WorldPosition;
}

const glm::vec3& aze::Transform::GetLocalPosition() const
{
	return m_LocalPosition;
}

void aze::Transform::SetWorldPosDirty()
{
	const auto children = GetGameObject()->GetChildren();
	for (auto child : children)
	{
		child->GetTransform().SetWorldPosDirty();
	}
	m_IsWorldPosDirty = true;
}

void aze::Transform::UpdateWorldPos()
{
	const auto gameObjectParent = GetGameObject()->GetParent();
	if (gameObjectParent == nullptr)
	{
		m_WorldPosition = m_LocalPosition;
	}
	else
	{
		const auto parentPosition = gameObjectParent->GetTransform().GetWorldPosition();
		m_WorldPosition = parentPosition + m_LocalPosition;
	}
	m_IsWorldPosDirty = false;
}
