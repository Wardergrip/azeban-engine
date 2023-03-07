#include "TextureObject.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "RenderComponent.h"

aze::TextureObject::TextureObject(std::weak_ptr<GameObject> pParentGameObject, const std::string& fileName)
	:Component(pParentGameObject)
	,m_pTexture{ nullptr }
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
	auto renderComp = GetGameObject().lock()->GetComponent<RenderComponent>();
	if (renderComp.expired())
	{
		throw missing_component();
	}
	renderComp.lock()->AddTexture(m_pTexture);
}

aze::TextureObject& aze::TextureObject::SetTexture(const std::string& fileName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
	return *this;
}

std::weak_ptr<aze::Texture2D> aze::TextureObject::GetTexture() const
{
	return m_pTexture;
}
