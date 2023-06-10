#include "CollisionManager.h"
#include "BoxColliderComponent.h"
#include <iostream>

void aze::CollisionManager::AddCollider(BoxColliderComponent* pCollider)
{
	m_BoxColliders.emplace_back(pCollider);
}

void aze::CollisionManager::RemoveCollider(BoxColliderComponent* pCollider)
{
	//m_BoxColliders.erase(std::remove(m_BoxColliders.begin(), m_BoxColliders.end(), pCollider), m_BoxColliders.end());
	pCollider;
}

void aze::CollisionManager::FixedUpdate()
{
	for (auto& pBoxCollider : m_BoxColliders)
	{
		if (pBoxCollider->IsStatic()) continue;
		std::vector<BoxColliderComponent*> colliding{GetColliding(pBoxCollider)};
		const auto& hitBox{ pBoxCollider->GetHitbox() };
		float totalOffsetX{ 0 };
		float totalOffsetY{ 0 };
		for (const auto& collider : colliding)
		{
			// Source: https://github.com/BramVernimmen/Prog4_Engine/blob/main/Minigin/CollisionManager.cpp
			const auto& otherHitBox{ collider->GetHitbox() };
			const bool hitIsLeft{ hitBox.topLeft.x <= otherHitBox.topLeft.x };
			const bool hitIsAbove{ hitBox.topLeft.y <= otherHitBox.topLeft.y };

			float offsetX{ 0 };
			float offsetY{ 0 };

			if (hitIsLeft)
			{
				offsetX = otherHitBox.topLeft.x - (hitBox.topLeft.x + hitBox.width);
			}
			else
			{
				offsetX = (hitBox.topLeft.x - (otherHitBox.topLeft.x + otherHitBox.width)) * -1;
			}

			if (hitIsAbove)
			{
				offsetY = otherHitBox.topLeft.y - (hitBox.topLeft.y + hitBox.height);
			}
			else
			{
				offsetY = (hitBox.topLeft.y - (otherHitBox.topLeft.y + otherHitBox.height)) * -1;
			}

			// Take the lowest offset, this is the shortest path to no longer overlap
			if (std::abs(offsetX) < std::abs(offsetY))
			{
				offsetY = 0;
			}
			else
			{
				offsetX = 0;
			}

			totalOffsetX += offsetX;
			totalOffsetY += offsetY;
		}

		// Make sure we won't overcorrect too much
		{
			const float hitsAmountRatio{ 1.f / std::max(colliding.size(),static_cast<size_t>(1)) };
			totalOffsetX *= hitsAmountRatio;
			totalOffsetY *= hitsAmountRatio;
		}
		const glm::vec3& localPos{ pBoxCollider->GetGameObject()->GetTransform().GetLocalPosition()};
		pBoxCollider->GetGameObject()->GetTransform().SetPosition(localPos.x + totalOffsetX, localPos.y + totalOffsetY);
	}
}

std::vector<aze::BoxColliderComponent*> aze::CollisionManager::GetColliding(BoxColliderComponent* pBoxCollider) const
{
	std::vector<BoxColliderComponent*> colliding;
	if (pBoxCollider == nullptr) return std::move(colliding);

	const auto& hitbox = pBoxCollider->GetHitbox();
	for (auto& pOtherBoxCollider : m_BoxColliders)
	{
		if (pBoxCollider == pOtherBoxCollider) continue;

		if (hitbox.IsOverlapping(pOtherBoxCollider->GetHitbox()))
		{
			colliding.emplace_back(pOtherBoxCollider);
		}
	}

	return std::move(colliding);
}
