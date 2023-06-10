#pragma once
#include "Singleton.h"
#include <vector>

namespace aze
{
	typedef uint32_t ColliderLayer;
	typedef uint32_t ColliderMask;
	namespace globals
	{
		static constexpr ColliderLayer L_DEFAULT{ 0x0001 };
		static constexpr ColliderMask M_DEFAULT{ 0x0001 };
		static constexpr ColliderMask M_ALL{ 0xFFFF };
	}

	class BoxColliderComponent;
	class CollisionManager final
	{
	public:
		CollisionManager() = default;
		virtual ~CollisionManager() = default;

		void AddCollider(BoxColliderComponent* pCollider);
		void RemoveCollider(BoxColliderComponent* pCollider);

		void FixedUpdate();

	private:
		std::vector<BoxColliderComponent*> GetOverlapping(BoxColliderComponent* pBoxCollider) const;
		std::vector<BoxColliderComponent*> m_BoxColliders;
	};
}
