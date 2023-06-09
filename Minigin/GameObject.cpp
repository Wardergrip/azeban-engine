#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Scene.h"

aze::GameObject::GameObject(Scene* pScene)
	:m_pParent{}
	,m_pChildren{}
	,m_IsMarkedForDestroy{false}
	,m_pComponents{}
	,m_Transform{nullptr}
	,m_pScene{pScene}
	,m_OnDestroyEvent{}
{
	assert(pScene != nullptr && "Scene is nullptr!");
}

aze::GameObject::~GameObject()
{
	Ev_Destroy<GameObject> destroyE{this};
	m_OnDestroyEvent.NotifyObservers(&destroyE);
}

bool aze::GameObject::IsMarkedForDestroy() const
{
	return m_IsMarkedForDestroy;
}

void aze::GameObject::Destroy(GameObject* pGameObject)
{
	// STATIC FUNCTION
	pGameObject->m_IsMarkedForDestroy = true;
}

void aze::GameObject::Start()
{
	for (auto& comp : m_pComponents)
	{
		comp->Start();
	}
	for (auto& child : m_pChildren)
	{
		if (child.get() == nullptr) continue;
		child->Start();
	}
}

void aze::GameObject::Update()
{
	for (auto& comp : m_pComponents)
	{
		comp->Update();
	}
	for (auto& child : m_pChildren)
	{
		if (child.get() == nullptr) continue;
		child->Update();
	}
	for (auto& child : m_pChildren)
	{
		if (child->IsMarkedForDestroy())
		{
			RemoveChild(child.get());
		}
	}
}

void aze::GameObject::Render() const
{
	for (const auto& comp : m_pComponents)
	{
		comp->Render();
	}
	for (auto& child : m_pChildren)
	{
		if (child.get() == nullptr) continue;
		child->Render();
	}
}

void aze::GameObject::OnGUI()
{
	for (const auto& pComp : m_pComponents)
	{
		pComp->OnGUI();
	}
	for (auto& child : m_pChildren)
	{
		if (child.get() == nullptr) continue;
		child->OnGUI();
	}
}

void aze::GameObject::SetPosition(float x, float y)
{
	GetTransform().SetPosition(x, y, 0.0f);
}

aze::GameObject& aze::GameObject::Adopt(std::unique_ptr<aze::GameObject> pChild, bool worldPositionStays)
{
	pChild->m_pParent = this;
	if (worldPositionStays)
	{
		pChild->GetTransform().SetPosition(pChild->GetTransform().GetLocalPosition() - m_pParent->GetTransform().GetWorldPosition());
	}
	else
	{
		pChild->GetTransform().SetWorldPosDirty();
	}
	m_pChildren.emplace_back(std::move(pChild));
	return *this;
}

aze::GameObject& aze::GameObject::Adopt(GameObject* pChild, bool worldPositionStays)
{
	return Adopt(std::move(std::unique_ptr<GameObject>(pChild)),worldPositionStays);
}

aze::GameObject& aze::GameObject::RemoveChild(GameObject* pChild)
{
	if (pChild == nullptr)
	{
		throw aze::child_is_nullptr();
	}
	auto findChild = [&](const std::unique_ptr<GameObject>& ptr1) { return ptr1.get() == pChild; };
	auto it = std::find_if(m_pChildren.begin(), m_pChildren.end(), findChild);
	if (it == m_pChildren.end())
	{
		throw aze::wrong_parent();
	}

	pChild->m_pParent = nullptr;
	m_pChildren.erase(it);
	return *this;
}

aze::GameObject& aze::GameObject::SetParent(GameObject* pParent, bool worldPositionStays)
{
	// If our new parent is the scene
	if (pParent == nullptr)
	{
		// Use specialised setparent function
		return SetParent(nullptr);
	}

	// if our current parent is the scene
	if (m_pParent == nullptr)
	{
		// New parent adopts us from the scene
		pParent->Adopt(m_pScene->Abandon(this),worldPositionStays);
	}

	// Set new parent
	m_pParent = pParent;

	// Adjust location
	auto& transform = GetTransform();
	if (worldPositionStays)
	{
		transform.SetPosition(transform.GetLocalPosition() - m_pParent->GetTransform().GetWorldPosition());
	}
	else
	{
		transform.SetWorldPosDirty();
	}

	return *this;
}

aze::GameObject& aze::GameObject::SetParent(std::nullptr_t)
{
	// If we have no parent, we don't have to do anything
	if (m_pParent == nullptr)
	{
		return *this;
	}

	// Scene adopts us from the old parent
	m_pScene->Adopt(m_pParent->Abandon(this));

	m_pParent = nullptr;

	// Adjust location
	auto& transform = GetTransform();
	// Our local = world since our parent is the scene.
	transform.SetPosition(transform.GetWorldPosition());
	return *this;
}

std::unique_ptr<aze::GameObject> aze::GameObject::Abandon(GameObject* pChild)
{
	auto found = std::find_if(m_pChildren.begin(), m_pChildren.end(), [&](const auto& p) { return p.get() == pChild; });

	if (found != m_pChildren.end())
	{
		std::unique_ptr<GameObject> ptr(std::move(*found));
		m_pChildren.erase(found);
		return ptr;
	}

	return nullptr;
}

aze::GameObject* aze::GameObject::GetParent() const
{
	return m_pParent;
}

size_t aze::GameObject::GetChildCount() const
{
	return m_pChildren.size();
}

aze::GameObject* aze::GameObject::GetChildAt(size_t index) const
{
	return m_pChildren.at(index).get();
}

std::vector<aze::GameObject*> aze::GameObject::GetChildren() const
{
	std::vector<GameObject*> children;
	children.reserve(m_pChildren.size());
	for (auto& child : m_pChildren)
	{
		children.push_back(child.get());
	}
	return children;
}

aze::Scene* aze::GameObject::GetScene() const
{
	return m_pScene;
}

const aze::Transform& aze::GameObject::GetTransform() const
{
	return *m_Transform;
}

aze::Transform& aze::GameObject::GetTransform()
{
	if (!m_Transform || !m_Transform.get())
	{
		m_Transform = std::make_unique<Transform>(this);
	}
	return *m_Transform;
}
