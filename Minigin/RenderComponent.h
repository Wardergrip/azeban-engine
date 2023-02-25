#pragma once
#include "UpdateComponent.h"
namespace aze
{
	class RenderComponent : public UpdateComponent
	{
	public:
		RenderComponent() = default;
		RenderComponent(std::weak_ptr<GameObject> pParent) :UpdateComponent{ pParent } {}
		RenderComponent(RenderComponent&& component) = default;
		RenderComponent(const RenderComponent& component) = default;
		RenderComponent& operator=(RenderComponent&& component) = default;
		RenderComponent& operator=(const RenderComponent& component) = default;
		virtual ~RenderComponent() = default;

		virtual void Render() const = 0;
	};
}

