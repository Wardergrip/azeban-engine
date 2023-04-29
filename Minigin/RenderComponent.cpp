#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"

aze::RenderComponent::RenderComponent(GameObject* pParentGameObject)
	:Component(pParentGameObject)
	,m_pTextures{}
{
}

void aze::RenderComponent::AddTexture(std::weak_ptr<Texture2D> pTexture)
{
	m_pTextures.push_back(pTexture);
}

void aze::RenderComponent::RemoveTexture(std::weak_ptr<Texture2D> pTexture)
{
	auto target = pTexture.lock();
	for (auto it = m_pTextures.begin(); it != m_pTextures.end(); ++it)
	{
		std::weak_ptr pThisChild{ *it };
		if (pThisChild.lock() == target)
		{
			m_pTextures.erase(it);
			break;
		}
	}
}

void aze::RenderComponent::Render() const
{
	const auto& pos = GetGameObject()->GetTransform().GetWorldPosition();
	for (const auto& texture : m_pTextures)
	{
		auto pTexture = texture.lock();
		if (!texture.expired() && pTexture.get() != nullptr)
		{
			Renderer::GetInstance().RenderTexture(*pTexture, pos.x, pos.y);
		}
	}
}
