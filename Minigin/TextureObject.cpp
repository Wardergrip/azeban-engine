#include "TextureObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

aze::TextureObject::TextureObject(std::weak_ptr<GameObject> pParent, const std::string& fileName)
	:RenderComponent(pParent)
	,m_pTexture{ nullptr }
	,m_Transform{}
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
}

aze::TextureObject* aze::TextureObject::SetTexture(const std::string& fileName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
	return this;
}

std::weak_ptr<aze::Texture2D> aze::TextureObject::GetTexture() const
{
	return m_pTexture;
}

aze::TextureObject& aze::TextureObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.f);
	return *this;
}

void aze::TextureObject::Render() const
{
	const auto& pos = m_Transform.GetPosition();
	if (m_pTexture.get())
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void aze::TextureObject::Update(float)
{
}
