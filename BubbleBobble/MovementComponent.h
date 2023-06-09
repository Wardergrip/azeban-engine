#pragma once
#include "Component.h"
#include <glm/glm.hpp>
namespace aze
{
	class MovementComponent : public Component<MovementComponent>
	{
	public:
		MovementComponent(GameObject* pParentGameObject);
		virtual ~MovementComponent() = default;
		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) = delete;

		void Move(const glm::vec3& dir, float speed);
	};
}

