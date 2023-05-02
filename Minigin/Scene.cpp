#include "Scene.h"

using namespace aze;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Adopt(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void aze::Scene::Adopt(GameObject* object)
{
	m_objects.emplace_back(std::move(std::unique_ptr<GameObject>(object)));
}

void aze::Scene::Remove(GameObject* object)
{
	assert(object->GetParent() == nullptr && "Object is not owned by the scene");

	auto it = std::find_if(m_objects.begin(), m_objects.end(), [&](const std::unique_ptr<GameObject>& ptr) { return ptr.get() == object; });
	m_objects.erase(it, m_objects.end());
}

std::unique_ptr<GameObject> aze::Scene::Abandon(GameObject* object)
{
	auto found = std::find_if(m_objects.begin(), m_objects.end(),[&](const auto& p) { return p.get() == object; });

	if (found != m_objects.end()) 
	{
		std::unique_ptr<GameObject> ptr(std::move(*found));
		m_objects.erase(found);
		return ptr;
	}

	return nullptr;
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void aze::Scene::Start()
{
	for (auto& object : m_objects)
	{
		object->Start();
	}
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}
	for (auto& object : m_objects)
	{
		if (object->IsMarkedForDestroy())
		{
			Remove(object.get());
		}
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void aze::Scene::OnGUI()
{
	for (const auto& object : m_objects)
	{
		object->OnGUI();
	}
}

