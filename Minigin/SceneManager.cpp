#include "SceneManager.h"
#include "Scene.h"

#include <iostream>

aze::SceneManager::SceneManager() = default;
aze::SceneManager::~SceneManager() = default;

void aze::SceneManager::Start()
{
	for (auto& scene : m_scenes)
	{
		scene->Start();
	}
}

void aze::SceneManager::Update()
{
	if (m_pActiveScene) m_pActiveScene->Update();
}

void aze::SceneManager::Render()
{
	if (m_pActiveScene) m_pActiveScene->Render();
}

void aze::SceneManager::OnGUI()
{
	if (m_pActiveScene) m_pActiveScene->OnGUI();
}

void aze::SceneManager::SetActiveScene(Scene* pScene)
{
	auto it = std::find_if(m_scenes.begin(), m_scenes.end(),
		[&](const std::unique_ptr<Scene>& uniquePtr) {
			return uniquePtr.get() == pScene;
		});

	if (it == m_scenes.end()) throw unregistered_scene();

	m_pActiveScene = pScene;
}

void aze::SceneManager::SetActiveScene(const std::string& sceneName)
{
	auto it = std::find_if(m_scenes.begin(), m_scenes.end(),
		[&](const std::unique_ptr<Scene>& uniquePtr) {
			return uniquePtr->GetName() == sceneName;
		});

	if (it == m_scenes.end()) throw unregistered_scene();

	m_pActiveScene = (*it).get();
}

aze::Scene* aze::SceneManager::GetActiveScene()
{
	return m_pActiveScene;
}

aze::Scene& aze::SceneManager::CreateScene(const std::string& name)
{
	m_scenes.emplace_back(std::unique_ptr<Scene>(new Scene(name)));
	if (m_pActiveScene == nullptr)
	{
		m_pActiveScene = m_scenes.back().get();
	}
	return *m_scenes.back();
}
