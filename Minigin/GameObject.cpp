#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "Azemacros.h"

aze::GameObject::GameObject()
	:m_pParent{}
	,m_pChildren{}
	,m_IsMarkedForDestroy{false}
	,m_pComponents{}
	,m_Transform{nullptr}
{
}

aze::GameObject::~GameObject() = default;

bool aze::GameObject::IsMarkedForDestroy() const
{
	return m_IsMarkedForDestroy;
}

void aze::GameObject::Destroy(GameObject* pGameObject)
{
	// STATIC FUNCTION
	pGameObject->m_IsMarkedForDestroy = true;
}

void aze::GameObject::Update(float elapsedSec)
{
	for (auto& comp : m_pComponents)
	{
		comp->Update(elapsedSec);
	}
}

void aze::GameObject::Render() const
{
	for (const auto& comp : m_pComponents)
	{
		comp->Render();
	}
}

void aze::GameObject::OnGUI()
{
	for (const auto& pComp : m_pComponents)
	{
		pComp->OnGUI();
	}
}

void aze::GameObject::SetPosition(float x, float y)
{
	GetTransform().SetPosition(x, y, 0.0f);
}

aze::GameObject& aze::GameObject::AddChild(std::weak_ptr<aze::GameObject> child)
{
	auto pChild = child.lock();
	auto childParent = pChild->GetParent();
	auto pChildParent = childParent.lock();
	if (pChildParent.get())
	{
		pChildParent->RemoveChild(child);
	}
	if (pChild.get() == nullptr)
	{
		throw aze::child_is_nullptr();
	}
	pChild->m_pParent = weak_from_this();
	m_pChildren.emplace_back(pChild);
	return *this;
}

aze::GameObject& aze::GameObject::RemoveChild(std::weak_ptr<aze::GameObject> child)
{
	auto pChild = child.lock();
	if (pChild.get() == nullptr)
	{
		throw aze::child_is_nullptr();
	}
	auto findChild = [&](const std::weak_ptr<GameObject>& ptr1) { return ptr1.lock() == pChild; };
	if (std::find_if(m_pChildren.begin(), m_pChildren.end(), findChild) == m_pChildren.end())
	{
		throw aze::wrong_parent();
	}

	for (auto it = m_pChildren.begin(); it != m_pChildren.end(); ++it) 
	{
		std::weak_ptr pThisChild{ *it };
		if (pThisChild.lock() == pChild) 
		{
			m_pChildren.erase(it);
			break;
		}
	}
	pChild->GetParent().reset();
	return *this;
}

aze::GameObject& aze::GameObject::SetParent(std::weak_ptr<GameObject> pParent, bool worldPositionStays)
{
	auto newParent = pParent.lock();
	// If we have a parent
	if (!m_pParent.expired())
	{
		// Remove ourselves from their children
		m_pParent.lock()->RemoveChild(weak_from_this());
	}
	// Set new parent
	m_pParent = pParent;

	auto transform = GetTransform();
	// If our parent is not existant
	if (m_pParent.expired())
	{
		// Our local = world since our parent is the scene.
		transform.SetPosition(transform.GetWorldPosition());
	}
	else
	{
		// Add ourselves as child to our parent
		newParent->m_pChildren.push_back(weak_from_this());
		if (worldPositionStays)
		{
			transform.SetPosition(transform.GetLocalPosition() - m_pParent.lock()->GetTransform().GetWorldPosition());
		}
		else
		{
			transform.SetWorldPosDirty();
		}
	}

	return *this;
}

aze::GameObject& aze::GameObject::SetParent(std::nullptr_t)
{
	// If we have no parent, we don't have to do anything
	if (m_pParent.expired())
	{
		return *this;
	}

	// Remove ourselves from their children
	m_pParent.lock()->RemoveChild(weak_from_this());

	m_pParent.reset();

	auto transform = GetTransform();
	// Our local = world since our parent is the scene.
	transform.SetPosition(transform.GetWorldPosition());
	return *this;
}

std::weak_ptr<aze::GameObject> aze::GameObject::GetParent() const
{
	return m_pParent;
}

size_t aze::GameObject::GetChildCount() const
{
	return m_pChildren.size();
}

std::weak_ptr<aze::GameObject> aze::GameObject::GetChildAt(size_t index) const
{
	return m_pChildren.at(index);
}

const std::vector<std::weak_ptr<aze::GameObject>>& aze::GameObject::GetChildren() const
{
	return m_pChildren;
}

const aze::Transform& aze::GameObject::GetTransform() const
{
	return *m_Transform;
}

aze::Transform& aze::GameObject::GetTransform()
{
	if (!m_Transform || !m_Transform.get())
	{
		m_Transform = std::make_unique<Transform>(weak_from_this());
	}
	return *m_Transform;
}
