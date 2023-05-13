#include "CollisionManager.h"
#include "BoxColliderComponent.h"
#include "GameObject.h"

void aze::CollisionManager::RegisterCollider(BoxColliderComponent* pCollider)
{
	if (pCollider == nullptr)
	{
		throw collider_is_null();
	}

	// If we can find the pointer, throw an error
	if (std::find(m_pColliders.begin(), m_pColliders.end(), pCollider) != m_pColliders.end())
	{
		throw collider_already_registered();
	}

	m_pColliders.emplace_back(pCollider);
}

void aze::CollisionManager::UnregisterCollider(BoxColliderComponent* pCollider)
{
	if (pCollider == nullptr)
	{
		throw collider_is_null();
	}

	auto it = std::find(m_pColliders.begin(), m_pColliders.end(), pCollider);
	// If we cant find the pointer, throw an error
	if (it == m_pColliders.end())
	{
		throw collider_not_registered();
	}

	m_pColliders.erase(it);
}

void aze::CollisionManager::Update()
{
	std::vector<BoxColliderComponent*> pOverlapping;
	for (auto pCollider : m_pColliders)
	{
		if (pCollider->IsStatic())
		{
			continue;
		}
		pOverlapping.clear();
		for (auto pColliderToCheck : m_pColliders)
		{
			if (pCollider == pColliderToCheck)
			{
				continue;
			}
			if (pCollider->GetRect().IsOverlapping(pColliderToCheck->GetRect()))
			{
				pOverlapping.emplace_back(pColliderToCheck);
			}
		}

		glm::vec3 offset{};
		auto thisHitBox = pCollider->GetHitbox();

		for (auto pOverlappingCollider : pOverlapping)
		{
			offset += pOverlappingCollider->GetHitbox().Middle() - thisHitBox.Middle();
		}
		offset /= pOverlapping.size();
		
		auto localPos = pCollider->GetGameObject()->GetTransform().GetLocalPosition();
		pCollider->GetGameObject()->GetTransform().SetPosition(localPos.x + offset.x, localPos.y + offset.y);
	}
}
