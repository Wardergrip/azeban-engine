#include "SceneManager.h"
#include "Scene.h"

void aze::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void aze::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void aze::SceneManager::OnGUI()
{
	for (const auto& scene : m_scenes)
	{
		scene->OnGUI();
	}
}

aze::Scene& aze::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
