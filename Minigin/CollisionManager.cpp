#include "CollisionManager.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include <iostream>
#include "Renderer.h"

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

		size_t amountOfRights{ 0 };
		size_t amountOfBelow{ 0 };
		for (const auto& collider : colliding)
		{
			// Source: https://github.com/BramVernimmen/Prog4_Engine/blob/main/Minigin/CollisionManager.cpp
			const auto& otherHitBox{ collider->GetHitbox() };
			const bool otherIsRight{ hitBox.topLeft.x <= otherHitBox.topLeft.x };
			const bool otherIsUnder{ hitBox.topLeft.y <= otherHitBox.topLeft.y };

			float offsetX{ 0 };
			float offsetY{ 0 };

			if (otherIsRight)
			{
				offsetX = otherHitBox.topLeft.x - (hitBox.topLeft.x + hitBox.width);
				++amountOfRights;
			}
			else
			{
				offsetX = (hitBox.topLeft.x - (otherHitBox.topLeft.x + otherHitBox.width)) * -1;
			}

			if (otherIsUnder)
			{
				offsetY = otherHitBox.topLeft.y - (hitBox.topLeft.y + hitBox.height);
				++amountOfBelow;
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

			Ev_Collision collisionE{ pBoxCollider,collider };
			pBoxCollider->m_OnCollisionEvent.NotifyObservers(&collisionE);
		}

		// Make sure we won't overcorrect too much
		{
			const float hitsAmountRatio{ 1.f / std::max(colliding.size(),static_cast<size_t>(1)) };
			totalOffsetX *= hitsAmountRatio;
			totalOffsetY *= hitsAmountRatio;
		}
		const glm::vec3& localPos{ pBoxCollider->GetGameObject()->GetTransform().GetLocalPosition()};
		pBoxCollider->GetGameObject()->GetTransform().SetPosition(localPos.x + totalOffsetX, localPos.y + totalOffsetY);

		auto pRigidbody = pBoxCollider->GetGameObject()->GetComponent<RigidbodyComponent>();
		if (!pRigidbody) return;
		// Rigidbody
		if (pRigidbody->IsOnGround())
		{
			glm::vec3 point{};
			point.x = hitBox.GetMiddle().x;
			point.y = hitBox.topLeft.y + hitBox.height + 2.f;
			bool found{ false };
			for (const auto& otherBoxCollider : m_BoxColliders)
			{
				if (otherBoxCollider == pBoxCollider) continue;
				if (otherBoxCollider->GetHitbox().IsOverlapping(point))
				{
					found = true;
					break;
				}
			}
			if (!found) pRigidbody->SetIsOnGround(false);
			if (pRigidbody->IsOnGround()) return;
		}

		auto vel = pRigidbody->GetVelocity();
		if ((amountOfBelow == colliding.size() || (amountOfBelow >= amountOfRights && amountOfRights > 0)) && colliding.size() > 1 && colliding.size() < 6)
		{
			vel.y = 0.0f;
			pRigidbody->SetIsOnGround(true);
		}
		else if (colliding.size() == 6 && vel.y < 0 && amountOfBelow > 3)
		{
			vel.y = 0.0f;
			pRigidbody->SetIsOnGround(true);
		}

		/*if ((amountOfBelow == 0 || colliding.size() == 6) && vel.y >= 0.0f)
		{
			vel.y = 0.0f;
		}*/


		// make sure we stop moving when hitting the lowest side of a tile, while keep moving if we are higher up.
		if (pRigidbody->IsOnGround() || (colliding.size() == 1 && amountOfBelow == 0 && (hitBox.topLeft.y < colliding.front()->GetHitbox().topLeft.y + colliding.front()->GetHitbox().width - 1)))
		{
			vel.x = 0.0f;
		}


		// set velocity
		pRigidbody->SetVelocity(vel);
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
		if (!pBoxCollider->ShouldCollide(pOtherBoxCollider->GetLayer())) continue;

		if (hitbox.IsOverlapping(pOtherBoxCollider->GetHitbox()))
		{
			colliding.emplace_back(pOtherBoxCollider);
		}
	}

	return std::move(colliding);
}
