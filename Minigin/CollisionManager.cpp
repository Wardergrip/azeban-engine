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
		for (auto& pOtherBoxCollider : m_BoxColliders)
		{
			if (pBoxCollider == pOtherBoxCollider) continue;
			if (pBoxCollider->GetHitbox().IsOverlapping(pOtherBoxCollider->GetHitbox()))
			{
				std::cout << "Overlapping!\n";
			}
			else
			{
				std::cout << "Not overlapping\n";
			}
		}
	}
}
