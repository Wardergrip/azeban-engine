#include "TextureObject.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "RenderComponent.h"

aze::TextureObject::TextureObject(GameObject* pParentGameObject, const std::string& fileName)
	:Component(pParentGameObject)
	,m_pTexture{ nullptr }
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
	auto renderComp = GetGameObject()->GetComponent<RenderComponent>();
	if (renderComp == nullptr)
	{
		throw missing_component();
	}
	renderComp->AddTexture(m_pTexture);
}

aze::TextureObject& aze::TextureObject::SetTexture(const std::string& fileName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
	return *this;
}

aze::Texture2D* aze::TextureObject::GetTexture() const
{
	return m_pTexture.get();
}
