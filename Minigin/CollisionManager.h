#pragma once
#include "Singleton.h"
#include <vector>

namespace aze
{
	class BoxColliderComponent;
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		virtual ~CollisionManager() = default;

		void AddCollider(BoxColliderComponent* pCollider);
		void RemoveCollider(BoxColliderComponent* pCollider);

		void FixedUpdate();
	protected:
		friend Singleton<CollisionManager>;
		CollisionManager() = default;

	private:
		std::vector<BoxColliderComponent*> GetColliding(BoxColliderComponent* pBoxCollider) const;
		std::vector<BoxColliderComponent*> m_BoxColliders;
	};
}
