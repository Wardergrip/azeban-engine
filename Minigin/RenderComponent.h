#pragma once
#include "UpdateComponent.h"
#include <memory>

namespace aze
{
	class RenderComponent : public UpdateComponent
	{
	public:
		RenderComponent(std::weak_ptr<GameObject> pParentGameObject) :UpdateComponent{ pParentGameObject } {}
		RenderComponent(RenderComponent&& component) = default;
		RenderComponent(const RenderComponent& component) = default;
		RenderComponent& operator=(RenderComponent&& component) = default;
		RenderComponent& operator=(const RenderComponent& component) = default;
		virtual ~RenderComponent() = default;

		virtual void Render() const = 0;
	};
}

