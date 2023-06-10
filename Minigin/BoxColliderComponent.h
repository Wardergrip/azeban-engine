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
			,m_IsStatic{false}
			,m_ColliderLayer{ globals::L_DEFAULT }
			,m_ColliderMask{ globals::M_DEFAULT }
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
			std::cout << this << " " << m_Rect.topLeft.x << " , " << m_Rect.topLeft.y << "\n";
		}

		const Rect& GetHitbox() const { return m_Rect; }
		void SetStatic(bool state) { m_IsStatic = state; }
		bool IsStatic() const { return m_IsStatic; }
		ColliderLayer GetLayer() const { return m_ColliderLayer; }
		ColliderMask GetMask() const { return m_ColliderMask; }
		void SetLayer(ColliderLayer layer) { m_ColliderLayer = layer; }
		void SetMask(ColliderMask mask) { m_ColliderMask = mask; }

		bool ShouldCollide(ColliderLayer otherLayer)
		{
			return (otherLayer & m_ColliderMask) != 0;
		}
		ColliderMask AddLayerToMask(ColliderLayer layer)
		{
			m_ColliderMask |= layer;
			return m_ColliderMask;
		}
		ColliderMask RemoveLayerFromMask(ColliderLayer layer)
		{
			m_ColliderMask &= ~layer;
			return m_ColliderMask;
		}

	private:
		Rect m_Rect;
		bool m_IsStatic;
		ColliderLayer m_ColliderLayer;
		ColliderMask m_ColliderMask;
	};
}