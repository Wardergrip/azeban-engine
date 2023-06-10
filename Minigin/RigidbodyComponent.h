#pragma once
#include "Component.h"
#include <glm/vec3.hpp>
#include "Transform.h"

namespace aze
{
	class RigidbodyComponent final : public Component
	{
	public:
		static float s_Gravity;
		static float s_MaxFallVelocity;

		RigidbodyComponent(GameObject* pParent);
		virtual ~RigidbodyComponent() = default;
		
		void SetIsOnGround(bool state) { m_IsOnGround = state; }
		bool IsOnGround() const { return m_IsOnGround; }
		void SetVelocity(const glm::vec3& velocity) { m_Velocity = velocity; }
		void AddVelocity(const glm::vec3& velocity) 
		{
			m_Velocity.x += velocity.x;
			m_Velocity.y += velocity.y;
			m_Velocity.z += velocity.z;
		}
		const glm::vec3& GetVelocity() const { return m_Velocity; }

		virtual void FixedUpdate() override;
	private:
		Transform& m_Transform;
		glm::vec3 m_Velocity;
		bool m_IsOnGround;
	};
}
