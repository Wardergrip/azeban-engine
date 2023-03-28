#include "MovementComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "GameTime.h"

aze::MovementComponent::MovementComponent(std::weak_ptr<GameObject> pParentGameObject)
	:Component(pParentGameObject)
{
}

void aze::MovementComponent::Move(const glm::vec3& dir, float speed)
{
	Transform& transform{ GetGameObject().lock()->GetTransform()};

	glm::vec3 newPos{ transform.GetLocalPosition() };
	newPos += dir * speed * GameTime::GetInstance().GetElapsed();

	transform.SetPosition(newPos);
}
