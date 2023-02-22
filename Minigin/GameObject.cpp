#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

aze::GameObject::~GameObject() = default;

void aze::GameObject::Update(){}

void aze::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void aze::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void aze::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
