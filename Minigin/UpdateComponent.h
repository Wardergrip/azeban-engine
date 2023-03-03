#pragma once
#include "Component.h"
namespace aze
{
	class UpdateComponent : public Component
	{
	public:
		UpdateComponent(std::weak_ptr<GameObject> pParentGameObject) :Component{ pParentGameObject } {}
		UpdateComponent(UpdateComponent&& component) = default;
		UpdateComponent(const UpdateComponent& component) = default;
		UpdateComponent& operator=(UpdateComponent&& component) = default;
		UpdateComponent& operator=(const UpdateComponent& component) = default;
		virtual ~UpdateComponent() = default;

		virtual void Update(float elapsedSec) = 0;
	};
}