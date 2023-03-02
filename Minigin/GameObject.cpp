#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "Azemacros.h"

aze::GameObject::~GameObject() = default;

bool aze::GameObject::IsMarkedForDestroy() const
{
	return false;
}

void aze::GameObject::Destroy(GameObject* pGameObject)
{
	// STATIC FUNCTION
	pGameObject->m_IsMarkedForDestroy = true;
}

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
	for (const auto& renderComps : m_pRenderComponents)
	{
		renderComps->Render();
	}
}

void aze::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

const aze::Transform& aze::GameObject::GetTransform() const
{
	return m_transform;
}

aze::Transform& aze::GameObject::GetTransform()
{
	return m_transform;
}
