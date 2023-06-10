#pragma once
#include "Component.h"
#include "Rect.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include <iostream>

namespace aze
{
	class BoxColliderComponent final : public Component
	{
	public:
		BoxColliderComponent(GameObject* pParent)
			:Component{pParent}
			,m_Rect{ 24.f,24.f }
		{
			CollisionManager::GetInstance().AddCollider(this);
		}
		virtual ~BoxColliderComponent()
		{
			CollisionManager::GetInstance().RemoveCollider(this);
		}

		virtual void Update() override
		{
			m_Rect.topLeft = GetGameObject()->GetTransform().GetWorldPosition();
		}

		const Rect& GetHitbox() const { return m_Rect; }

	private:
		Rect m_Rect;
	};
}