#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "Azemacros.h"

aze::GameObject::~GameObject() = default;

void aze::GameObject::Update(float elapsedSec)
{
	for (const auto& renderComps : m_pRenderComponents)
	{
		renderComps->Update(elapsedSec);
	}
	for (const auto& updateComps : m_pUpdateComponents)
	{
		updateComps->Update(elapsedSec);
	}
}

void aze::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	if (m_texture.get())
	{
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}
	for (const auto& renderComps : m_pRenderComponents)
	{
		renderComps->Render();
	}
}

void aze::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void aze::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
