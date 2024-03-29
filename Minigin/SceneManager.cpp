#include "SceneManager.h"
#include "Scene.h"

#include <iostream>

aze::SceneManager::SceneManager()
	:m_pSceneToBeLoaded{nullptr}
{
}
aze::SceneManager::~SceneManager() = default;

void aze::SceneManager::Start()
{
	
}

void aze::SceneManager::Update()
{
	if (m_pActiveScene.get()) m_pActiveScene->Update();
}

void aze::SceneManager::FixedUpdate()
{
	if (m_pActiveScene.get()) m_pActiveScene->FixedUpdate();
}

void aze::SceneManager::Render()
{
	if (m_pActiveScene.get()) m_pActiveScene->Render();
}

void aze::SceneManager::OnGUI()
{
	if (m_pActiveScene.get()) m_pActiveScene->OnGUI();
}

void aze::SceneManager::CleanUp()
{
	if (m_pActiveScene.get()) m_pActiveScene->CleanUp();
	if (m_pSceneToBeLoaded)
	{
		auto sceneToLoad = m_pSceneToBeLoaded;
		auto loadFunct = sceneToLoad->GetLoadFunction();

		m_pActiveScene = std::unique_ptr<Scene>(new Scene(sceneToLoad->GetName(), loadFunct));
		loadFunct(*m_pActiveScene);
		m_pActiveScene->Start();
		m_pSceneToBeLoaded = nullptr;
	}
}

void aze::SceneManager::SetActiveScene(const std::string& sceneName)
{
	auto it = std::find_if(m_scenes.begin(), m_scenes.end(),
		[&](const std::unique_ptr<Scene>& uniquePtr) {
			return uniquePtr->GetName() == sceneName;
		});

	if (it == m_scenes.end()) throw unregistered_scene();

	m_pSceneToBeLoaded = (*it).get();
	if (m_pActiveScene.get())
	{
		for (auto& obj : m_pActiveScene->m_objects)
		{
			GameObject::Destroy(obj.get());
		}
	}
}

aze::Scene* aze::SceneManager::GetActiveScene()
{
	return m_pActiveScene.get();
}

aze::Scene& aze::SceneManager::CreateScene(const std::string& name, const std::function<void(aze::Scene&)>& loadFunc)
{
	m_scenes.emplace_back(std::unique_ptr<Scene>(new Scene(name,loadFunc)));
	if (m_pSceneToBeLoaded == nullptr)
	{
		SetActiveScene(m_scenes.back().get()->GetName());
	}
	return *m_scenes.back();
}
