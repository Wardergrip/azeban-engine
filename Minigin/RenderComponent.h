#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <vector>
namespace aze
{
	class RenderComponent : public Component
	{
	public:
		RenderComponent(GameObject* pParentGameObject);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void AddTexture(std::weak_ptr<Texture2D> pTexture);
		void RemoveTexture(std::weak_ptr<Texture2D> pTexture);
		void Render() const override;

	private:
		std::vector<std::weak_ptr<Texture2D>> m_pTextures;
	};
}

